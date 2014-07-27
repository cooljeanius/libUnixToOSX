#serial 19
dnl# Copyright (C) 2002, 2005, 2007, 2009-2012 Free Software Foundation
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_DUP2],[
  AC_REQUIRE([gl_UNISTD_H_DEFAULTS])dnl
  AC_REQUIRE([AC_CANONICAL_HOST])dnl
  m4_ifdef([gl_FUNC_DUP2_OBSOLETE],[
    AC_CHECK_FUNCS_ONCE([dup2])
    if test "x${ac_cv_func_dup2}" = "xno"; then
      HAVE_DUP2=0
    fi
  ],[
    AC_DEFINE([HAVE_DUP2],[1],
              [Define to 1 if you have the 'dup2' function.])
  ])
  if test ${HAVE_DUP2} = 1; then
    AC_CACHE_CHECK([whether dup2 works],[gl_cv_func_dup2_works],
      [AC_RUN_IFELSE([AC_LANG_PROGRAM([[
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
           ]],[[
int result = 0;
#ifdef FD_CLOEXEC
if (fcntl(1, F_SETFD, FD_CLOEXEC) == -1) {
  result |= 1;
}
#endif /* FD_CLOEXEC */
if (dup2(1, 1) == 0) {
  result |= 2;
}
#ifdef FD_CLOEXEC
if (fcntl(1, F_GETFD) != FD_CLOEXEC) {
  result |= 4;
}
#endif /* FD_CLOEXEC */
close(0);
if (dup2(0, 0) != -1) {
  result |= 8;
}
/* Many gnulib modules require POSIX conformance of EBADF: */
if ((dup2(2, 1000000) == -1) && (errno != EBADF)) {
  result |= 16;
}
return result;
           ]])dnl
        ],
        [gl_cv_func_dup2_works=yes],[gl_cv_func_dup2_works=no],
        [case "${host_os}" in
           mingw*) # on this platform, dup2 always returns 0 for success
             gl_cv_func_dup2_works="guessing no" ;;
           cygwin*) # on cygwin 1.5.x, dup2(1,1) returns 0
             gl_cv_func_dup2_works="guessing no" ;;
           linux*) # On linux between 2008-07-27 and 2009-05-11, dup2 of a
                   # closed fd may yield -EBADF instead of -1/errno=EBADF.
             gl_cv_func_dup2_works="guessing no" ;;
           freebsd*) # on FreeBSD 6.1, dup2(1,1000000) gives EMFILE,
                     # not EBADF.
             gl_cv_func_dup2_works="guessing no" ;;
           haiku*) # on Haiku alpha 2, dup2(1, 1) resets FD_CLOEXEC.
             gl_cv_func_dup2_works="guessing no" ;;
           *) gl_cv_func_dup2_works="guessing yes" ;;
         esac])
      ])
    case "${gl_cv_func_dup2_works}" in
      *yes) ;;
      *)
        REPLACE_DUP2=1
        ;;
    esac
  fi
  dnl# Replace dup2() for supporting the gnulib-defined fchdir() function,
  dnl# to keep fchdir's bookkeeping up-to-date.
  m4_ifdef([gl_FUNC_FCHDIR],[
    gl_TEST_FCHDIR
    if test ${HAVE_FCHDIR} = 0; then
      if test ${HAVE_DUP2} = 1; then
        REPLACE_DUP2=1
      fi
    fi
  ])dnl
])dnl

# Prerequisites of lib/dup2.c (none so far).
AC_DEFUN([gl_PREREQ_DUP2],[:])dnl
