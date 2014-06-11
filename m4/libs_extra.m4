dnl# libs_extra.m4: extra checks for libraries

AC_DEFUN([AC_LIB_CRYPT],[
  AC_CHECK_LIB([crypt],[crypt],[],[
    AC_CHECK_LIB([crypt],[main])dnl
  ])dnl
  AC_SEARCH_LIBS([crypt],[crypt System crypto c pub gnu iberty])dnl
])dnl
