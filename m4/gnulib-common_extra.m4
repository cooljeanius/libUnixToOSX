AC_DEFUN([gl_COMMON_JUST_BODY],[
  dnl# Use AC_REQUIRE here, so that the code is expanded once only:
  AC_REQUIRE([gl_COMMON_BODY])dnl
])dnl

AC_DEFUN([gl_COMMON_SEMI_UMBRELLA],[
  AC_REQUIRE([gl_COMMON_JUST_BODY])dnl
  AC_REQUIRE([gl_FEATURES_H])dnl
  AC_REQUIRE([gl_PROG_CC_C99])dnl
  AC_REQUIRE([gl_PROG_AR_RANLIB])dnl
  AC_REQUIRE([AC_PROG_MKDIR_P])dnl
  AC_REQUIRE([AC_C_RESTRICT])dnl
  AC_REQUIRE([gl_BIGENDIAN])dnl
])dnl
