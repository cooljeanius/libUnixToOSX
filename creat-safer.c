/* creat-safer.c: Invoke creat, but avoid some glitches.
 *
 * Copyright (C) 2005-2006, 2009-2012 Free Software Foundation, Inc.
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

/* Written by Jim Meyering.  */

#include <config.h>

#include "fcntl-safer.h"

#include <fcntl.h>
#include "unistd-safer.h"

/* we already cast, which fails to fix the warning, so turn it off: */
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 1))
#  if (__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)
/* can push and pop with this version, so do so: */
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wtraditional-conversion"
#  else
#   pragma GCC diagnostic ignored "-Wconversion"
#  endif /* GCC 4.6+ || not */
# endif /* GCC 4.1+ */
#endif /* gcc */

int creat_safer(char const *file, mode_t mode)
{
  return fd_safer(creat(file, (mode_t)mode));
}

/* keep condition (essentially) the same as where we push: */
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6))
#  pragma GCC diagnostic pop
# endif /* GCC 4.6+ */
#endif /* gcc */

/* EOF */
