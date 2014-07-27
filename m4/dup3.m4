# dup3.m4 serial 5
dnl# Copyright (C) 2009-2012 Free Software Foundation, Inc.
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_DUP3],[
  AC_REQUIRE([gl_UNISTD_H_DEFAULTS])dnl

  dnl# Persuade glibc <unistd.h> to declare dup3() for us:
  AC_REQUIRE([AC_USE_SYSTEM_EXTENSIONS])dnl

  AC_CHECK_FUNCS_ONCE([dup3])
  if test "x${ac_cv_func_dup3}" != "xyes"; then
    HAVE_DUP3=0
  fi

  dnl# Replace dup3() for supporting the gnulib-defined fchdir() function,
  dnl# to keep fchdir's bookkeeping up-to-date.
  m4_ifdef([gl_FUNC_FCHDIR],[
    gl_TEST_FCHDIR
    if test ${HAVE_FCHDIR} = 0; then
      dnl# We should already be replacing dup3 unconditionally, but just
      dnl# in case we are not actually doing so, force it here:
      if test ${HAVE_DUP3} = 1 && test ${REPLACE_DUP3} != 1; then
        REPLACE_DUP3=1
      fi
    fi
  ])dnl
])dnl
