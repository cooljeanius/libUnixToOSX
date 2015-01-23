/* strndup.c: A replacement function, for systems that lack strndup.
 *
 * Copyright (C) 1996-1998, 2001-2003, 2005-2007, 2009-2012 Free Software
 * Foundation, Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 1))
#   pragma GCC diagnostic ignored "-Wredundant-decls"
# endif /* GCC 4.1+ */
#endif /* gcc */

#include <config.h>

#include <string.h>

#include <stdlib.h>

#ifndef __STRING_H
# include "string.h"
#endif /* !__STRING_H */

#ifndef strnlen
/* prototype might not actually be in "string.h", even if "strnlen.c" does
 * get built: */
size_t strnlen(const char *string, size_t maxlen);
#endif /* !strnlen */

char *strndup(char const *s, size_t n)
{
  size_t len;
  char *newstr;

  len = strnlen(s, n);
  newstr = (char *)malloc(len + 1UL);

  if (newstr == NULL) {
	  return NULL;
  }

  newstr[len] = '\0';
  return (char *)memcpy((char *)newstr, s, len);
}

/* EOF */
