dnl# c_extra.m4: extra checks for C compiler characteristics

AC_DEFUN([AC_C_CHARACTERISTICS_UMBRELLA],[
  AC_REQUIRE([AC_SYS_LARGEFILE])dnl
  AC_REQUIRE([AC_C_BIGENDIAN])dnl
  AC_REQUIRE([AC_C_CHAR_UNSIGNED])dnl
  AC_REQUIRE([AC_C_CONST])dnl
  AC_REQUIRE([AC_C_INLINE])dnl
  AC_REQUIRE([gl_INLINE])dnl
  AC_REQUIRE([gl_EXTERN_INLINE])dnl
  AC_REQUIRE([AC_C_RESTRICT])dnl
  AC_REQUIRE([AC_C_PROTOTYPES])dnl
  AC_REQUIRE([AC_C_VOLATILE])dnl
])dnl

AC_DEFUN([gl_C_MISC],[
  AC_REQUIRE([gl_ASM_SYMBOL_PREFIX])dnl
  AC_REQUIRE([gl_CYCLE_CHECK])dnl
  AC_REQUIRE([gl_I_RING])dnl
  AC_REQUIRE([gl_MULTIARCH])dnl
  AC_REQUIRE([gl_NONBLOCKING_IO])dnl
  gl_FCNTL_MODULE_INDICATOR([nonblocking])dnl
  dnl# Define the C macro GNULIB_NONBLOCKING to 1.
  gl_MODULE_INDICATOR([nonblocking])dnl
  AC_REQUIRE([gl_SAME])dnl
  AC_REQUIRE([gl_SIGNAL_SIGPIPE])dnl
  dnl# Define the C macro GNULIB_SIGPIPE to 1.
  gl_MODULE_INDICATOR([sigpipe])dnl
])dnl
