dnl# combine all relocatability checks into a single macro:
AC_DEFUN([gl_RELOCATABILITY_UMBRELLA],[
  AC_REQUIRE([gl_RELOCATABLE_NOP])dnl
  AC_REQUIRE([gl_RELOCATABLE_LIBRARY])
  if test "x${RELOCATABLE}" = "xyes"; then
    AC_LIBOBJ([progreloc])dnl
    AC_LIBOBJ([relocatable])
  fi
  AC_REQUIRE_AUX_FILE([relocatable.sh.in])
  relocatable_sh=${ac_aux_dir}/relocatable.sh.in
  AC_SUBST_FILE([relocatable_sh])
  if test "x${gl_source_base}" = "x"; then
    if test -n "${srcdir}" && test -d ${srcdir}; then
      gl_SOURCE_BASE([${srcdir}])
      export gl_source_base=${srcdir}
    elif test -d . && test -e ./relocwrapper.c; then
      gl_SOURCE_BASE([.])
      export gl_source_base=.
    else
      test -z "${gl_source_base}"
      AC_MSG_WARN([not sure what to set "gl_source_base" to; will not be able to make programs relocatable])
    fi
  fi
  # do this as a separate conditional in case the value of "gl_source_base"
  # got changed by the previous conditional:
  if test "x${gl_source_base}" != "x"; then
    test ! -z "${gl_source_base}" || test -n "${gl_source_base}"
    gl_RELOCATABLE([${gl_source_base}])
  fi
])dnl
