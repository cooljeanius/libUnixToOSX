/* fdopen.c: Open a stream with a given file descriptor.
 * Copyright (C) 2011-2012 Free Software Foundation, Inc.
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

#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 1))
#   pragma GCC diagnostic ignored "-Wredundant-decls"
# endif /* GCC 4.1+ */
#endif /* gcc */

#include <config.h>

/* Specification: */
#include <stdio.h>

#include <errno.h>

#include "rpl_misc_funcs.h"

#if defined(HAVE_MSVC_INVALID_PARAMETER_HANDLER) && HAVE_MSVC_INVALID_PARAMETER_HANDLER
# include "msvc-inval.h"
#endif /* HAVE_MSVC_INVALID_PARAMETER_HANDLER */

#undef fdopen

#if defined(HAVE_MSVC_INVALID_PARAMETER_HANDLER) && HAVE_MSVC_INVALID_PARAMETER_HANDLER
static FILE *
fdopen_nothrow(int fd, const char *mode)
{
  FILE *result;

  TRY_MSVC_INVAL
    {
      result = fdopen(fd, mode);
    }
  CATCH_MSVC_INVAL
    {
      result = NULL;
    }
  DONE_MSVC_INVAL;

  return result;
}
#else
# define fdopen_nothrow fdopen
#endif /* HAVE_MSVC_INVALID_PARAMETER_HANDLER */

FILE *
rpl_fdopen(int fd, const char *mode)
{
  int saved_errno = errno;
  FILE *fp;

  errno = 0;
  fp = fdopen_nothrow (fd, mode);
  if (fp == NULL) {
      if (errno == 0) {
        errno = EBADF;
	  }
  } else {
	  errno = saved_errno;
  }

  return fp;
}

/* EOF */
