# fallocate.m4 serial 2
dnl# Copyright (C) 2009 Free Software Foundation, Inc.
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_FALLOCATE],[
  AC_CHECK_HEADERS_ONCE([sys/falloc.h])dnl
  dnl# Remove this when glibc does NOT require it:
  AC_CHECK_HEADERS_ONCE([linux/falloc.h])dnl

  AC_REQUIRE([gl_FCNTL_H_DEFAULTS])dnl
  dnl# Persuade glibc <fcntl.h> to declare fallocate() for us:
  AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])dnl

  AC_CACHE_CHECK([for fallocate],[gl_cv_func_fallocate],[
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[
#include <fcntl.h>        /* fallocate() declaration */
#ifdef HAVE_LINUX_FALLOC_H
# include <linux/falloc.h> /* FALLOC_FL_KEEP_SIZE define */
#else
# ifndef FALLOC_FL_KEEP_SIZE
#  define FALLOC_FL_KEEP_SIZE 0x01
# endif /* !FALLOC_FL_KEEP_SIZE */
# if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#  warning "this conftest for fallocate wants to include <linux/falloc.h>"
# endif /* __GNUC__ && !__STRICT_ANSI__ */
#endif /* HAVE_LINUX_FALLOC_H */
    ]],[[fallocate(-1, FALLOC_FL_KEEP_SIZE, 0, 0);]])],
                   [gl_cv_func_fallocate=yes],
                   [gl_cv_func_fallocate=no])dnl# end link test
  ])dnl# end cache check

  if test "x${gl_cv_func_fallocate}" = "xyes"; then
    AC_DEFINE([HAVE_FALLOCATE],[1],[Defined if fallocate() exists])dnl
    ## TODO: check if used
  else
    AC_REQUIRE([AC_C_INLINE])dnl
    ## set up for replacing:
    REPLACE_FALLOCATE=1; AC_SUBST([REPLACE_FALLOCATE])
    AC_LIBOBJ([fallocate])dnl
    ## ok
  fi
])dnl
