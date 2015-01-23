# off_t.m4 serial 2
dnl# Copyright (C) 2012 Free Software Foundation, Inc.
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

dnl# Check whether to override the 'off_t' type.
dnl# Set WINDOWS_64_BIT_OFF_T.

AC_DEFUN([gl_TYPE_OFF_T],[
  m4_ifdef([gl_LARGEFILE],[
    AC_REQUIRE([gl_LARGEFILE])dnl
  ],[
    WINDOWS_64_BIT_OFF_T=0
  ])dnl
  AC_SUBST([WINDOWS_64_BIT_OFF_T])dnl
])dnl
