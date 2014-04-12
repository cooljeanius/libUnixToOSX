dnl# AC_CHECK_FUNCS_IF_NOT_CACHED([FUNCTION...])
dnl# usage: just like AC_CHECK_FUNCS, except it skips the test entirely
dnl# if the value is already cached instead of printing a message.
AC_DEFUN([AC_CHECK_FUNCS_IF_NOT_CACHED],[
  m4_foreach_w([ac_FUNC_to_check],[$1],[
    cache_value_to_check="ac_func_`echo ac_FUNC_to_check`"
    if test "x${cache_value_to_check}" = "x"; then
      test -z "${cache_value_to_check}"
      AC_CHECK_HEADERS([ac_FUNC_to_check])
    fi
    unset cache_value_to_check
  ])
])
