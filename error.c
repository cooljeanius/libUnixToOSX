/* error.c: error handler for noninteractive utilities
 * Copyright (C) 1990-1998, 2000-2007, 2009-2012 Free Software Foundation, Inc.
 * This file is part of the GNU C Library.
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

/* Written by David MacKenzie <djm@gnu.ai.mit.edu>. */

#if !defined(_LIBC) || (defined(_LIBC) && !_LIBC)
# include <config.h>
#endif /* !_LIBC */

#include "error.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (!defined(_LIBC) || (defined(_LIBC) && !_LIBC)) && (defined(ENABLE_NLS) && ENABLE_NLS)
# include "gettext.h"
# define _(msgid) gettext (msgid)
#endif /* !_LIBC && ENABLE_NLS */

#ifdef _LIBC
# include <libintl.h>
# include <stdbool.h>
# include <stdint.h>
# include <wchar.h>
# define mbsrtowcs __mbsrtowcs
#else
# if defined(HAVE_LIBINTL_H) && (defined(ENABLE_NLS) && ENABLE_NLS)
#  include <libintl.h>
# endif /* HAVE_LIBINTL_H */
#endif /* _LIBC */

#if USE_UNLOCKED_IO
# include "unlocked-io.h"
#endif /* USE_UNLOCKED_IO */

#ifndef _
# define _(String) String
#endif /* !_ */

/* If NULL, error will flush stdout, then print on stderr the program
 * name, a colon and a space. Otherwise, error will call this
 * function without parameters instead. */
void (*error_print_progname)(void);

/* This variable is incremented each time 'error' is called. */
unsigned int error_message_count;

#ifdef _LIBC
/* In the GNU C library, there is a predefined variable for this. */

# define program_name program_invocation_name
# include <errno.h>
# include <limits.h>
# include <libio/libioP.h>

/* In GNU libc we want do not want to use the common name 'error' directly.
 * Instead make it a weak alias. */
extern void __error(int status, int errnum, const char *message, ...)
     __attribute__((__format__(__printf__, 3, 4)));
extern void __error_at_line(int status, int errnum, const char *file_name,
							unsigned int line_number, const char *message, ...)
     __attribute__((__format__(__printf__, 5, 6)));
# define error __error
# define error_at_line __error_at_line

# include <libio/iolibio.h>
# define fflush(s) INTUSE(_IO_fflush) (s)
# undef putc
# define putc(c, fp) INTUSE(_IO_putc) (c, fp)

# include <bits/libc-lock.h>

#else /* not _LIBC: */

# include <fcntl.h>
# include <unistd.h>

# if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
/* Get declarations of the native Windows API functions.  */
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
/* Get _get_osfhandle.  */
#  include "msvc-nothrow.h"
# endif /* (_WIN32 || __WIN32__) && !__CYGWIN__ */

/* The gnulib override of fcntl is not needed in this file.  */
# undef fcntl

# if !HAVE_DECL_STRERROR_R
#  ifndef HAVE_DECL_STRERROR_R
"this configure-time declaration test was not run"
#  endif /* !HAVE_DECL_STRERROR_R */
#  if STRERROR_R_CHAR_P
char *strerror_r();
#  else
int strerror_r();
#  endif /* STRERROR_R_CHAR_P */
# endif /* !HAVE_DECL_STRERROR_R */

/* The calling program should define program_name and set it to the
 * name of the executing program.  */
extern char *program_name;

# if HAVE_STRERROR_R || defined strerror_r
#  define __strerror_r strerror_r
# endif /* HAVE_STRERROR_R || defined strerror_r */
#endif  /* not _LIBC */

#ifndef INLINECALL
# ifdef __STRICT_ANSI__
#  ifdef __inline__
#   define INLINECALL __inline__
#  else
#   if defined(__NO_INLINE__) && defined(__GNUC__) && !defined(__STDC__)
#    warning "INLINECALL will be unavailable when using the '-ansi' compiler flag"
#   endif /* __NO_INLINE__ && __GNUC__ && !__STDC__ */
#   define INLINECALL /* nothing */
#  endif /* __inline__ */
# else
#  define INLINECALL inline
# endif /* __STRICT_ANSI__ */
#endif /* !INLINECALL */

#if !defined(_LIBC) || (defined(_LIBC) && !_LIBC)
/* Return non-zero if FD is open.  */
static INLINECALL int is_open(int fd)
{
# if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
  /* On native Windows: The initial state of unassigned standard file
   * descriptors is that they are open but point to an INVALID_HANDLE_VALUE.
   * There is no fcntl & the gnulib replacement fcntl does not support F_GETFL */
  return (HANDLE)_get_osfhandle(fd) != INVALID_HANDLE_VALUE;
# else
#  ifndef F_GETFL
#   error Please port fcntl to your platform
#  endif /* !F_GETFL */
  return (0 <= fcntl(fd, F_GETFL));
# endif /* (_WIN32 || __WIN32__) && !__CYGWIN__ */
}
#endif /* !_LIBC */

static INLINECALL void flush_stdout(void)
{
  int should_do_fflush = 1;
#if !defined(_LIBC) || (defined(_LIBC) && !_LIBC)
  int stdout_fd;

# if defined(GNULIB_FREOPEN_SAFER) && GNULIB_FREOPEN_SAFER
  /* Use of gnulib's freopen-safer module normally ensures that
   *   fileno (stdout) == 1
   * whenever stdout is open. */
  stdout_fd = STDOUT_FILENO;
# else
  /* POSIX states that fileno (stdout) after fclose is unspecified. But in
   * practice it is not a problem, because stdout is statically allocated and
   * the fd of a FILE stream is stored as a field in its allocated memory. */
  stdout_fd = fileno(stdout);
# endif /* GNULIB_FREOPEN_SAFER */
  /* POSIX states that fflush(stdout) after fclose is unspecified; it
   * is safe in glibc, but not on all other platforms. fflush(NULL)
   * is always defined, but too draconian. */
  if ((0 <= stdout_fd) && is_open(stdout_fd)) {
	  /* do nothing (keep 'should_do_fflush' as 1) */ ;
  } else {
	  should_do_fflush = 0;
  }
#endif /* !_LIBC */
  if (should_do_fflush == 1) {
	  fflush(stdout);
  }
}

static void
print_errno_message(int errnum)
{
  char const *s;

#if defined HAVE_STRERROR_R || _LIBC
  char errbuf[1024];
# if (defined(STRERROR_R_CHAR_P) && STRERROR_R_CHAR_P) || (defined(_LIBC) && _LIBC)
  s = __strerror_r(errnum, errbuf, sizeof errbuf);
# else
	if (__strerror_r(errnum, errbuf, sizeof errbuf) == 0) {
		s = errbuf;
	} else {
		s = 0;
	}
# endif /* STRERROR_R_CHAR_P || _LIBC */
#else
  s = strerror(errnum);
#endif /* HAVE_STRERROR_R || _LIBC */

#if !defined(_LIBC) || (defined(_LIBC) && !_LIBC)
	if (! s) {
		s = _("Unknown system error");
	}
#endif /* !_LIBC */

#if defined(_LIBC) && _LIBC
  __fxprintf(NULL, ": %s", s);
#else
  fprintf(stderr, ": %s", s);
#endif /* _LIBC */
}

static void
#if defined(_GL_ATTRIBUTE_FORMAT_PRINTF_STANDARD) && defined(_GL_ARG_NONNULL)
_GL_ATTRIBUTE_FORMAT_PRINTF_STANDARD(3, 0) _GL_ARG_NONNULL((3))
#endif /* _GL_ATTRIBUTE_FORMAT_PRINTF_STANDARD && _GL_ARG_NONNULL */
error_tail(int status, int errnum, const char *message, va_list args)
{
  int should_do_vprintf = 1;
#if defined(_LIBC) && _LIBC
  if (_IO_fwide(stderr, 0) > 0) {
# define ALLOCA_LIMIT 2000
      size_t len = (strlen(message) + 1);
      wchar_t *wmessage = NULL;
      mbstate_t st;
      size_t res;
      const char *tmp;
      bool use_malloc = false;

      while (1) {
          if (__libc_use_alloca(len * sizeof(wchar_t))) {
            wmessage = (wchar_t *)alloca(len * sizeof(wchar_t));
          } else {
              if (!use_malloc) {
				  wmessage = NULL;
			  }

              wchar_t *p = (wchar_t *)realloc(wmessage,
											  (len * sizeof(wchar_t)));
              if (p == NULL) {
                  free (wmessage);
                  fputws_unlocked(L"out of memory\n", stderr);
                  return;
			  }
              wmessage = p;
              use_malloc = true;
		  }

          memset(&st, '\0', sizeof (st));
          tmp = message;

          res = mbsrtowcs(wmessage, &tmp, len, &st);
          if (res != len) {
			  break;
		  }

          if (__builtin_expect(len >= (SIZE_MAX / 2), 0)) {
              /* This really should not happen if everything is fine.  */
              res = (size_t)-1;
              break;
		  }

          len *= 2;
        }

      if (res == (size_t)-1) {
          /* The string cannot be converted.  */
          if (use_malloc) {
              free(wmessage);
              use_malloc = false;
		  }
          wmessage = (wchar_t *)L"???";
	  }

      __vfwprintf(stderr, wmessage, args);

	  if (use_malloc) {
		  free(wmessage);
	  }
	  should_do_vprintf = 0;
  } else {
	  should_do_vprintf = 1;
  }
#endif /* _LIBC */
  if (should_do_vprintf == 1) {
	  vfprintf(stderr, message, args);
  }
  va_end(args);

  ++error_message_count;
	if (errnum) {
		print_errno_message (errnum);
	}
#if defined(_LIBC) && _LIBC
  __fxprintf(NULL, "\n");
#else
  putc('\n', stderr);
#endif /* _LIBC */
  fflush(stderr);
	if (status) {
		exit (status);
	}
}


/* Print the program name and error message MESSAGE, which is a printf-style
 * format string with optional args.
 * If ERRNUM is nonzero, print its corresponding system error message.
 * Exit with status STATUS if it is nonzero.  */
void
error(int status, int errnum, const char *message, ...)
{
  va_list args;

#if defined _LIBC && defined __libc_ptf_call
  /* We do not want this call to be cut short by a thread
   * cancellation. Therefore disable cancellation for now. */
  int state = PTHREAD_CANCEL_ENABLE;
  __libc_ptf_call(pthread_setcancelstate, (PTHREAD_CANCEL_DISABLE, &state), 0);
#endif /* _LIBC && __libc_ptf_call */

  flush_stdout();
#ifdef _LIBC
  _IO_flockfile(stderr);
#endif /* _LIBC */
	if (error_print_progname) {
		(*error_print_progname)();
	} else {
#if defined(_LIBC) && _LIBC
      __fxprintf(NULL, "%s: ", program_name);
#else
      fprintf(stderr, "%s: ", program_name);
#endif /* _LIBC */
    }

  va_start(args, message);
  error_tail(status, errnum, message, args);

#ifdef _LIBC
  _IO_funlockfile(stderr);
# ifdef __libc_ptf_call
  __libc_ptf_call(pthread_setcancelstate, (state, NULL), 0);
# endif /* __libc_ptf_call */
#endif /* _LIBC */
}

/* Sometimes we want to have at most one error per line. This
 * variable controls whether this mode is selected or not.  */
int error_one_per_line;

void
error_at_line(int status, int errnum, const char *file_name,
			  unsigned int line_number, const char *message, ...)
{
  va_list args;

  if (error_one_per_line) {
      static const char *old_file_name;
      static unsigned int old_line_number;

      if ((old_line_number == line_number)
          && ((file_name == old_file_name)
              || (strcmp(old_file_name, file_name) == 0))) {
			  /* Simply return and print nothing.  */
			  return;
		  }

      old_file_name = file_name;
      old_line_number = line_number;
  }

#if defined _LIBC && defined __libc_ptf_call
  /* We do not want this call to be cut short by a thread
   * cancellation. Therefore disable cancellation for now. */
  int state = PTHREAD_CANCEL_ENABLE;
  __libc_ptf_call(pthread_setcancelstate, (PTHREAD_CANCEL_DISABLE, &state), 0);
#endif /* _LIBC && __libc_ptf_call */

  flush_stdout();
#ifdef _LIBC
  _IO_flockfile(stderr);
#endif /* _LIBC */
	if (error_print_progname) {
		(*error_print_progname)();
	} else {
#if defined(_LIBC) && _LIBC
      __fxprintf(NULL, "%s:", program_name);
#else
      fprintf(stderr, "%s:", program_name);
#endif /* _LIBC */
    }

#if defined(_LIBC) && _LIBC
  __fxprintf(NULL, ((file_name != NULL) ? "%s:%d: " : " "),
			 file_name, line_number);
#else
  if (file_name != NULL) {
    fprintf(stderr, "%s:%d: ", file_name, line_number);
  } else {
    fprintf(stderr, " ");
  }
#endif /* _LIBC */

  va_start(args, message);
  error_tail(status, errnum, message, args);

#ifdef _LIBC
  _IO_funlockfile(stderr);
# ifdef __libc_ptf_call
  __libc_ptf_call(pthread_setcancelstate, (state, NULL), 0);
# endif /* __libc_ptf_call */
#endif /* _LIBC */
}

#ifdef _LIBC
/* Make the weak alias.  */
# undef error
# undef error_at_line
weak_alias(__error, error)
weak_alias(__error_at_line, error_at_line)
#endif /* _LIBC */

/* EOF */
