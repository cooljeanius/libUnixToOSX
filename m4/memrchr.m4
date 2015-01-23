# memrchr.m4 serial 11
dnl# Copyright (C) 2002-2003, 2005-2007, 2009-2012 Free Software Foundation
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_MEMRCHR],[
  dnl# Persuade glibc <string.h> to declare memrchr() for us:
  AC_REQUIRE([AC_USE_SYSTEM_EXTENSIONS])dnl

  AC_REQUIRE([gl_HEADER_STRING_H_DEFAULTS])dnl
  AC_CHECK_DECLS_ONCE([memrchr])dnl

  if test "x${ac_cv_have_decl_memrchr}" = "xno"; then
    HAVE_DECL_MEMRCHR=0
  fi

  AC_CHECK_FUNCS([memrchr])dnl
])dnl

# Prerequisites of lib/memrchr.c (none so far).
AC_DEFUN([gl_PREREQ_MEMRCHR],[:])
