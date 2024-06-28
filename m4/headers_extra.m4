dnl# AC_CHECK_HEADERS_IF_NOT_CACHED([HEADER-FILE...])
dnl# usage: just like AC_CHECK_HEADERS, except it skips the test entirely
dnl# if the value is already cached instead of printing a message.
AC_DEFUN([AC_CHECK_HEADERS_IF_NOT_CACHED],[
  AC_REQUIRE([AC_HEADER_STDC])
  for ac_HEADER_to_check in $1; do
    cache_value_to_check=`printf "%s\n" "ac_cv_header_${ac_HEADER_to_check}" | ${as_tr_sh}`
    if eval test \"x\$"${cache_value_to_check}"\" = "x"; then
      test -z "${cache_value_to_check}"
      AC_CHECK_HEADERS([${ac_HEADER_to_check}])
    fi
    unset cache_value_to_check
  done
])

AC_DEFUN([AC_HEADER_UMBRELLA],[
  AC_REQUIRE([AC_SYS_POSIX_TERMIOS])dnl
  AC_REQUIRE([AC_HEADER_ASSERT])dnl
  AC_REQUIRE([AC_HEADER_DIRENT])dnl
  AC_REQUIRE([AC_HEADER_STAT])dnl
  AC_REQUIRE([AC_CHECK_HEADER_STDBOOL])dnl
  AC_REQUIRE([AC_HEADER_STDBOOL])dnl
  AC_REQUIRE([AC_HEADER_STDC])dnl
  AC_REQUIRE([AC_HEADER_TIME])dnl
  AC_REQUIRE([AC_HEADER_TIOCGWINSZ])dnl
])dnl

m4_ifndef([gl_HEADER_STRING_H],[
AC_DEFUN([gl_HEADER_STRING_H],[
  AC_REQUIRE([gl_STRING_H])dnl
])dnl
])dnl

m4_ifndef([gl_HEADER_STRING_H_DEFAULTS],[
AC_DEFUN([gl_HEADER_STRING_H_DEFAULTS],[
  AC_REQUIRE([gl_STRING_H_REQUIRE_DEFAULTS])dnl
  AC_REQUIRE([gl_STRING_H_DEFAULTS])dnl
  ## assume this one check should be sufficient for all of them; will probably
  ## require some revision at some point:
  if test -z "${GNULIB_FFSL}"; then
  GNULIB_FFSL=0;        AC_SUBST([GNULIB_FFSL])
  GNULIB_FFSLL=0;       AC_SUBST([GNULIB_FFSLL])
  GNULIB_MEMCHR=0;      AC_SUBST([GNULIB_MEMCHR])
  GNULIB_MEMMEM=0;      AC_SUBST([GNULIB_MEMMEM])
  GNULIB_MEMPCPY=0;     AC_SUBST([GNULIB_MEMPCPY])
  GNULIB_MEMRCHR=0;     AC_SUBST([GNULIB_MEMRCHR])
  GNULIB_RAWMEMCHR=0;   AC_SUBST([GNULIB_RAWMEMCHR])
  GNULIB_STPCPY=0;      AC_SUBST([GNULIB_STPCPY])
  GNULIB_STPNCPY=0;     AC_SUBST([GNULIB_STPNCPY])
  GNULIB_STRCHRNUL=0;   AC_SUBST([GNULIB_STRCHRNUL])
  GNULIB_STRDUP=0;      AC_SUBST([GNULIB_STRDUP])
  GNULIB_STRNCAT=0;     AC_SUBST([GNULIB_STRNCAT])
  GNULIB_STRNDUP=0;     AC_SUBST([GNULIB_STRNDUP])
  GNULIB_STRNLEN=0;     AC_SUBST([GNULIB_STRNLEN])
  GNULIB_STRPBRK=0;     AC_SUBST([GNULIB_STRPBRK])
  GNULIB_STRSEP=0;      AC_SUBST([GNULIB_STRSEP])
  GNULIB_STRSTR=0;      AC_SUBST([GNULIB_STRSTR])
  GNULIB_STRCASESTR=0;  AC_SUBST([GNULIB_STRCASESTR])
  GNULIB_STRTOK_R=0;    AC_SUBST([GNULIB_STRTOK_R])
  GNULIB_MBSLEN=0;      AC_SUBST([GNULIB_MBSLEN])
  GNULIB_MBSNLEN=0;     AC_SUBST([GNULIB_MBSNLEN])
  GNULIB_MBSCHR=0;      AC_SUBST([GNULIB_MBSCHR])
  GNULIB_MBSRCHR=0;     AC_SUBST([GNULIB_MBSRCHR])
  GNULIB_MBSSTR=0;      AC_SUBST([GNULIB_MBSSTR])
  GNULIB_MBSCASECMP=0;  AC_SUBST([GNULIB_MBSCASECMP])
  GNULIB_MBSNCASECMP=0; AC_SUBST([GNULIB_MBSNCASECMP])
  GNULIB_MBSPCASECMP=0; AC_SUBST([GNULIB_MBSPCASECMP])
  GNULIB_MBSCASESTR=0;  AC_SUBST([GNULIB_MBSCASESTR])
  GNULIB_MBSCSPN=0;     AC_SUBST([GNULIB_MBSCSPN])
  GNULIB_MBSPBRK=0;     AC_SUBST([GNULIB_MBSPBRK])
  GNULIB_MBSSPN=0;      AC_SUBST([GNULIB_MBSSPN])
  GNULIB_MBSSEP=0;      AC_SUBST([GNULIB_MBSSEP])
  GNULIB_MBSTOK_R=0;    AC_SUBST([GNULIB_MBSTOK_R])
  GNULIB_STRERROR=0;    AC_SUBST([GNULIB_STRERROR])
  GNULIB_STRERROR_R=0;  AC_SUBST([GNULIB_STRERROR_R])
  GNULIB_STRSIGNAL=0;   AC_SUBST([GNULIB_STRSIGNAL])
  GNULIB_STRVERSCMP=0;  AC_SUBST([GNULIB_STRVERSCMP])
  fi
  if test "x${HAVE_MEMCHR}" = "x"; then
    test -z "${HAVE_MEMCHR}" && export HAVE_MEMCHR=1
    AC_SUBST([HAVE_MEMCHR])
  fi
])dnl
])dnl

m4_ifndef([gl_HEADER_TIME_H],[
AC_DEFUN([gl_HEADER_TIME_H],[
  AC_REQUIRE([gl_TIME_H])dnl
])dnl
])dnl

m4_ifndef([gl_HEADER_TIME_H_DEFAULTS],[
AC_DEFUN([gl_HEADER_TIME_H_DEFAULTS],[
  AC_REQUIRE([gl_TIME_H_REQUIRE_DEFAULTS])dnl
  AC_REQUIRE([gl_TIME_H_DEFAULTS])dnl
])dnl
])dnl

AC_DEFUN([gl_HEADER_UMBRELLA],[
  AC_REQUIRE([gl_DIRENT_H])dnl
  AC_REQUIRE([gl_DIRENT_SAFER])dnl
  gl_MODULE_INDICATOR([dirent-safer])dnl
  AC_REQUIRE([gl_HEADER_ERRNO_H])dnl
  AC_REQUIRE([gl_FCNTL_H])
  if test "x${NEXT_FCNTL_H}" = "x"; then
    test -z "${NEXT_FCNTL_H}" && export NEXT_FCNTL_H="<fcntl.h>"
    AC_SUBST([NEXT_FCNTL_H])
  fi
  if test "x${GNULIB_FCNTL}" = "x"; then
    test -z "${GNULIB_FCNTL}" && export GNULIB_FCNTL=0;
    AC_SUBST([GNULIB_FCNTL])
  fi
  if test "x${GNULIB_NONBLOCKING}" = "x"; then
    test -z "${GNULIB_NONBLOCKING}" && export GNULIB_NONBLOCKING=0;
    AC_SUBST([GNULIB_NONBLOCKING])
  fi
  if test "x${GNULIB_OPEN}" = "x"; then
    test -z "${GNULIB_OPEN}" && export GNULIB_OPEN=0;
    AC_SUBST([GNULIB_OPEN])
  fi
  if test "x${GNULIB_OPENAT}" = "x"; then
    test -z "${GNULIB_OPENAT}" && export GNULIB_OPENAT=0;
    AC_SUBST([GNULIB_OPENAT])
  fi
  if test "x${REPLACE_POSIX_FALLOCATE}" = "x"; then
    test -z "${REPLACE_POSIX_FALLOCATE}" && export REPLACE_POSIX_FALLOCATE=0
    AC_SUBST([REPLACE_POSIX_FALLOCATE])
  fi
  if test "x${REPLACE_POSIX_FALLOCATE64}" = "x"; then
    test -z "${REPLACE_POSIX_FALLOCATE64}" && export REPLACE_POSIX_FALLOCATE64=0
    AC_SUBST([REPLACE_POSIX_FALLOCATE64])
  fi
  AC_REQUIRE([gl_FCNTL_SAFER])dnl
  gl_MODULE_INDICATOR([fcntl-safer])dnl
  AC_REQUIRE([gl_FLOAT_H])dnl
  if test ${REPLACE_FLOAT_LDBL} = 1; then
    AC_LIBOBJ([float])
  fi
  if test ${REPLACE_ITOLD} = 1; then
    AC_LIBOBJ([itold])
  fi
  AC_REQUIRE([gl_GETOPT_CHECK_HEADERS])dnl
  AC_REQUIRE([gl_LOCALE_H])dnl
  AC_REQUIRE([gl_MATH_H])dnl
  AC_REQUIRE([gl_POLL_H])dnl
  AC_REQUIRE([gl_PTY_H])dnl
  AC_REQUIRE([gl_SIGNAL_H])dnl
  dnl# Define the substituted variable GNULIB_SIGNAL_H_SIGPIPE to 1.
  AC_REQUIRE([gl_SIGNAL_H_DEFAULTS])
  export GNULIB_SIGNAL_H_SIGPIPE=1
  AC_SUBST([GNULIB_SIGNAL_H_SIGPIPE])dnl
  AC_REQUIRE([gl_HEADER_STRING_H])dnl
  AC_REQUIRE([gl_HEADER_STRINGS_H])dnl
  AC_REQUIRE([AC_PROG_MKDIR_P])dnl
  AC_REQUIRE([gl_HEADER_SYS_SOCKET])dnl
  gl_SYS_SOCKET_MODULE_INDICATOR([recv])dnl
  AC_REQUIRE([gl_HEADER_SYS_STAT_H])dnl
  m4_ifdef([AM_STDBOOL_H],[
    AC_REQUIRE([AM_STDBOOL_H])dnl
  ],[
    AC_REQUIRE([AC_HEADER_STDBOOL])dnl# also "_CHECK"s it
    ## can now use this cache value:
    if test "x${ac_cv_header_stdbool_h}" = "xyes"; then
      STDBOOL_H=''
    else
      STDBOOL_H='stdbool.h'
    fi
    AC_SUBST([STDBOOL_H])dnl
    AM_CONDITIONAL([GL_GENERATE_STDBOOL_H],[test -n "${STDBOOL_H}"])dnl
  ])dnl
  AC_REQUIRE([gl_STDBOOL_H])dnl
  AC_REQUIRE([gl_STDDEF_H])dnl
  AC_REQUIRE([gl_STDINT_H])dnl
  AC_REQUIRE([gl_STDIO_H])dnl
  dnl# Define the substituted variables GNULIB_STDIO_H_NONBLOCKING and
  dnl# GNULIB_STDIO_H_SIGPIPE to 1.
  AC_REQUIRE([gl_STDIO_H_DEFAULTS])
  export GNULIB_STDIO_H_NONBLOCKING=1
  export GNULIB_STDIO_H_SIGPIPE=1
  AC_SUBST([GNULIB_STDIO_H_NONBLOCKING])dnl
  AC_SUBST([GNULIB_STDIO_H_SIGPIPE])dnl
  AC_REQUIRE([gl_TERMIOS_H])dnl
  AC_REQUIRE([gl_HEADER_TIME_H])dnl
  AC_REQUIRE([gl_UNISTD_H])dnl
  dnl# Define the substituted variables GNULIB_UNISTD_H_NONBLOCKING and
  dnl# GNULIB_UNISTD_H_SIGPIPE to 1.
  AC_REQUIRE([gl_UNISTD_H_DEFAULTS])
  export GNULIB_UNISTD_H_NONBLOCKING=1
  export GNULIB_UNISTD_H_SIGPIPE=1
  AC_SUBST([GNULIB_UNISTD_H_NONBLOCKING])dnl
  AC_SUBST([GNULIB_UNISTD_H_SIGPIPE])dnl
  AC_REQUIRE([gl_UNISTD_SAFER])dnl
  AC_REQUIRE([gl_WCHAR_H])dnl
  ## 1 thing from the stdlib.h module that changed:
  if test "x${REPLACE_REALLOC}" = "x"; then
    test -z "${REPLACE_REALLOC}" && export REPLACE_REALLOC=0
    AC_SUBST([REPLACE_REALLOC])
  fi
])dnl
