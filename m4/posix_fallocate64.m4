# posix_fallocate64.m4 serial 1
dnl# Copyright (C) 2014 Eric Gallager
dnl# Based on posix_fallocate.m4, which is in turn based on fallocate.m4,
dnl# which is copyright (C) 2009 Free Software Foundation, Inc.
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_POSIX_FALLOCATE64],[
  AC_REQUIRE([gl_FUNC_POSIX_FALLOCATE])dnl

  AC_CACHE_CHECK([for posix_fallocate64],[gl_cv_func_posix_fallocate64],[
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[
#include <fcntl.h>        /* posix_fallocate64() declaration */
#include <limits.h>       /* CHAR_BITS declaration */
#ifndef CHAR_BITS
# define CHAR_BITS 8
#endif /* !CHAR_BITS */
    ]],[[posix_fallocate64(-1, 0, ((400000 / CHAR_BITS) * 2));]])],
                   [gl_cv_func_posix_fallocate64=yes],
                   [gl_cv_func_posix_fallocate64=no])dnl# end link test
  ])dnl# end cache check

  if test "x${gl_cv_func_posix_fallocate64}" = "xyes"; then
    AC_DEFINE([HAVE_POSIX_FALLOCATE64],[1],
              [Define to 1 if posix_fallocate64() exists])dnl
    ## TODO: check if used
  else
    REPLACE_POSIX_FALLOCATE64=1; AC_SUBST([REPLACE_POSIX_FALLOCATE64])
    AC_LIBOBJ([posix_fallocate64])dnl
    ## ok
  fi
])dnl
