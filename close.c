/* close.c: close replacement.
 * Copyright (C) 2008-2012 Free Software Foundation, Inc.
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
#include <unistd.h>

#include <errno.h>

#include "fd-hook.h"
#include "msvc-inval.h"

#include "rpl_misc_funcs.h"

#undef close

#if defined(HAVE_MSVC_INVALID_PARAMETER_HANDLER) && HAVE_MSVC_INVALID_PARAMETER_HANDLER
static int close_nothrow(int fd)
{
  int result;

  TRY_MSVC_INVAL
    {
      result = close(fd);
    }
  CATCH_MSVC_INVAL
    {
      result = -1;
      errno = EBADF;
    }
  DONE_MSVC_INVAL;

  return result;
}
#else
# define close_nothrow close
#endif /* HAVE_MSVC_INVALID_PARAMETER_HANDLER */

/* Override close() to call into other gnulib modules: */
int rpl_close(int fd)
{
#if defined(WINDOWS_SOCKETS) && WINDOWS_SOCKETS
  int retval = execute_all_close_hooks(close_nothrow, fd);
#else
  int retval = close_nothrow(fd);
#endif /* WINDOWS_SOCKETS */

#if defined(REPLACE_FCHDIR) && REPLACE_FCHDIR
  if (retval >= 0) {
    _gl_unregister_fd(fd);
  }
#endif /* REPLACE_FCHDIR */

  return retval;
}

/* EOF */
