# strndup.m4 serial 22
dnl# Copyright (C) 2002-2003, 2005-2012 Free Software Foundation, Inc.
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_STRNDUP],[
  dnl# Persuade glibc <string.h> to declare strndup() for us:
  AC_REQUIRE([AC_USE_SYSTEM_EXTENSIONS])

  AC_REQUIRE([AC_CANONICAL_HOST])dnl# for cross-compiles
  AC_REQUIRE([gl_HEADER_STRING_H_DEFAULTS])dnl
  AC_CHECK_DECLS_ONCE([strndup])dnl
  AC_CHECK_FUNCS_ONCE([strndup])dnl

  if test "x${ac_cv_have_decl_strndup}" = "xno"; then
    HAVE_DECL_STRNDUP=0
  fi

  if test "x${ac_cv_func_strndup}" = "xyes"; then
    HAVE_STRNDUP=1
    # AIX 4.3.3, AIX 5.1 have a func that fails to add a terminating '\0'.
    AC_CACHE_CHECK([for working strndup],[gl_cv_func_strndup_works],
      [AC_RUN_IFELSE([
         AC_LANG_PROGRAM([[#include <string.h>
                           #include <stdlib.h>]],[[
#if !HAVE_DECL_STRNDUP
  extern
  #ifdef __cplusplus
  "C"
  #endif /* __cplusplus */
  char *strndup(const char *, size_t);
#endif /* !HAVE_DECL_STRNDUP */
  char *s;
  s = strndup("some longer string", 15);
  free(s);
  s = strndup("shorter string", 13);
  return s[13] != '\0';]])],
         [gl_cv_func_strndup_works=yes],
         [gl_cv_func_strndup_works=no],
         [
changequote(,)dnl
          case ${host_os} in
            aix | aix[3-6]*) gl_cv_func_strndup_works="guessing no";;
            *)               gl_cv_func_strndup_works="guessing yes";;
          esac
changequote([,])dnl
         ])])
    case ${gl_cv_func_strndup_works} in
      *no) REPLACE_STRNDUP=1 ;;
    esac
  else
    HAVE_STRNDUP=0
  fi
])dnl
