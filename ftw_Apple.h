/*
 *  ftw_Apple.h
 *  libUnixToOSX
 *
 *  Created by Eric Gallager on 4/2/14.
 *  Header for code that was adapted from code taken from Apple documentation.
 *
 */

#ifndef _FTW_APPLE_H_
#define _FTW_APPLE_H_ 1

#include <fts.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>

/* prototypes: */
int ftw_simple(char *argv[]);
#if defined(_GL_WARN_ON_USE) && defined(__APPLE__)
_GL_WARN_ON_USE(ftw_simple, "ftw_simple is not natively present on OS X.");
#endif /* _GL_WARN_ON_USE && __APPLE__ */
int compar_for_fts_open(const FTSENT **fsthing1, const FTSENT **fsthing2);

#endif /* !_FTW_APPLE_H_ */

/* EOF */
