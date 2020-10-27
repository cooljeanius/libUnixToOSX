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
    else
      ## This defeats the entire purpose of the macro, but I temporarily need
      ## to debug something...
      echo "${cache_value_to_check} is already set!"
    fi
    unset cache_value_to_check
  done
  echo "done with this set of header checks"
  ## FIXME: something broke in here
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
  AC_REQUIRE([AM_STDBOOL_H])dnl
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
])dnl
