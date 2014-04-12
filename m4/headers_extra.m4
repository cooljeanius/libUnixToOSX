dnl# AC_CHECK_HEADERS_IF_NOT_CACHED([HEADER-FILE...])
dnl# usage: just like AC_CHECK_HEADERS, except it skips the test entirely
dnl# if the value is already cached instead of printing a message.
AC_DEFUN([AC_CHECK_HEADERS_IF_NOT_CACHED],[
  m4_foreach_w([ac_HEADER_to_check],[$1],[
    cache_value_to_check="ac_cv_header_`echo ac_HEADER_to_check | tr \. _`"
    if test "x${cache_value_to_check}" = "x"; then
      test -z "${cache_value_to_check}"
      AC_CHECK_HEADERS([ac_HEADER_to_check])
    fi
    unset cache_value_to_check
  ])
])
