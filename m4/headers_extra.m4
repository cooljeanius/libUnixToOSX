dnl# AC_CHECK_HEADERS_IF_NOT_CACHED([HEADER-FILE...])
dnl# usage: just like AC_CHECK_HEADERS, except it skips the test entirely
dnl# if the value is already cached instead of printing a message.
AC_DEFUN([AC_CHECK_HEADERS_IF_NOT_CACHED],[
  AC_REQUIRE([AC_HEADER_STDC])
  for ac_HEADER_to_check in $1; do
    cache_value_to_check=`${as_echo} "ac_cv_header_${ac_HEADER_to_check}" | ${as_tr_sh}`
    if eval test \"x\$"${cache_value_to_check}"\" = "x"; then
      test -z "${cache_value_to_check}"
      AC_CHECK_HEADERS([${ac_HEADER_to_check}])
    fi
    unset cache_value_to_check
  done
])
