/*	$OpenBSD: ftw.c,v 1.4 2004/07/07 16:05:23 millert Exp $	*/

/*
 * Copyright (c) 2003, 2004 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Sponsored in part by the Defense Advanced Research Projects
 * Agency (DARPA) and Air Force Research Laboratory, Air Force
 * Materiel Command, USAF, under agreement number F39502-99-1-0512.
 */

#if 0
# if defined(LIBC_SCCS) && !defined(lint)
static const char rcsid[] = "$OpenBSD: ftw.c,v 1.4 2004/07/07 16:05:23 millert Exp $";
# else
extern int libftw0_ftw_c_var;
int libftw0_ftw_c_var = 0;
# endif /* LIBC_SCCS and not lint */
#else
typedef int libftw0_ftw_c_t;
#endif /* 0 */

#include <sys/cdefs.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fts.h>
#include <ftw.h>
#include <limits.h>
#include <unistd.h>

#ifndef OPEN_MAX
# define OPEN_MAX 10240 /* max open files per process. TODO: make a config option? */
#endif /* !OPEN_MAX */

int
ftw(const char *path, int (*fn)(const char *, const struct stat *, int),
    int nfds)
{
	char *const paths[2] = { (char *)path, NULL };
	FTSENT *cur;
	FTS *ftsp;
	int error, fnflag, sverrno;

	error = 0;

	/* XXX: nfds is currently unused */
	if ((nfds < 1) || (nfds > OPEN_MAX)) {
		errno = EINVAL;
		return (-1);
	}

	ftsp = fts_open(paths, (FTS_LOGICAL | FTS_COMFOLLOW | FTS_NOCHDIR), NULL);
	if (ftsp == NULL) {
		return (-1);
	}
	while ((cur = fts_read(ftsp)) != NULL) {
		switch (cur->fts_info) {
			case FTS_D:
				fnflag = FTW_D;
				break;
			case FTS_DNR:
				fnflag = FTW_DNR;
				break;
			case FTS_DP:
				/* we only visit in preorder */
				continue;
			case FTS_F:
			case FTS_DEFAULT:
				fnflag = FTW_F;
				break;
			case FTS_NS:
			case FTS_NSOK:
			case FTS_SLNONE:
				fnflag = FTW_NS;
				break;
			case FTS_SL:
				fnflag = FTW_SL;
				break;
			case FTS_DC:
				errno = ELOOP;
				/* FALLTHROUGH */
			default:
				error = -1;
				goto done;
		}
		error = fn(cur->fts_path, cur->fts_statp, fnflag);
		if (error != 0) {
			break;
		}
	}

done:
	sverrno = errno;
	if ((fts_close(ftsp) != 0) && (error == 0)) {
		error = -1;
	} else {
		errno = sverrno;
	}
	return (error);
}

/* EOF */
