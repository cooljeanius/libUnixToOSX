dnl# types_extra.m4: extra checks for types

AC_DEFUN([AC_TYPES_UMBRELLA],[
  AC_REQUIRE([gl_INTTYPES_INCOMPLETE])dnl
  AC_REQUIRE([AC_TYPE_INT8_T])dnl
  AC_REQUIRE([AC_TYPE_INT16_T])dnl
  AC_REQUIRE([AC_TYPE_INT32_T])dnl
  AC_REQUIRE([AC_TYPE_INT64_T])dnl
  AC_REQUIRE([AC_TYPE_INTMAX_T])
  dnl# consider requiring instead, now that we are inside a defun-ed macro:
  if test "x${ac_cv_type_mode_t}" = "x"; then
    test -z "${ac_cv_type_mode_t}"
    AC_TYPE_MODE_T
  fi
  AC_REQUIRE([AC_TYPE_OFF_T])dnl
  AC_REQUIRE([gl_TYPE_OFF_T])dnl
  AC_REQUIRE([AC_TYPE_PID_T])dnl
  AC_REQUIRE([AC_TYPE_SIZE_T])dnl
  AC_REQUIRE([AC_TYPE_SSIZE_T])dnl
  AC_REQUIRE([gt_TYPE_SSIZE_T])dnl
  AC_REQUIRE([AC_TYPE_UID_T])dnl
  AC_REQUIRE([AC_TYPE_UINT8_T])dnl
  AC_REQUIRE([AC_TYPE_UINT16_T])dnl
  AC_REQUIRE([AC_TYPE_UINT32_T])dnl
  AC_REQUIRE([AC_TYPE_UINT64_T])dnl
  AC_REQUIRE([AC_TYPE_UINTMAX_T])
  dnl# consider requiring instead, now that we are inside a defun-ed macro:
  if test "x${gt_cv_c_wchar_t}" = "x"; then
    test -z "${gt_cv_c_wchar_t}"
    gt_TYPE_WCHAR_T
  else
    test ! -z "${gt_cv_c_wchar_t}" || test -n "${gt_cv_c_wchar_t}"
    AC_SUBST([gt_cv_c_wchar_t])
  fi
  if test "x${gt_cv_c_wint_t}" = "x"; then
    test -z "${gt_cv_c_wint_t}"
    gt_TYPE_WINT_T
  else
    test ! -z "${gt_cv_c_wint_t}" || test -n "${gt_cv_c_wint_t}"
    AC_SUBST([gt_cv_c_wint_t])
  fi
])dnl

AC_DEFUN([AC_STRUCTS_UMBRELLA],[
  AC_REQUIRE([AC_STRUCT_DIRENT_D_INO])dnl
  AC_REQUIRE([AC_STRUCT_DIRENT_D_TYPE])dnl
  AC_REQUIRE([AC_STRUCT_ST_BLOCKS])dnl
  AC_REQUIRE([AC_STRUCT_TM])dnl
  AC_REQUIRE([AC_STRUCT_TIMEZONE])dnl
])dnl
