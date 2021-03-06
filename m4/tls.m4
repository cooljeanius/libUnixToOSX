# tls.m4 serial 3 (gettext-0.18)
dnl# Copyright (C) 2005, 2008-2012 Free Software Foundation, Inc.
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

dnl# From Bruno Haible.

AC_DEFUN([gl_TLS],[
  AC_REQUIRE([gl_THREADLIB])dnl
])dnl

AC_DEFUN([gl_XORG_TLS],[
  AC_REQUIRE([gl_TLS])dnl
  AC_REQUIRE([XORG_TLS])dnl
])dnl
