# posix_fallocate.m4 serial 1
dnl# Copyright (C) 2014 Eric Gallager
dnl# Based on fallocate.m4, which is copyright (C) 2009 FSF
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_POSIX_FALLOCATE],[
  AC_REQUIRE([AC_TYPE_OFF_T])dnl
  AC_REQUIRE([AC_SYS_LARGEFILE])dnl
  AC_REQUIRE([gl_FUNC_FALLOCATE])dnl

  AC_CACHE_CHECK([for posix_fallocate],[gl_cv_func_posix_fallocate],[
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[
#include <fcntl.h>        /* posix_fallocate() declaration */
#include <limits.h>       /* CHAR_BITS declaration */
#ifndef CHAR_BITS
# define CHAR_BITS 8
#endif /* !CHAR_BITS */
    ]],[[posix_fallocate(-1, 0, (400000 / CHAR_BITS));]])],
                   [gl_cv_func_posix_fallocate=yes],
                   [gl_cv_func_posix_fallocate=no])dnl# end link test
  ])dnl# end cache check

  if test "x${gl_cv_func_posix_fallocate}" = "xyes"; then
    AC_DEFINE([HAVE_POSIX_FALLOCATE],[1],
              [Define to 1 if posix_fallocate() exists])dnl
    ## TODO: check if used
  else
    REPLACE_POSIX_FALLOCATE=1; AC_SUBST([REPLACE_POSIX_FALLOCATE])
    AC_LIBOBJ([posix_fallocate])dnl
    ## ok
  fi
])dnl
