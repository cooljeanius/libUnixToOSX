/*
 *  dysize.h
 *  libUnixToOSX
 *
 *  Created by Eric Gallager on 4/2/14.
 *  Header for code that was adapted from code taken from Apple documentation.
 *
 */

#ifndef _DYSIZE_H_
#define _DYSIZE_H_ 1

#include <time.h>

/* prototypes: */
int dysize(int year);
#if defined(_GL_WARN_ON_USE) && defined(__APPLE__)
_GL_WARN_ON_USE(dysize, "dysize is not supported in OS X.");
#endif /* _GL_WARN_ON_USE && __APPLE__ */

#endif /* !_DYSIZE_H */

/* EOF */
