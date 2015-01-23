/* getmntent.c */
/* adapted from a portion of Wine's  dlls/ntdll/directory.c */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */

/* Specification. */
#include "mntent.h"

#include <fstab.h> /* header for getfsent(), which is equivalent on OSX */
#include <string.h> /* for strsep() and strspn() */
#include <stdio.h> /* for file pointers */
#include <stdlib.h> /* for atoi() */

#ifdef __ANDROID__
/* prototype: */
# ifdef __WINESRC__
static
# endif /* __WINESRC__ */
struct mntent *getmntent_replacement(FILE *f);

/* helper function: */
static char *unescape_field(char *str)
{
    char *in, *out;

    for ((in = out = str); *in; in++, out++) {
        *out = *in;
        if (in[0] == '\\') {
            if (in[1] == '\\') {
                out[0] = '\\';
                in++;
            } else if ((in[1] == '0') && (in[2] == '4') && (in[3] == '0')) {
                out[0] = ' ';
                in += 3;
            } else if ((in[1] == '0') && (in[2] == '1') && (in[3] == '1')) {
                out[0] = '\t';
                in += 3;
            } else if ((in[1] == '0') && (in[2] == '1') && (in[3] == '2')) {
                out[0] = '\n';
                in += 3;
            } else if ((in[1] == '1') && (in[2] == '3') && (in[3] == '4')) {
                out[0] = '\\';
                in += 3;
            }
        }
    }
    *out = '\0';

    return str;
}

static inline char *get_field(char **str)
{
    char *ret;

    ret = strsep(str, " \t");
    if (*str) {
		*str += strspn(*str, " \t");
	}

    return ret;
}
/************************************************************************
 * getmntent_replacement
 *
 * getmntent replacement for Android.
 *
 * N.B.: returned static buffer is not thread safe; protect it with
 * dir_section:
 */
#ifdef __WINESRC__
static
#endif /* __WINESRC__ */
struct mntent *getmntent_replacement(FILE *f)
{
    static struct mntent mount_entry;
    static char buf[4096];
    char *p, *start;

    do {
        if (!fgets(buf, (int)sizeof(buf), f)) {
			return NULL;
		}
        p = strchr(buf, '\n');
        if (p) {
			*p = '\0';
        } else {
			/* Partially unread line, move file ptr to end: */
            char tmp[1024];
            while (fgets(tmp, (int)sizeof(tmp), f)) {
                if (strchr(tmp, '\n')) {
					break;
				}
			}
        }
        start = (buf + strspn(buf, " \t"));
    } while ((start[0] == '\0') || (start[0] == '#'));

    p = get_field(&start);
    mount_entry.mnt_fsname = (p ? unescape_field(p) : (char *)"");

    p = get_field(&start);
    mount_entry.mnt_dir = (p ? unescape_field(p) : (char *)"");

    p = get_field(&start);
    mount_entry.mnt_type = (p ? unescape_field(p) : (char *)"");

    p = get_field(&start);
    mount_entry.mnt_opts = (p ? unescape_field(p) : (char *)"");

    p = get_field(&start);
    mount_entry.mnt_freq = (p ? atoi(p) : 0);

    p = get_field(&start);
    mount_entry.mnt_passno = (p ? atoi(p) : 0);

    return &mount_entry;
}
# define getmntent getmntent_replacement
#endif /* __ANDROID__ */

/* Silence a warning from '-Wunused-macros' (temporarily) */
#ifdef getmntent
# undef getmntent
#endif /* getmntent */

/* EOF */
