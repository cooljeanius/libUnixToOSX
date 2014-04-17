## ------------------------------- ##
## Check for function prototypes.  ##
## From Franc,ois Pinard           ##
## ------------------------------- ##

# Copyright 1996, 1997, 1998, 2000, 2001, 2002  FSF, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# serial 3

AC_DEFUN([AM_ANSI_C_PROTOTYPES],
[AC_REQUIRE([AM_REDONE_PROG_CC_STDC])
AC_REQUIRE([AC_PROG_CPP])
AC_REQUIRE([AC_OBJEXT])
AC_MSG_CHECKING([for ANSI C function prototypes])
if test "x${am_new_cv_prog_cc_stdc}" != "xno"; then
  AC_MSG_RESULT([yes])
  AC_DEFINE([PROTOTYPES],[1],
            [Define to 1 if compiler has ANSI C function prototypes])
  U=""
  ANSI2KNR=""
else
  AC_MSG_RESULT([no])
  U="_"
  ANSI2KNR="./ansi2knr"
fi
# Ensure some checks needed by ansi2knr itself.
AC_REQUIRE([AC_HEADER_STDC])
AC_CHECK_HEADERS_ONCE([ctype.h])
AC_SUBST([U])dnl
AC_SUBST([ANSI2KNR])dnl
])

AU_DEFUN([fp_C_PROTOTYPES],[AM_ANSI_C_PROTOTYPES])
