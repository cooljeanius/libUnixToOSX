/* unistd-safer.h: Invoke unistd-like functions, but avoid some glitches.
 *
 * Copyright (C) 2001, 2003, 2005, 2009-2012 Free Software Foundation, Inc.
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

/* Written by Paul Eggert and Eric Blake.  */

#ifndef __UNISTD_SAFER_H__
#define __UNISTD_SAFER_H__ 1

int dup_safer(int);
int fd_safer(int);
int pipe_safer(int[2]);

/* if you do not want to define this just to get these prototypes, there are
 * other headers that yoou can include that I also put these prototypes in: */
#if defined(GNULIB_FD_SAFER_FLAG) && GNULIB_FD_SAFER_FLAG
int dup_safer_flag(int, int);
int fd_safer_flag(int, int);
#endif /* GNULIB_FD_SAFER_FLAG */

#if defined(GNULIB_PIPE2_SAFER) && GNULIB_PIPE2_SAFER
int pipe2_safer(int[2], int);
#endif /* GNULIB_PIPE2_SAFER */

#endif /* !__UNISTD_SAFER_H__ */

/* EOF */
