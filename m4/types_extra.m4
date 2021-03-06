dnl# types_extra.m4: extra checks for types

AC_DEFUN([AC_TYPES_UMBRELLA],[
  AC_REQUIRE([gl_INTTYPES_INCOMPLETE])dnl
  AC_REQUIRE([AC_TYPE_INT8_T])dnl
  AC_REQUIRE([AC_TYPE_INT16_T])dnl
  AC_REQUIRE([AC_TYPE_INT32_T])dnl
  AC_REQUIRE([AC_TYPE_INT64_T])dnl
  AC_REQUIRE([AC_TYPE_INTMAX_T])dnl
  AC_REQUIRE([AC_TYPE_MODE_T])dnl
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
  AC_REQUIRE([AC_TYPE_UINTMAX_T])dnl
  AC_REQUIRE([gt_TYPE_WCHAR_T])dnl
  AC_REQUIRE([gt_TYPE_WINT_T])dnl
])dnl

AC_DEFUN([AC_STRUCTS_UMBRELLA],[
  AC_REQUIRE([AC_STRUCT_DIRENT_D_INO])dnl
  AC_REQUIRE([AC_STRUCT_DIRENT_D_TYPE])dnl
  AC_REQUIRE([AC_STRUCT_ST_BLOCKS])dnl
  AC_REQUIRE([AC_STRUCT_TM])dnl
  AC_REQUIRE([AC_STRUCT_TIMEZONE])dnl
])dnl
