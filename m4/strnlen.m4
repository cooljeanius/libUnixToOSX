# strnlen.m4 serial 14
dnl# Copyright (C) 2002-2003, 2005-2007, 2009-2012 Free Software Foundation
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_STRNLEN],[
  AC_REQUIRE([gl_HEADER_STRING_H_DEFAULTS])dnl

  dnl# Persuade glibc <string.h> to declare strnlen() for us:
  AC_REQUIRE([AC_USE_SYSTEM_EXTENSIONS])dnl

  AC_CHECK_DECLS_ONCE([strnlen])dnl

  if test "x${ac_cv_have_decl_strnlen}" = "xno"; then
    HAVE_DECL_STRNLEN=0
  else
    if test "x${ac_cv_func_strnlen_working}" = "x"; then
      test -z "${ac_cv_func_strnlen_working}"
      m4_pushdef([AC_LIBOBJ],[:])
      dnl# Note: AC_FUNC_STRNLEN does AC_LIBOBJ([strnlen]).
      AC_FUNC_STRNLEN
      m4_popdef([AC_LIBOBJ])
    fi
    if test "x${ac_cv_func_strnlen_working}" = "xno"; then
      REPLACE_STRNLEN=1
    fi
  fi
])dnl

# Prerequisites of lib/strnlen.c (none so far).
AC_DEFUN([gl_PREREQ_STRNLEN],[:])dnl
