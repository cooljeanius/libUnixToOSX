# btowc.m4 serial 11
dnl# Copyright (C) 2008-2012 Free Software Foundation, Inc.
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_BTOWC],[
  AC_REQUIRE([gl_WCHAR_H_DEFAULTS])dnl
  dnl# Check whether <wchar.h> is usable at all, first. Otherwise the test
  dnl# program below may lead to an endless loop. See
  dnl# <http://gcc.gnu.org/bugzilla/show_bug.cgi?id=42440>.
  AC_REQUIRE([gl_WCHAR_H_INLINE_OK])dnl
  dnl# actually check stuff:
  AC_CHECK_FUNCS_ONCE([btowc])
  if test "x${ac_cv_func_btowc}" = "xno"; then
    HAVE_BTOWC=0
  else
    AC_REQUIRE([AC_PROG_CC])dnl
    AC_REQUIRE([gt_LOCALE_FR])dnl
    AC_REQUIRE([AC_CANONICAL_HOST]) dnl# for cross-compiles
    dnl# Cygwin 1.7.2 btowc('\0') is WEOF, not 0.
    AC_CACHE_CHECK([whether btowc(0) is correct],
      [gl_cv_func_btowc_nul],
      [AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <string.h>
/* Tru64 with Desktop Toolkit C has a bug: <stdio.h> must be included
 * before <wchar.h>.
 * BSD/OS 4.0.1 has a bug: <stddef.h>, <stdio.h> and <time.h> must be
 * included before <wchar.h>.  */
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>
int main(void)
{
  if (btowc('\0') != 0) {
    return 1;
  }
  return 0;
}
]])],[gl_cv_func_btowc_nul=yes],[gl_cv_func_btowc_nul=no],[
changequote(,)dnl
           case "${host_os}" in
                      # Guess no on Cygwin:
             cygwin*) gl_cv_func_btowc_nul="guessing no" ;;
                      # Guess yes otherwise:
             *)       gl_cv_func_btowc_nul="guessing yes" ;;
           esac
changequote([,])dnl
          ])dnl
      ])dnl

    dnl# IRIX 6.5 btowc(EOF) is 0xFF, not WEOF.
    AC_CACHE_CHECK([whether btowc(EOF) is correct],
      [gl_cv_func_btowc_eof],
      [dnl# Initial guess, used when cross-compiling or when no suitable
       dnl# locale is present.
changequote(,)dnl
        case "${host_os}" in
                 # Guess no on IRIX:
          irix*) gl_cv_func_btowc_eof="guessing no" ;;
                 # Guess yes otherwise:
          *)     gl_cv_func_btowc_eof="guessing yes" ;;
        esac
changequote([,])dnl
        if test "x${LOCALE_FR}" != "xnone"; then
          AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <locale.h>
#include <string.h>
/* Tru64 with Desktop Toolkit C has a bug: <stdio.h> must be included
 * before <wchar.h>.
 * BSD/OS 4.0.1 has a bug: <stddef.h>, <stdio.h> and <time.h> must be
 * included before <wchar.h>. */
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>
int main(void)
{
  if (setlocale(LC_ALL, "${LOCALE_FR}") != NULL) {
      if (btowc (EOF) != WEOF) {
        return 1;
      }
  }
  return 0;
}
]])],[gl_cv_func_btowc_eof=yes],[gl_cv_func_btowc_eof=no],[:])
        fi
      ])dnl

    case "${gl_cv_func_btowc_nul}" in
      *yes) ;;
      *) REPLACE_BTOWC=1 ;;
    esac
    case "${gl_cv_func_btowc_eof}" in
      *yes) ;;
      *) REPLACE_BTOWC=1 ;;
    esac
  fi
])dnl

# Prerequisites of lib/btowc.c.
AC_DEFUN([gl_PREREQ_BTOWC],[:])dnl
