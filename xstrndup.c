/* xstrndup.c: Duplicate a bounded initial segment of a string, with
 * out-of-memory checking.
 * Copyright (C) 2003, 2006-2007, 2009-2012 Free Software Foundation, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>

/* Specification.  */
#include "xstrndup.h"

#include <string.h>
#include "xalloc.h"

/* not sure if this "&&" should be an "||" instead: */
#if !defined(HAVE_STRNDUP) && !defined(strndup)
/* only try to get strndup from elsewhere if darwin does not already provide it: */
# if defined(__APPLE__) && (!defined(__DARWIN_C_LEVEL) || (defined(__DARWIN_C_LEVEL) && (__DARWIN_C_LEVEL < 200809L)))
#  if defined(HAVE_PUBLIB_H) && defined(HAVE_PUBLIB_STRUTIL_H)
#   include <publib.h>
#  else
#   if defined(HAVE_PUBLIB_STRUTIL_H)
#    include <publib/strutil.h>
#   else
#    if defined(HAVE_STRUTIL_H)
#     include <strutil.h>
#    else
#     if defined(__GNUC__) && !defined(__STRICT_ANSI__) && !defined(__STDC__)
#      warning "could not find a header to include to get strndup()"
#     endif /* __GNUC__ && !__STRICT_ANSI__ && !__STDC__ */
#    endif /* HAVE_STRUTIL_H */
#   endif /* HAVE_PUBLIB_STRUTIL_H */
#  endif /* HAVE_PUBLIB_H && HAVE_PUBLIB_STRUTIL_H */
# endif /* Apple pre-POSIX.1-2008 */
#endif /* !HAVE_STRNDUP && !strndup */

/* Return a newly allocated copy of at most N bytes of STRING.
 * In other words, return a copy of the initial segment of length N of
 * STRING.  */
char *
xstrndup (const char *string, size_t n)
{
  char *s = strndup(string, n);
  if (! s) {
    xalloc_die();
  }
  return s;
}

/* EOF */
