dnl#                                               -*- Autoconf -*-
dnl# Process this file with autoconf to produce a configure script.

dnl# This configure.ac was originally only for building a standalone argp
dnl# library.
AC_PREREQ([2.69])
AC_INIT([argp],[standalone-1.3])
AC_CONFIG_SRCDIR([argp-ba.c])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_MACRO_DIR([../../m4]) dnl# inherit macros from parent project
AC_CONFIG_HEADERS([config.h])

# GNU libc defaults to supplying the ISO C library functions only. The
# _GNU_SOURCE define enables these extensions, in particular we want
# errno.h to declare program_invocation_name. Enable it on all
# systems; no problems have been reported with it so far.
AC_USE_SYSTEM_EXTENSIONS
	
# Checks for programs.
AC_PROG_RANLIB
AM_REDONE_PROG_CC_STDC
am_cv_prog_cc_stdc=${ac_cv_prog_cc_stdc}
if test "x${am_cv_prog_cc_stdc}" = "xno"; then
  AC_MSG_ERROR([the C compiler does NOT handle ANSI-C])
fi

# Checks for header files.
AC_CHECK_HEADERS([libintl.h limits.h malloc.h malloc/malloc.h stddef.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AM_ANSI_C_PROTOTYPES
gl_INLINE
gl_EXTERN_INLINE
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

LSH_GCC_ATTRIBUTES

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([strerror])

AC_REPLACE_FUNCS([mempcpy strndup strchrnul])
# keep autoscan happy:
if test "x" = "y"; then
  test -x `which autoscan`
  AC_CHECK_FUNCS([mempcpy strndup])
fi

dnl# usage:
dnl# ARGP_CHECK_FUNC([includes],[function-call],[if-found],[if-not-found])
AC_DEFUN([ARGP_CHECK_FUNC],
  [AS_VAR_PUSHDEF([ac_func], m4_substr([$2], 0, m4_index([$2], [(])))
   AS_VAR_PUSHDEF([ac_var], [ac_cv_func_call_]ac_func)
   AH_TEMPLATE(AS_TR_CPP(HAVE_[]ac_func),
               [Define to 1 if you have the `]ac_func[' function.])
   AC_CACHE_CHECK([for $2], ac_var,
     [AC_LINK_IFELSE([AC_LANG_PROGRAM([[$1]], [[$2]])],[AS_VAR_SET(ac_var, yes)],[AS_VAR_SET(ac_var, no)])])
   if test AS_VAR_GET(ac_var) = yes ; then
     ifelse([$3],,
	    [AC_DEFINE_UNQUOTED(AS_TR_CPP(HAVE_[]ac_func))],
	    [$3
])
   else
     ifelse([$4],, true, [$4])
   fi
   AS_VAR_POPDEF([ac_var])
   AS_VAR_POPDEF([ac_func])
   ])

# At least on freebsd, putc_unlocked is a macro, so the standard
# AC_CHECK_FUNCS does NOT work well.
ARGP_CHECK_FUNC([#include <stdio.h>],[putc_unlocked('x', stdout)])

AC_CHECK_FUNCS([flockfile])
AC_CHECK_FUNCS([fputs_unlocked fwrite_unlocked])

# Used only by argp-test.c, so do NOT use AC_REPLACE_FUNCS.
AC_CHECK_FUNCS([strdup asprintf])

# Other funcs that should just be "CHECK"ed instead of "REPLACE"d:
AC_CHECK_FUNCS([isascii memchr memmove memset strchr strrchr])

AC_CHECK_DECLS([program_invocation_name, program_invocation_short_name],
               [],[],[[#include <errno.h>]])

# Set these flags *last*, or else the test programs will NOT compile:
if test "x${GCC}" = "xyes"; then
  # Using -ggdb3 makes (some versions of) Redhat's gcc-2.96 dump core:
  if "${CC}" --version | grep '^2\.96$' 1>/dev/null 2>&1; then
    true
  else
    CFLAGS="${CFLAGS} -ggdb3"
  fi
  CFLAGS="${CFLAGS} -Wall -W \
 -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes \
 -Waggregate-return \
 -Wpointer-arith -Wbad-function-cast -Wnested-externs"
fi

CPPFLAGS="${CPPFLAGS} -I${srcdir}"

AC_CONFIG_FILES([Makefile testsuite/Makefile])
AC_OUTPUT
