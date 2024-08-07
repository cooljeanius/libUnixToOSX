/* fpending.c -- return the number of pending output bytes on a stream
 * Copyright (C) 2000, 2004, 2006-2007, 2009-2012 Free Software Foundation,
 * Inc.
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

/* Written by Jim Meyering. */

#include <config.h>

#include "fpending.h"

/* Return the number of pending (aka buffered, unflushed)
 * bytes on the stream, FP, that is open for writing.  */
size_t
__fpending(FILE *fp)
{
  (void)fp;
#if defined PENDING_OUTPUT_N_BYTES
  return (size_t)(PENDING_OUTPUT_N_BYTES);
#else
  return 0UL;
#endif /* PENDING_OUTPUT_N_BYTES */
}

/* EOF */
