dnl# AC_CHECK_FUNCS_IF_NOT_CACHED([FUNCTION...])
dnl# usage: just like AC_CHECK_FUNCS, except it skips the test entirely
dnl# if the value is already cached instead of printing a message.
AC_DEFUN([AC_CHECK_FUNCS_IF_NOT_CACHED],[
  for ac_FUNC_to_check in $1; do
    cache_value_to_check=`${as_echo} "ac_cv_func_${ac_FUNC_to_check}" | ${as_tr_sh}`
    if eval test \"x\$"${cache_value_to_check}"\" = "x"; then
      test -z "${cache_value_to_check}"
      AC_CHECK_FUNCS([${ac_FUNC_to_check}])
    fi
    unset cache_value_to_check
  done
])
