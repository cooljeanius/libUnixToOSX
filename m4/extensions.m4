dnl# note: line with ser-num needs to be just a regular shell comment
dnl# (i.e. no 'dnl'); else aclocal will fail to see it and overwrite this:
# serial 14  -*- Autoconf -*-
# Enable extensions on systems that normally disable them.

# Copyright (C) 2003, 2006-2014 Free Software Foundation, Inc.
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This definition of AC_USE_SYSTEM_EXTENSIONS is stolen from git
# Autoconf.  Perhaps we can remove this once we can assume Autoconf
# 2.70 or later everywhere, but since Autoconf mutates rapidly
# enough in this area it is likely we will need to redefine
# AC_USE_SYSTEM_EXTENSIONS for quite some time.

# If autoconf reports a warning
#     warning: AC_COMPILE_IFELSE was called before AC_USE_SYSTEM_EXTENSIONS
# or  warning: AC_RUN_IFELSE was called before AC_USE_SYSTEM_EXTENSIONS
# the fix is
#   1) to ensure that AC_USE_SYSTEM_EXTENSIONS is never directly invoked
#      but always AC_REQUIREd,
#   2) to ensure that for each occurrence of
#        AC_REQUIRE([AC_USE_SYSTEM_EXTENSIONS])
#      or
#        AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])
#      the corresponding gnulib module description has 'extensions' among
#      its dependencies. This will ensure that the gl_USE_SYSTEM_EXTENSIONS
#      invocation occurs in gl_EARLY, not in gl_INIT.

# AC_USE_SYSTEM_EXTENSIONS
# ------------------------
# Enable extensions on systems that normally disable them,
# typically due to standards-conformance issues.
#
# Remember that #undef in AH_VERBATIM gets replaced with #define by
# AC_DEFINE.  The goal here is to define all known feature-enabling
# macros, then, if reports of conflicts are made, disable macros that
# cause problems on some platforms (such as __EXTENSIONS__).
AC_DEFUN_ONCE([AC_USE_SYSTEM_EXTENSIONS],[
AC_BEFORE([$0],[AC_COMPILE_IFELSE])dnl
AC_BEFORE([$0],[AC_RUN_IFELSE])dnl

  unset ac_cv_header_minix_config_h
  AC_CHECK_HEADERS([minix/config.h],[MINIX=yes],[MINIX=""])
  if test "x${MINIX}" = "xyes"; then
    AC_DEFINE([_POSIX_SOURCE],[1],
      [Define to 1 if you need to in order for 'stat' and other
       things to work.])dnl
    AC_DEFINE([_POSIX_1_SOURCE],[2],
      [Define to 2 if the system does not provide POSIX.1 features
       except with this defined.])dnl
    AC_DEFINE([_MINIX],[1],
      [Define to 1 if on MINIX.])dnl
    AC_DEFINE([_NETBSD_SOURCE],[1],
      [Define to 1 to make NetBSD features available. MINIX 3 needs this.])
  fi

dnl# Use a different key than __EXTENSIONS__, as that name broke existing
dnl# configure.ac when using autoheader 2.62.
  AH_VERBATIM([USE_SYSTEM_EXTENSIONS],[
/* Enable extensions on AIX 3, Interix: */
#ifndef _ALL_SOURCE
# undef _ALL_SOURCE
#endif /* !_ALL_SOURCE */
/* Enable general extensions on OS X: */
#ifndef _DARWIN_C_SOURCE
# undef _DARWIN_C_SOURCE
#endif /* !_DARWIN_C_SOURCE */
/* Enable GNU extensions on systems that have them: */
#ifndef _GNU_SOURCE
# undef _GNU_SOURCE
#endif /* !_GNU_SOURCE */
/* Enable threading extensions on Solaris: */
#ifndef _POSIX_PTHREAD_SEMANTICS
# undef _POSIX_PTHREAD_SEMANTICS
#endif /* !_POSIX_PTHREAD_SEMANTICS */
/* Enable extensions on HP NonStop: */
#ifndef _TANDEM_SOURCE
# undef _TANDEM_SOURCE
#endif /* !_TANDEM_SOURCE */
/* Enable X/Open extensions if necessary.  HP-UX 11.11 defines
 * mbstate_t only if _XOPEN_SOURCE is defined to 500, regardless of
 * whether compiling with -Ae or -D_HPUX_SOURCE=1.  */
#ifndef _XOPEN_SOURCE
# undef _XOPEN_SOURCE
#endif /* !_XOPEN_SOURCE */
/* Enable general extensions on Solaris: */
#ifndef __EXTENSIONS__
# undef __EXTENSIONS__
#endif /* !__EXTENSIONS__ */
  ])dnl
  AC_CACHE_CHECK([whether it is safe to define __EXTENSIONS__],
    [ac_cv_safe_to_define___extensions__],
    [AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM([[
#         define __EXTENSIONS__ 1
          ]AC_INCLUDES_DEFAULT])],
       [ac_cv_safe_to_define___extensions__=yes],
       [ac_cv_safe_to_define___extensions__=no]) dnl# end compile test
  ]) dnl# end cache check

  test "x${ac_cv_safe_to_define___extensions__}" = "xyes" &&
    AC_DEFINE([__EXTENSIONS__])
  AC_DEFINE([_ALL_SOURCE])dnl
  AC_DEFINE([_DARWIN_C_SOURCE])dnl
  AC_DEFINE([_GNU_SOURCE])dnl
  AC_DEFINE([_POSIX_PTHREAD_SEMANTICS])dnl
  AC_DEFINE([_TANDEM_SOURCE])dnl
  AC_CHECK_HEADERS_ONCE([wchar.h])dnl
  AC_CHECK_TYPES([mbstate_t])dnl
  AC_CACHE_CHECK([whether _XOPEN_SOURCE should be defined],
    [ac_cv_should_define__xopen_source],
    [ac_cv_should_define__xopen_source=no
     AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM([[
          #include <wchar.h>
          mbstate_t x;]])],
       [],
       [AC_COMPILE_IFELSE(
          [AC_LANG_PROGRAM([[
             #define _XOPEN_SOURCE 500
             #include <wchar.h>
             mbstate_t x;]])],
          [ac_cv_should_define__xopen_source=yes]) dnl# end of 2nd comptest
       ]) dnl# end of 1st comptest
  ])dnl# end of cache check

  test "x$ac_cv_should_define__xopen_source" = "xyes" &&
    AC_DEFINE([_XOPEN_SOURCE],[500])
])dnl# AC_USE_SYSTEM_EXTENSIONS

# AC_GNU_SOURCE
# --------------
AC_DEFUN([AC_GNU_SOURCE],[
AH_VERBATIM([_GNU_SOURCE],[
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# undef _GNU_SOURCE
#endif /* !_GNU_SOURCE */
])dnl
AC_BEFORE([$0],[AC_COMPILE_IFELSE])dnl
AC_BEFORE([$0],[AC_RUN_IFELSE])dnl
AC_DEFINE([_GNU_SOURCE])dnl
])

# gl_USE_SYSTEM_EXTENSIONS
# ------------------------
# Enable extensions on systems that normally disable them,
# typically due to standards-conformance issues.
AC_DEFUN_ONCE([gl_USE_SYSTEM_EXTENSIONS],[
  dnl# Require this macro before AC_USE_SYSTEM_EXTENSIONS.
  dnl# gnulib does not need it. But if it gets required by third-party
  dnl# macros after AC_USE_SYSTEM_EXTENSIONS is required,
  dnl# autoconf 2.62..2.63 emit a warning:
  dnl# "AC_COMPILE_IFELSE was called before AC_USE_SYSTEM_EXTENSIONS".
  dnl# Note: We can do this only for one of the macros out of AC_AIX,
  dnl# AC_GNU_SOURCE, and AC_MINIX. If people still use AC_AIX or AC_MINIX,
  dnl# then they are out of luck.
  AC_REQUIRE([AC_GNU_SOURCE])dnl
  dnl# Now we can actually do AC_USE_SYSTEM_EXTENSIONS here:
  AC_REQUIRE([AC_USE_SYSTEM_EXTENSIONS])dnl
  dnl# throw these in as well:
  AC_REQUIRE([AC_EXEEXT])dnl
  AC_REQUIRE([AC_OBJEXT])dnl
])dnl
