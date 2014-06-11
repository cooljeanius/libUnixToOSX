dnl# programs_extra.m4: extra checks for programs

dnl# checks for compilers:
AC_DEFUN([AC_REQUIRE_COMPILER],[
  AC_REQUIRE([AC_PROG_CC])dnl
  AC_REQUIRE([AC_PROG_CC_C_O])dnl
  AC_REQUIRE([AM_PROG_CC_C_O])dnl
  AC_REQUIRE([AC_PROG_CPP])dnl
  AC_REQUIRE([XORG_PROG_RAWCPP])dnl
  AC_REQUIRE([AC_PROG_CXX])dnl
  AC_REQUIRE([AC_PROG_CXX_C_O])dnl
  AC_REQUIRE([AC_PROG_CXXCPP])dnl
  AC_REQUIRE([AC_PROG_GCC_TRADITIONAL])dnl
  AC_REQUIRE([AC_PROG_OBJC])dnl
  AC_REQUIRE([AC_PROG_OBJCPP])dnl
  AC_REQUIRE([AC_PROG_OBJCXX])dnl
  AC_REQUIRE([AC_PROG_OBJCXXCPP])dnl
  AC_REQUIRE([XORG_COMPILER_BRAND])dnl
])dnl

dnl# relocated from configure.ac:
AC_DEFUN([AC_REQUIRE_GREPS],[
  AC_REQUIRE([AC_PROG_GREP])dnl
  AC_REQUIRE([AC_PROG_EGREP])dnl
  AC_REQUIRE([AC_PROG_FGREP])dnl
])dnl
dnl# (now included as part of AC_TEXT_FILTER_PROGS below)

AC_DEFUN([AC_REQUIRE_INSTALL],[
  AC_REQUIRE([AC_PROG_INSTALL])dnl
  AC_REQUIRE([AM_PROG_INSTALL_SH])dnl
  AC_REQUIRE([AM_PROG_INSTALL_STRIP])dnl
  AC_REQUIRE([XORG_INSTALL])dnl
])dnl
dnl# (now included as part of AC_FILESYSTEM_OPERATION_PROGS below)

dnl# checks for programs that modify the filesystem:
AC_DEFUN([AC_FILESYSTEM_OPERATION_PROGS],[
  AC_REQUIRE([AC_REQUIRE_INSTALL])dnl
  AC_REQUIRE([AC_PROG_LN_S])dnl
  AC_REQUIRE([AC_PROG_MKDIR_P])dnl
])dnl

dnl# relocated from configure.ac:
AC_DEFUN([AC_REQUIRE_RANLIB],[
  AC_REQUIRE([AC_PROG_RANLIB])dnl
])dnl
dnl# (now included as part of AC_REQUIRE_RANLIB_ONCE below)

dnl# relocated from configure.ac (was not a macro there though):
AC_DEFUN([AC_REQUIRE_RANLIB_ONCE],[
  if test "x${RANLIB}" = "x" && test "x${ac_cv_prog_ac_ct_RANLIB}" = "x"; then
    test -z "${RANLIB}" && test -z "${ac_cv_prog_ac_ct_RANLIB}"
    AC_REQUIRE_RANLIB
  else
    test -n "${RANLIB}" || test -n "${ac_cv_prog_ac_ct_RANLIB}"
    test ! -z "${RANLIB}" && export RANLIB
    AC_SUBST([RANLIB])
  fi
])dnl

dnl# relocated from configure.ac:
AC_DEFUN([AC_REQUIRE_SED],[
  AC_REQUIRE([AC_PROG_SED])dnl
])dnl
dnl# (now included as part of AC_TEXT_FILTER_PROGS below)

dnl# checks for text filters:
AC_DEFUN([AC_TEXT_FILTER_PROGS],[
  AC_REQUIRE([AC_REQUIRE_GREPS])dnl
  AC_REQUIRE([AC_REQUIRE_SED])dnl
  AC_REQUIRE([AC_PROG_AWK])dnl
  AC_REQUIRE([XORG_WITH_M4])dnl
  AC_REQUIRE([XORG_CHANGELOG])dnl
])dnl

dnl# relocated from configure.ac (was not a macro there though):
AC_DEFUN([AC_PROG_LDD],[
  dnl# TODO: use "otool -L" as a substitute for "ldd" when applicable:
  AC_CHECK_PROG([LDD],[ldd])
  if test "x${LDD}" = "x" && test "x${ac_cv_prog_ac_ct_OBJDUMP}" = "x"; then
    test -z "${OBJDUMP}"
    gl_LDD
  fi
])dnl
dnl# (now included as part of AC_REQUIRE_LINKER below)

dnl# checks for linker characteristics:
AC_DEFUN([AC_REQUIRE_LINKER],[
  AC_REQUIRE([AC_PROG_LDD])dnl
  AC_REQUIRE([XORG_LD_WRAP])dnl
  AC_REQUIRE([LT_PATH_LD])dnl
])dnl

AC_DEFUN([AC_REQUIRE_LINT],[
  AC_REQUIRE([XORG_WITH_LINT])dnl
  AC_REQUIRE([XORG_LINT_LIBRARY])dnl
])dnl

dnl# relocated from configure.ac (was not a macro there though):
AC_DEFUN([AC_PROG_KERNEL_TOOLS],[
  dnl# FIXME: are all of these correct?
  AC_CHECK_PROG([LSMOD],[lsmod])
  if test "x${LSMOD}" = "x" || test "x${LSMOD}" = "xno"; then
    AC_CHECK_PROG([KEXTUTIL],[kextutil])dnl
    AC_CHECK_PROG([KEXTSTAT],[kextstat])dnl
    AC_CHECK_PROG([KEXTLOAD],[kextload])dnl
    AC_CHECK_PROG([KMODUNLOAD],[kmodunload])
  fi
])dnl
