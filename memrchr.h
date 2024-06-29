/* memrchr.h -*- C -*- */

#ifndef MEMRCHR_H
# define MEMRCHR_H 1

# include <stdlib.h> /* for size_t */

# if !defined(HAVE_DECL_MEMRCHR) || !HAVE_DECL_MEMRCHR
extern void *memrchr(const void *, int, size_t);
# endif /* !HAVE_DECL_MEMRCHR */

#endif /* !MEMRCHR_H */
