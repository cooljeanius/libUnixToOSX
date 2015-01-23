/* fallocate.c: Allocate storage for a file descriptor.
   Copyright (C) 2009 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>. */

/* Written by Pádraig Brady <P@draigBrady.com>, 2009.  */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */

#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

/* FIXME: look at orig email for this file definition. */
int rpl_fallocate(int fd, int mode, off_t offset, off_t len)
{
#if (defined(__APPLE__) && defined(__APPLE_CC__)) || defined(__MWERKS__)
# pragma unused (fd, mode, offset, len)
#endif /* (__APPLE__ && __APPLE_CC__) || __MWERKS__ */
  /* This is a valid replacement for missing glibc fallocate(),
   * because code calling fallocate() must also handle this error
   * in the case that the kernel or filesystem do NOT support this: */
  return ENOSYS; /* FIXME: glibc interface may change to set errno and ret -1 */
  /* FIXME: support fcntl(fd, F_ALLOCSP, ...) on solaris.  */
}

/* EOF */
