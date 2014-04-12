/*
 *  alloc.h
 *  libUnixToOSX
 *
 *  Created by Eric Gallager on 4/2/14.
 *  Taken from Apple documentation.
 *
 */

#ifndef _ALLOCA_H
#define _ALLOCA_H 1

#undef  __alloca

/* Now define the internal interfaces.  */
extern void *__alloca(size_t __size);

#ifdef  __GNUC__
# define __alloca(size) __builtin_alloca (size)
#endif /* GCC.  */

#else
# ifndef __ALLOC_H__
#  define __ALLOC_H__ 1
typedef int alloc_h_dummy_t;
# endif /* !__ALLOC_H__ */
#endif /* !_ALLOCA_H */

/* EOF */
