/* strnlen.c: Find the length of STRING, but scan at most MAXLEN characters.
 * Copyright (C) 2005-2007, 2009-2012 Free Software Foundation, Inc.
 * Written by Simon Josefsson.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */

#include <string.h>

/* Find the length of STRING, but scan at most MAXLEN characters.
 * If no '\0' terminator is found in that many characters, return MAXLEN.
 */
#ifndef strnlen
/* this prototype would not be necessary if I were using gnulib properly,
 * or if I were on a system that already had strnlen()... */
size_t strnlen(const char *string, size_t maxlen);
#endif /* !strnlen */
size_t strnlen(const char *string, size_t maxlen)
{
  const char *end;
  end = (const char *)memchr(string, '\0', maxlen);
  return (end ? (size_t)(end - string) : maxlen);
}

/* EOF */
