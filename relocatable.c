/* relocatable.c: Provide relocatable packages.
 * Copyright (C) 2003-2006, 2008-2012 Free Software Foundation, Inc.
 * Written by Bruno Haible <bruno@clisp.org>, 2003.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Tell glibc's <stdio.h> to provide a prototype for getline().
 * This must come before <config.h> because <config.h> may include
 * <features.h>, and once <features.h> has been included, it is too late. */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif /* !_GNU_SOURCE */

#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2))
#  pragma GCC diagnostic ignored "-Wunused-macros"
# endif /* GCC 4.2+ */
#endif /* gcc */

#ifndef _GL_USE_STDLIB_ALLOC
# define _GL_USE_STDLIB_ALLOC 1
#endif /* !_GL_USE_STDLIB_ALLOC */
#include <config.h>

/* Specification: */
#include "relocatable.h"

#if ENABLE_RELOCATABLE

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# ifdef HAVE_MACH_O_DYLD_H
#  include <mach-o/dyld.h>
# endif /* HAVE_MACH_O_DYLD_H */

# ifdef HAVE_DLFCN_H
#  ifdef __APPLE__
#   define _DARWIN_C_SOURCE 1 /* to get the Dl_info struct */
#  endif /* __APPLE__ */
#  include <dlfcn.h>
# endif /* HAVE_DLFCN_H */

# ifdef NO_XMALLOC
#  define xmalloc malloc
# else
#  include "xalloc.h"
# endif /* NO_XMALLOC */

# if (defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__
#  define WIN32_LEAN_AND_MEAN 1
#  include <windows.h>
# endif /* (_WIN32 || __WIN32__) && !__CYGWIN__ */

# if defined(DEPENDS_ON_LIBCHARSET) && DEPENDS_ON_LIBCHARSET
#  include <libcharset.h>
# endif /* DEPENDS_ON_LIBCHARSET */
# if (defined(DEPENDS_ON_LIBICONV) && DEPENDS_ON_LIBICONV) && HAVE_ICONV
#  include <iconv.h>
# endif /* DEPENDS_ON_LIBICONV && HAVE_ICONV */
# if (defined(DEPENDS_ON_LIBINTL) && DEPENDS_ON_LIBINTL) && ENABLE_NLS
#  include <libintl.h>
# endif /* DEPENDS_ON_LIBINTL && ENABLE_NLS */

/* Faked cheap 'bool'.  */
# undef bool
# undef false
# undef true
# define bool int
# define false 0
# define true 1

/* Pathname support.
 * ISSLASH(C)           tests whether C is a directory separator character.
 * IS_PATH_WITH_DIR(P)  tests whether P contains a directory specification.
 */
# if ((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__) || defined __EMX__ || defined __DJGPP__
/* Native Windows, OS/2, DOS */
#  define ISSLASH(C) (((C) == '/') || ((C) == '\\'))
#  define HAS_DEVICE(P) \
    (((((P)[0] >= 'A') && ((P)[0] <= 'Z')) || (((P)[0] >= 'a') && ((P)[0] <= 'z'))) \
     && ((P)[1] == ':'))
#  define IS_PATH_WITH_DIR(P) \
    ((strchr(P, '/') != NULL) || (strchr(P, '\\') != NULL) || HAS_DEVICE(P))
#  define FILE_SYSTEM_PREFIX_LEN(P) (HAS_DEVICE(P) ? 2 : 0)
# else
/* Unix */
#  define ISSLASH(C) ((C) == '/')
#  define IS_PATH_WITH_DIR(P) (strchr(P, '/') != NULL)
#  define FILE_SYSTEM_PREFIX_LEN(P) 0
# endif /* ((_WIN32 || __WIN32__) && !__CYGWIN__) || __EMX__ || __DJGPP__ */

/* Whether to enable the more costly support for relocatable libraries.
 * It allows libraries to be have been installed with a different original
 * prefix than the program. But it is quite costly, especially on Cygwin
 * platforms, see below. Therefore we enable it by default only on native
 * Windows platforms.  */
# ifndef ENABLE_COSTLY_RELOCATABLE
#  if (defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__
#   define ENABLE_COSTLY_RELOCATABLE 1
#  else
#   define ENABLE_COSTLY_RELOCATABLE 0
#  endif /* (_WIN32 || __WIN32__) && !__CYGWIN__ */
# endif /* !ENABLE_COSTLY_RELOCATABLE */

/* Original installation prefix.  */
static char *orig_prefix;
static size_t orig_prefix_len;
/* Current installation prefix.  */
static char *curr_prefix;
static size_t curr_prefix_len;
/* These prefixes do not end in a slash. Anything that will be concatenated
 * to them must start with a slash.  */

/* Sets the original and the current installation prefix of this module.
 * Relocation simply replaces a pathname starting with the original prefix
 * by the corresponding pathname with the current prefix instead. Both
 * prefixes should be directory names without trailing slash (i.e. use ""
 * instead of "/").  */
static void
set_this_relocation_prefix(const char *orig_prefix_arg,
						   const char *curr_prefix_arg)
{
	int can_use_mem = 1;
	if ((orig_prefix_arg != NULL) && (curr_prefix_arg != NULL)
		/* Optimization: if orig_prefix and curr_prefix are equal, the
		 * relocation is a nop.  */
		&& (strcmp(orig_prefix_arg, curr_prefix_arg) != 0)) {
		/* Duplicate the argument strings.  */
		char *memory;

		orig_prefix_len = strlen(orig_prefix_arg);
		curr_prefix_len = strlen(curr_prefix_arg);
		memory = (char *)xmalloc(orig_prefix_len + 1 + curr_prefix_len + 1);
# ifdef NO_XMALLOC
		if (memory != NULL) {
			/* do nothing (keep 'can_use_mem' the same) */ ;
		} else {
			can_use_mem = 0;
		}
# endif /* NO_XMALLOC */
		/* new variable check is to prevent code-level conditional from being
		 * split by the preprocessor-level conditional: */
		if (can_use_mem == 1) {
			memcpy(memory, orig_prefix_arg, (orig_prefix_len + 1));
			orig_prefix = memory;
			memory += (orig_prefix_len + 1);
			memcpy(memory, curr_prefix_arg, (curr_prefix_len + 1));
			curr_prefix = memory;
			return;
		}
	}
	orig_prefix = NULL;
	curr_prefix = NULL;
	/* Do NOT worry about wasted memory here - this function is usually only
	 * called once.  */
}

/* Sets the original and the current installation prefix of the package.
 * Relocation simply replaces a pathname starting with the original prefix
 * by the corresponding pathname with the current prefix instead. Both
 * prefixes should be directory names without trailing slash (i.e. use ""
 * instead of "/").  */
void
set_relocation_prefix(const char *orig_prefix_arg, const char *curr_prefix_arg)
{
	set_this_relocation_prefix(orig_prefix_arg, curr_prefix_arg);

	/* Now notify all dependent libraries: */
# if defined(DEPENDS_ON_LIBCHARSET) && DEPENDS_ON_LIBCHARSET
	libcharset_set_relocation_prefix(orig_prefix_arg, curr_prefix_arg);
# endif /* DEPENDS_ON_LIBCHARSET */
# if (defined(DEPENDS_ON_LIBICONV) && DEPENDS_ON_LIBICONV) && HAVE_ICONV && (_LIBICONV_VERSION >= 0x0109)
	libiconv_set_relocation_prefix(orig_prefix_arg, curr_prefix_arg);
# endif /* DEPENDS_ON_LIBICONV && HAVE_ICONV && (_LIBICONV_VERSION >= 0x0109) */
# if (defined(DEPENDS_ON_LIBINTL) && DEPENDS_ON_LIBINTL) && ENABLE_NLS && defined(libintl_set_relocation_prefix)
	libintl_set_relocation_prefix(orig_prefix_arg, curr_prefix_arg);
# endif /* DEPENDS_ON_LIBINTL && ENABLE_NLS && libintl_set_relocation_prefix */
}

# if !defined IN_LIBRARY || (defined PIC && defined INSTALLDIR && ENABLE_COSTLY_RELOCATABLE)

/* Convenience function:
 * Computes the current installation prefix, based on the original
 * installation prefix, the original installation directory of a particular
 * file, and the current pathname of this file.
 * Returns it, freshly allocated.  Returns NULL upon failure.  */
#  ifdef IN_LIBRARY
#   define compute_curr_prefix local_compute_curr_prefix
static
#  endif /* IN_LIBRARY */
char *
compute_curr_prefix(const char *orig_installprefix, const char *orig_installdir,
					const char *curr_pathname)
{
	char *curr_installdir;
	const char *rel_installdir;

	if (curr_pathname == NULL) {
		return NULL;
	}

	/* Determine the relative installation directory, relative to the prefix.
     * This is simply the difference between orig_installprefix and
     * orig_installdir. */
	if (strncmp(orig_installprefix, orig_installdir, strlen(orig_installprefix))
		!= 0) {
		/* Should NOT happen - nothing should be installed outside $(prefix). */
		return NULL;
	}
	rel_installdir = (orig_installdir + strlen(orig_installprefix));

	/* Determine the current installation directory. */
	{
		const char *p_base = (curr_pathname + FILE_SYSTEM_PREFIX_LEN(curr_pathname));
		const char *p = (curr_pathname + strlen(curr_pathname));
		char *q;

		while (p > p_base) {
			p--;
			if (ISSLASH(*p)) {
				break;
			}
		}

		q = (char *)xmalloc((size_t)(p - curr_pathname + 1));
#  ifdef NO_XMALLOC
		if (q == NULL) {
			return NULL;
		}
#  endif /* NO_XMALLOC */
		memcpy(q, curr_pathname, (size_t)(p - curr_pathname));
		q[(p - curr_pathname)] = '\0';
		curr_installdir = q;
	}

	/* Compute the current installation prefix by removing the trailing
	 * rel_installdir from it.  */
	{
		const char *rp = (rel_installdir + strlen(rel_installdir));
		const char *cp = (curr_installdir + strlen(curr_installdir));
		const char *cp_base =
			(curr_installdir + FILE_SYSTEM_PREFIX_LEN(curr_installdir));

		while ((rp > rel_installdir) && (cp > cp_base)) {
			bool same = false;
			const char *rpi = rp;
			const char *cpi = cp;

			while ((rpi > rel_installdir) && (cpi > cp_base)) {
				rpi--;
				cpi--;
				if (ISSLASH(*rpi) || ISSLASH(*cpi)) {
					if (ISSLASH(*rpi) && ISSLASH(*cpi)) {
						same = true;
					}
					break;
				}
				/* Do case-insensitive comparison if the file system is always or
				 * often case-insensitive. It is better to accept the comparison
				 * if the difference is only in case, rather than to fail.  */
#  if defined _WIN32 || defined __WIN32__ || defined __CYGWIN__ || defined __EMX__ || defined __DJGPP__
				/* Native Windows, Cygwin, OS/2, DOS - case insignificant file system */
				if (((*rpi >= 'a') && (*rpi <= ('z' ? (*rpi - 'a' + 'A') : *rpi)))
					!= ((*cpi >= 'a') && (*cpi <= ('z' ? (*cpi - 'a' + 'A') : *cpi)))) {
					break;
				}
#  else
				if (*rpi != *cpi) {
					break;
				}
#  endif /* _WIN32 || __WIN32__ || __CYGWIN__ || __EMX__ || __DJGPP__ */
			}
			if (!same) {
				break;
			}
			/* The last pathname component was the same. opi and cpi now point
			 * to the slash before it.  */
			rp = rpi;
			cp = cpi;
		}

		if (rp > rel_installdir) {
			/* Unexpected: The curr_installdir does not end with
			 * rel_installdir. */
			free(curr_installdir);
			return NULL;
		}

		{
			/* these are already globally declared, not sure whether to deal
			 * with the shadowing or not: */
			size_t curr_prefix_len = (size_t)(cp - curr_installdir);
			char *curr_prefix;

			curr_prefix = (char *)xmalloc(curr_prefix_len + 1);
#  ifdef NO_XMALLOC
			if (curr_prefix == NULL) {
				free(curr_installdir);
				return NULL;
			}
#  endif /* NO_XMALLOC */
			memcpy(curr_prefix, curr_installdir, curr_prefix_len);
			curr_prefix[curr_prefix_len] = '\0';

			free(curr_installdir);

			return curr_prefix;
		}
	}
}

# endif /* !IN_LIBRARY || PIC */

# if defined PIC && defined INSTALLDIR && ENABLE_COSTLY_RELOCATABLE

/* global variable for the full pathname of shared library, or NULL. */
static char *shared_library_fullname;

#  if (defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__
/* Native Windows only.
 * On Cygwin, it is better to use the Cygwin-provided /proc interface, than
 * to use native Windows API and cygwin_conv_to_posix_path, because it
 * supports longer file names
 * (see <http://cygwin.com/ml/cygwin/2011-01/msg00410.html>). */

/* Determine the full pathname of the shared library when it is loaded. */
BOOL WINAPI
DllMain(HINSTANCE module_handle, DWORD event, LPVOID reserved)
{
	(void)reserved;

	if (event == DLL_PROCESS_ATTACH) {
		/* The DLL is being loaded into an application's address range. */
		static char location[MAX_PATH];

		if (!GetModuleFileName(module_handle, location, sizeof(location))) {
			/* Should NOT happen. */
			return FALSE;
		}

		if (!IS_PATH_WITH_DIR(location)) {
			/* Should NOT happen. */
			return FALSE;
		}

		shared_library_fullname = strdup(location);
	}

	return TRUE;
}

#  else /* Unix */

static void
find_shared_library_fullname()
{
#   if (defined __linux__ && (__GLIBC__ >= 2 || defined __UCLIBC__)) || defined __CYGWIN__
	/* Linux has /proc/self/maps. glibc 2 and uClibc have the getline()
	 * function.
	 * Cygwin >= 1.5 has /proc/self/maps and the getline() function too.
	 * But it is costly: ca. 0.3 ms on Linux, 3 ms on Cygwin 1.5, and 5 ms on
	 * Cygwin 1.7.
	 * Also compiles on other OSes, but that does not mean that it is
	 * necessarily correct, because it can compile without /proc/self/maps even
	 * being present */
	FILE *fp;

	/* Open the maps file for the current proc. It describes 1 VMA per line. */
	fp = fopen("/proc/self/maps", "r");
	if (fp) {
		/* hey wait a second */
		unsigned long address = (unsigned long)&find_shared_library_fullname;
		for (;;) {
			unsigned long start, end;
			int c;

			if (fscanf(fp, "%lx-%lx", &start, &end) != 2) {
				break;
			}
			if ((address >= start) && (address <= (end - 1))) {
				/* Found it. Now see if this line contains a filename.  */
				while ((c = getc(fp)), ((c != EOF) && (c != '\n') && (c != '/'))) {
					continue;
				}
				if (c == '/') {
					size_t size;
					int len;

					ungetc(c, fp);
					shared_library_fullname = NULL;
					size = 0;
					len = getline(&shared_library_fullname, &size, fp);
					if (len >= 0) {
						/* Success: filled shared_library_fullname. */
						if ((len > 0) && (shared_library_fullname[(len - 1)] == '\n')) {
							shared_library_fullname[(len - 1)] = '\0';
						}
                    }
                }
				break;
            }
			while ((c = getc(fp)), ((c != EOF) && (c != '\n'))) {
				continue;
			}
        }
		fclose(fp);
    }
#   elif defined(HAVE_DLADDR)
	Dl_info* info;
	/* TODO: actually calculate this with dladdr() once we have a way to provide
	 * a valid address for the first paramater to dladdr(): */
	info.dli_fname = "/dev/null";
	if (info.dli_fname != NULL) {
		shared_library_fullname = info.dli_fname;
	}
#   endif /* ((__linux__ && glibc 2+) || __CYGWIN__) || HAVE_DLADDR */
}

#  endif /* Native Windows / Unix */

/* Return the full pathname of the current shared library.
 * Return NULL if unknown.
 * Guaranteed to work only on Linux, Cygwin, and native Windows. */
static char *
get_shared_library_fullname()
{
#  if !((defined _WIN32 || defined __WIN32__) && !defined __CYGWIN__)
	static bool tried_find_shared_library_fullname;
	if (!tried_find_shared_library_fullname) {
		find_shared_library_fullname();
		tried_find_shared_library_fullname = true;
    }
#  endif /* !((_WIN32 || __WIN32__) && !__CYGWIN__) */
	return shared_library_fullname;
}

# endif /* PIC */

/* Returns the pathname, relocated according to the current installation
 directory.
 The returned string is either PATHNAME unmodified or a freshly allocated
 string that you can free with free() after casting it to 'char *'.  */
const char *
relocate(const char *pathname)
{
# if defined PIC && defined INSTALLDIR && ENABLE_COSTLY_RELOCATABLE
	static int initialized;

	/* Initialization code for a shared library.  */
	if (!initialized) {
		/* At this point, orig_prefix and curr_prefix likely have already been
		 * set through the main program's set_program_name_and_installdir
		 * function. This is sufficient in the case that the library has
         * initially been installed in the same orig_prefix. But we can do
         * better, to also cover the cases that:
		 * 1. it has been installed in a different prefix before being moved to
		 *    orig_prefix and (later) to curr_prefix, or:
		 * 2. unlike the program, it has not moved away from orig_prefix.  */
		const char *orig_installprefix = INSTALLPREFIX;
		const char *orig_installdir = INSTALLDIR;
		char *curr_prefix_better;

		curr_prefix_better =
        compute_curr_prefix(orig_installprefix, orig_installdir,
							get_shared_library_fullname());

		set_relocation_prefix(orig_installprefix, ((curr_prefix_better != NULL)
												   ? curr_prefix_better
												   : curr_prefix));

		if (curr_prefix_better != NULL) {
			free(curr_prefix_better);
		}

		initialized = 1;
    }
# endif /* PIC && INSTALLDIR && ENABLE_COSTLY_RELOCATABLE */

	/* Note: It is not necessary to perform case insensitive comparison here,
     * even for DOS-like file systems, because the pathname argument was
     * typically created from the same Makefile variable as orig_prefix came
     * from.  */
	if ((orig_prefix != NULL) && (curr_prefix != NULL)
		&& (strncmp(pathname, orig_prefix, orig_prefix_len) == 0)) {
		if (pathname[orig_prefix_len] == '\0') {
			int have_result = 1;
			/* pathname equals orig_prefix.  */
			char *result = (char *)xmalloc(strlen (curr_prefix) + 1);
# ifdef NO_XMALLOC
			if (result != NULL) {
				/* do nothing (value stored to 'have_result' stays 1) */ ;
			} else {
				have_result = 0;
			}
# endif /* NO_XMALLOC */
			/* another case of my insistence my preferred bracketing style
			 * leading to the introduction of a new variable: */
            if (have_result == 1) {
				strcpy (result, curr_prefix);
				return result;
            }
        } else if (ISSLASH (pathname[orig_prefix_len])) {
			/* pathname starts with orig_prefix.  */
			const char *pathname_tail = &pathname[orig_prefix_len];
			int have_result_here = 1;
			char *result =
				(char *)xmalloc(curr_prefix_len + strlen(pathname_tail) + 1);
# ifdef NO_XMALLOC
			if (result != NULL) {
				/* do nothing (keep 'have_result_here' the same) */ ;
			} else {
				have_result_here = 0;
			}
# endif /* NO_XMALLOC */
			/* as above */
            if (have_result_here == 1) {
				memcpy(result, curr_prefix, curr_prefix_len);
				strcpy((result + curr_prefix_len), pathname_tail);
				return result;
            }
        }
    }
	/* Nothing to relocate. */
	return pathname;
}

#else
/* prevent file from being empty: */
typedef int relocatable_c_dummy_t;
#endif /* ENABLE_RELOCATABLE */

/* EOF */
