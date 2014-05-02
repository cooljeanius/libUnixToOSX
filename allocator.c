/* allocator.c */

#ifndef _GL_USE_STDLIB_ALLOC
# define _GL_USE_STDLIB_ALLOC 1
#endif /* !_GL_USE_STDLIB_ALLOC */
#include <config.h>
#include "allocator.h"
#include <stdlib.h>
struct allocator const stdlib_allocator = { malloc, realloc, free, NULL };

/* silence '-Wunused-macros' warning: */
#ifdef _GL_USE_STDLIB_ALLOC
# undef _GL_USE_STDLIB_ALLOC
#endif /* _GL_USE_STDLIB_ALLOC */

/* EOF */
