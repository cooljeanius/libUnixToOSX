# errno_h.m4 serial 13
dnl# Copyright (C) 2004, 2006, 2008-2012 Free Software Foundation, Inc.
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN_ONCE([gl_HEADER_ERRNO_H],[
  AC_REQUIRE([AC_PROG_CC])dnl
  AC_REQUIRE([AC_PROG_CPP])dnl
  AC_REQUIRE([AC_PROG_EGREP])dnl
  AC_CACHE_CHECK([for complete errno.h],[gl_cv_header_errno_h_complete],[
    AC_EGREP_CPP([booboo],[
#include <errno.h>
#if !defined ETXTBSY
booboo
#endif /* !ETXTBSY */
#if !defined ENOMSG
booboo
#endif /* !ENOMSG */
#if !defined EIDRM
booboo
#endif /* !EIDRM */
#if !defined ENOLINK
booboo
#endif /* !ENOLINK */
#if !defined EPROTO
booboo
#endif /* !EPROTO */
#if !defined EMULTIHOP
booboo
#endif /* !EMULTIHOP */
#if !defined EBADMSG
booboo
#endif /* !EBADMSG */
#if !defined EOVERFLOW
booboo
#endif /* !EOVERFLOW */
#if !defined ENOTSUP
booboo
#endif /* !ENOTSUP */
#if !defined ENETRESET
booboo
#endif /* !ENETRESET */
#if !defined ECONNABORTED
booboo
#endif /* !ECONNABORTED */
#if !defined ESTALE
booboo
#endif /* !ESTALE */
#if !defined EDQUOT
booboo
#endif /* !EDQUOT */
#if !defined ECANCELED
booboo
#endif /* !ECANCELED */
#if !defined EOWNERDEAD
booboo
#endif /* !EOWNERDEAD */
#if !defined ENOTRECOVERABLE
booboo
#endif /* !ENOTRECOVERABLE */
      ],
      [gl_cv_header_errno_h_complete=no],
      [gl_cv_header_errno_h_complete=yes])
  ])
  if test "x${gl_cv_header_errno_h_complete}" = "xyes"; then
    ERRNO_H=''
  else
    gl_NEXT_HEADERS([errno.h])
    ERRNO_H='errno.h'
  fi
  AC_SUBST([ERRNO_H])dnl
  AM_CONDITIONAL([GL_GENERATE_ERRNO_H],[test -n "${ERRNO_H}"])dnl
  dnl# now that we are adding more of these, let us alphabetize them for
  dnl# easier reference:
  gl_REPLACE_ERRNO_VALUE([EBADMSG])dnl
  gl_REPLACE_ERRNO_VALUE([ECANCELED])dnl
  gl_REPLACE_ERRNO_VALUE([ECONNABORTED])dnl
  gl_REPLACE_ERRNO_VALUE([EDQUOT])dnl
  gl_REPLACE_ERRNO_VALUE([EIDRM])dnl
  gl_REPLACE_ERRNO_VALUE([EMULTIHOP])dnl
  gl_REPLACE_ERRNO_VALUE([ENETRESET])dnl
  gl_REPLACE_ERRNO_VALUE([ENOLINK])dnl
  gl_REPLACE_ERRNO_VALUE([ENOMSG])dnl
  gl_REPLACE_ERRNO_VALUE([ENOTSUP])dnl
  gl_REPLACE_ERRNO_VALUE([EOVERFLOW])dnl
  gl_REPLACE_ERRNO_VALUE([EPROTO])dnl
  gl_REPLACE_ERRNO_VALUE([ESOCK])dnl
  gl_REPLACE_ERRNO_VALUE([ESTALE])dnl
  gl_REPLACE_ERRNO_VALUE([ESTREAMS])dnl
  gl_REPLACE_ERRNO_VALUE([EWINSOCK])dnl
])dnl

# Assuming $1 = EOVERFLOW.
# The EOVERFLOW errno value ought to be defined in <errno.h>, according to
# POSIX. But some systems (like OpenBSD 4.0 or AIX 3) do NOT define it,
# and some systems (like OSF/1) define it when _XOPEN_SOURCE_EXTENDED
# is defined.
# Check for the value of EOVERFLOW.
# Set the variables EOVERFLOW_HIDDEN and EOVERFLOW_VALUE.
AC_DEFUN([gl_REPLACE_ERRNO_VALUE],[
  if test -n "${ERRNO_H}"; then
    AC_CACHE_CHECK([for ]$1[ value],[gl_cv_header_errno_h_]$1,[
      AC_EGREP_CPP([yes_alright],[
#include <errno.h>
#ifdef ]$1[
yes_alright
#endif /* ]$1[ */
      ],
      [gl_cv_header_errno_h_]$1[=yes],
      [gl_cv_header_errno_h_]$1[=no])
      if test "x${gl_cv_header_errno_h_]$1[}" = "xno"; then
        AC_EGREP_CPP([yes_mhm],[
#define _XOPEN_SOURCE_EXTENDED 1
#include <errno.h>
#ifdef ]$1[
yes_mhm
#endif /* ]$1[ */
          ],[gl_cv_header_errno_h_]$1[=hidden])
        if test "x${gl_cv_header_errno_h_]$1[}" = "xhidden"; then
          dnl# The macro exists but is hidden.
          dnl# Define it to the same value.
          AC_COMPUTE_INT([gl_cv_header_errno_h_]$1,$1,[
#define _XOPEN_SOURCE_EXTENDED 1
#include <errno.h>
/* The following two lines are a workaround against an autoconf-2.52 bug.  */
#include <stdio.h>
#include <stdlib.h>
])
        fi
      fi
    ])
    case ${gl_cv_header_errno_h_]$1[} in
      yes | no)
        ]$1[_HIDDEN=0; ]$1[_VALUE=""
        ;;
      *)
        ]$1[_HIDDEN=1; ]$1[_VALUE="${gl_cv_header_errno_h_]$1[}"
        ;;
    esac
    AC_SUBST($1[_HIDDEN])
    AC_SUBST($1[_VALUE])
  fi
])dnl

dnl# Autoconf >= 2.61 has AC_COMPUTE_INT built-in.
dnl# Remove this when we can assume autoconf >= 2.61.
m4_ifdef([AC_COMPUTE_INT],[],[
  AC_DEFUN([AC_COMPUTE_INT],[_AC_COMPUTE_INT([$2],[$1],[$3],[$4])])dnl
])dnl
