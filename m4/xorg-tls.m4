dnl# Copyright (c) 2011 Apple Inc.
dnl#
dnl# Permission is hereby granted, free of charge, to any person obtaining
dnl# a copy of this software and associated documentation files
dnl# (the "Software"), to deal in the Software without restriction,
dnl# including without limitation the rights to use, copy, modify, merge,
dnl# publish, distribute, sublicense, and/or sell copies of the Software,
dnl# and to permit persons to whom the Software is furnished to do so,
dnl# subject to the following conditions:
dnl#
dnl# The above copyright notice and this permission notice
dnl# (including the next paragraph) shall be included in all copies or
dnl# substantial portions of the Software.
dnl#
dnl# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
dnl# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
dnl# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
dnl# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
dnl# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
dnl# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
dnl# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
dnl#
dnl# Authors: Jeremy Huddleston <jeremyhu@apple.com>

AC_DEFUN([XORG_TLS],[
  if test "x${STRICT_COMPILE}" = "xyes"; then 
    if test "x${STRICT_CFLAGS}" = "x"; then
      test -z "${STRICT_CFLAGS}"
      AC_MSG_NOTICE([need to set STRICT_CFLAGS for xorg-style checks])
      if test "x${WARN_CFLAGS}" != "x"; then
        test -n "${WARN_CFLAGS}" && export STRICT_CFLAGS="${WARN_CFLAGS}"
      else
        test -z "${WARN_CFLAGS}"
        dnl# just hardcode them instead of duplicating warning checks:
        export STRICT_CFLAGS="-pedantic -Werror -Werror=attributes"
      fi
    else
      test -n "${STRICT_CFLAGS}"
    fi
  else
    if test "x${STRICT_CFLAGS}" = "x"; then
      test -z "${STRICT_CFLAGS}" && export STRICT_CFLAGS="-pedantic"
    else
      test -n "${STRICT_CFLAGS}" && unset STRICT_CFLAGS
    fi
  fi
  AC_MSG_CHECKING([for thread local storage (TLS) support])
  AC_CACHE_VAL([ac_cv_tls],[
    ac_cv_tls=none
    keywords="__thread __declspec(thread)"
    for kw in ${keywords}; do
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[int ${kw} test;]],[[]])],
                        [ac_cv_tls=${kw}; break;])
    done
  ])
  AC_MSG_RESULT([${ac_cv_tls}])dnl

  if test "x${ac_cv_tls}" != "xnone"; then
    AC_MSG_CHECKING([for tls_model attribute support])
    AC_CACHE_VAL([ac_cv_tls_model],[
      save_CFLAGS="${CFLAGS}"
      CFLAGS="${CFLAGS} ${STRICT_CFLAGS}"
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
int ${ac_cv_tls} __attribute__((tls_model("initial-exec"))) test;]],[[]])],
                        [ac_cv_tls_model=yes],[ac_cv_tls_model=no])
      CFLAGS="${save_CFLAGS}"
    ])
    AC_MSG_RESULT([${ac_cv_tls_model}])dnl

    if test "x${ac_cv_tls_model}" = "xyes"; then
      xorg_tls=${ac_cv_tls}' __attribute__((tls_model("initial-exec")))'
    else
      xorg_tls=${ac_cv_tls}
    fi

    AC_DEFINE_UNQUOTED([TLS],[${xorg_tls}],
                       [The compiler-supported TLS storage class,
                        prefering initial-exec if tls_model is supported])
  fi
])dnl
