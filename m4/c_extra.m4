dnl# c_extra.m4: extra checks for C compiler characteristics

AC_DEFUN([AC_C_CHARACTERISTICS_UMBRELLA],[
  AC_REQUIRE([AC_SYS_LARGEFILE])dnl
  AC_REQUIRE([AC_C_BIGENDIAN])dnl
  AC_REQUIRE([AC_C_CHAR_UNSIGNED])dnl
  AC_REQUIRE([AC_C_CONST])dnl
  dnl# might want to move these to be required now that we are inside a
  dnl# defun-ed macro:
  if test "x${ac_cv_c_inline}" = "x"; then
    test -z "${ac_cv_c_inline}"
    AC_C_INLINE
  elif test "x${gl_cv_c_inline_effective}" = "x"; then
    test -z "${gl_cv_c_inline_effective}"
    gl_INLINE
    gl_EXTERN_INLINE
  fi
  if test "x${ac_cv_c_restrict}" = "x"; then
    test -z "${ac_cv_c_restrict}"
    AC_C_RESTRICT
  fi
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
