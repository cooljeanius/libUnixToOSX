# thread.m4 serial 3
dnl# Copyright (C) 2008-2012 Free Software Foundation, Inc.
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_THREAD],[
  AC_REQUIRE([gl_THREADLIB])dnl
  AC_REQUIRE([AC_C_INLINE])dnl

  if test "x${gl_threads_api}" = "xposix"; then
    gl_save_LIBS="${LIBS}"
    LIBS="${LIBS} ${LIBMULTITHREAD}"
    AC_CHECK_FUNCS([pthread_atfork])
    LIBS="${gl_save_LIBS}"
  fi
])dnl
