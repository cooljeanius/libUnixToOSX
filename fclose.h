/*
 *  fclose.h
 *  libUnixToOSX
 *
 *  Created by Eric Gallager on 4/2/14.
 *  Header file for fclose.c and fcloseall.c
 *
 */

#ifndef _FCLOSE_H_
#define _FCLOSE_H_ 1

#include <stdio.h>

/* prototypes for functions from fclose.c: */
#ifndef rpl_fclose
int rpl_fclose(FILE *fp);
#endif /* !rpl_fclose */

/* prototypes and stuff required for fcloseall.c: */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif /* !_GNU_SOURCE */
#ifdef _GNU_SOURCE
int fcloseall(void);
#else
# if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#  warning "_GNU_SOURCE must be defined to use fcloseall()"
# endif /* __GNUC__ && !__STRICT_ANSI__ */
# ifdef(_GL_WARN_ON_USE)
_GL_WARN_ON_USE(fcloseall, "fcloseall is a GNU extension."
#  ifdef __APPLE__
				"Although OS X supports fclose, fcloseall is not supported."
#  endif /* __APPLE__ */
				);
# endif /* _GL_WARN_ON_USE */
#endif /* _GNU_SOURCE */

#endif /* !_FCLOSE_H_ */

/* EOF */
