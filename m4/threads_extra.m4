dnl# threads_extra.m4: extra thread-related macros

AC_DEFUN([gl_THREAD_UMBRELLA],[
  AC_REQUIRE([gl_THREADLIB_EARLY])dnl
  AC_REQUIRE([gl_LOCK])dnl
  AC_REQUIRE([gl_THREADLIB])dnl
  AC_REQUIRE([gl_THREAD])dnl
  AC_REQUIRE([gl_TLS])dnl
  AC_REQUIRE([XORG_TLS])dnl
])dnl
