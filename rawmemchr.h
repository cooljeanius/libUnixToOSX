/*
 *  rawmemchr.h
 *  libUnixToOSX
 *
 *  Created by Eric Gallager on 4/17/14.
 *  Header file for rawmemchr.c and strchrnull.c
 *
 */

#ifndef _RAWMEMCHR_H_
#define _RAWMEMCHR_H_ 1

#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 1))
#   pragma GCC diagnostic ignored "-Wredundant-decls"
# endif /* GCC 4.1+ */
#endif /* gcc */

/* prototypes for functions from rawmemchr.c: */
#ifndef rawmemchr
void *rawmemchr(const void *s, int c_in);
#endif /* !rawmemchr */

/* prototypes for functions from strchrnul.c: */
#ifndef strchrnul
char *strchrnul(const char *s, int c_in);
#endif /* !strchrnul */

#endif /* !_FCLOSE_H_ */

/* EOF */
