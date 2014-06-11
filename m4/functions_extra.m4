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

dnl# keep all umbrella macros in alphabetical order, please.

dnl# checks related to alloca():
AC_DEFUN([AC_ALLOCA_UMBRELLA],[
  AC_REQUIRE([AC_FUNC_ALLOCA])dnl
  AC_REQUIRE([gl_FUNC_ALLOCA])dnl
])dnl

dnl# checks related to allocation functions:
AC_DEFUN([gl_ALLOC_FUNCS_UMBRELLA],[
  AC_REQUIRE([AC_ALLOCA_UMBRELLA])dnl
  AC_REQUIRE([gl_MALLOC_UMBRELLA])dnl
  AC_REQUIRE([gl_REALLOC_UMBRELLA])dnl
  AC_REQUIRE([gl_XALLOC])dnl
])dnl

dnl# checks related to areadlinkat():
AC_DEFUN([AC_FUNC_AREADLINKAT],[
  AC_CHECK_FUNCS_ONCE([areadlinkat])dnl
  gl_MODULE_INDICATOR([areadlinkat])dnl
  gl_MODULE_INDICATOR([areadlinkat-with-size])dnl
])dnl

dnl# checks related to btowc():
AC_DEFUN([gl_BTOWC_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_BTOWC])
  if test ${HAVE_BTOWC} = 0 || test ${REPLACE_BTOWC} = 1; then
    AC_LIBOBJ([btowc])dnl
    gl_PREREQ_BTOWC
  fi
  gl_WCHAR_MODULE_INDICATOR([btowc])dnl
])dnl

dnl# checks related to canonicalizing:
AC_DEFUN([gl_CANONICALIZE_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_CANONICALIZE_FILENAME_MODE])dnl
  gl_MODULE_INDICATOR([canonicalize])dnl
  gl_MODULE_INDICATOR_FOR_TESTS([canonicalize])dnl
  gl_MODULE_INDICATOR([canonicalize_file_name])dnl
  gl_STDLIB_MODULE_INDICATOR([canonicalize_file_name])dnl
  AC_REQUIRE([gl_CANONICALIZE_LGPL])
  if test ${HAVE_CANONICALIZE_FILE_NAME} = 0 || test ${REPLACE_CANONICALIZE_FILE_NAME} = 1; then
    AC_LIBOBJ([canonicalize-lgpl])
  fi
  gl_MODULE_INDICATOR([canonicalize-lgpl])dnl
  dnl# "canonicalize_file_name" is already indicated above
  gl_STDLIB_MODULE_INDICATOR([realpath])dnl
  AC_REQUIRE([gl_CANONICALIZE_LGPL_SEPARATE])dnl
])dnl

dnl# checks for changing directories:
AC_DEFUN([gl_CHDIR_UMBRELLA],[
  gl_UNISTD_MODULE_INDICATOR([chdir])dnl
  AC_REQUIRE([gl_FUNC_CHDIR_LONG])
  if test "x${gl_cv_have_arbitrary_file_name_length_limit}" = "xyes"; then
    AC_LIBOBJ([chdir-long])dnl
    gl_PREREQ_CHDIR_LONG
  fi
  AC_REQUIRE([gl_CHDIR_SAFER])dnl
  AC_REQUIRE([gl_FUNC_FCHDIR])dnl
  gl_UNISTD_MODULE_INDICATOR([fchdir])dnl
])dnl

dnl# checks related to chown-ing:
AC_DEFUN([gl_CHOWN_UMBRELLA],[
  AC_REQUIRE([AC_FUNC_CHOWN])dnl
  AC_REQUIRE([gl_FUNC_CHOWN])
  if test ${HAVE_CHOWN} = 0 || test ${REPLACE_CHOWN} = 1; then
    AC_LIBOBJ([chown])
  fi
  if test ${REPLACE_CHOWN} = 1 && test "x${ac_cv_func_fchown}" = "xno"; then
    AC_LIBOBJ([fchown-stub])
  fi
  gl_UNISTD_MODULE_INDICATOR([chown])dnl
  AC_REQUIRE([gl_FCHOWNAT_UMBRELLA])dnl
])dnl

dnl# checks related to closing things:
AC_DEFUN([gl_CLOSE_UMBRELLA],[
  gl_MODULE_INDICATOR_FOR_TESTS([cloexec])dnl
  AC_REQUIRE([gl_FUNC_CLOSE])
  if test ${REPLACE_CLOSE} = 1; then
    AC_LIBOBJ([close])
  fi
  gl_UNISTD_MODULE_INDICATOR([close])dnl
  AC_REQUIRE([AC_FUNC_CLOSEDIR_VOID])dnl
  AC_REQUIRE([gl_CLOSEOUT])dnl
  AC_REQUIRE([gl_CLOSE_STREAM])dnl
  gl_MODULE_INDICATOR([close-stream])dnl
  AC_REQUIRE([gl_FUNC_FCLOSE])
  if test ${REPLACE_FCLOSE} = 1; then
    AC_LIBOBJ([fclose])
  fi
  gl_STDIO_MODULE_INDICATOR([fclose])dnl
])dnl

dnl# checks for functions related to the current working directory:
AC_DEFUN([gl_CWD_UMBRELLA],[
  AC_REQUIRE([gl_SAVE_CWD])dnl
  AC_REQUIRE([gl_XGETCWD])dnl
])dnl

dnl# checks related to the dirname:
AC_DEFUN([gl_DIRNAME_UMBRELLA],[
  AC_REQUIRE([gl_DIRNAME])dnl
  AC_REQUIRE([gl_DIRNAME_LGPL])dnl
  gl_MODULE_INDICATOR([dirname])dnl
])dnl

dnl# checks for the dup() family of functions:
AC_DEFUN([gl_DUP_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_DUP])
  if test ${REPLACE_DUP} = 1; then
    AC_LIBOBJ([dup])dnl
    gl_PREREQ_DUP
  fi
  gl_UNISTD_MODULE_INDICATOR([dup])dnl
  AC_REQUIRE([gl_FUNC_DUP2])
  if test ${HAVE_DUP2} = 0 || test ${REPLACE_DUP2} = 1; then
    AC_LIBOBJ([dup2])dnl
    gl_PREREQ_DUP2
  fi
  gl_UNISTD_MODULE_INDICATOR([dup2])dnl
  AC_REQUIRE([gl_FUNC_DUP2_OBSOLETE])dnl
  AC_REQUIRE([gl_FUNC_DUP3])dnl
  gl_UNISTD_MODULE_INDICATOR([dup3])dnl
])dnl

dnl# checks for funcs related to the environment
AC_DEFUN([gl_ENVIRON_FUNCS_UMBRELLA],[
  AC_REQUIRE([gl_ENVIRON])dnl
  gl_UNISTD_MODULE_INDICATOR([environ])
  test -x "`which env`"
  AC_REQUIRE([gl_FUNC_SETENV])
  if test ${HAVE_SETENV} = 0 || test ${REPLACE_SETENV} = 1; then
    AC_LIBOBJ([setenv])
  fi
  gl_STDLIB_MODULE_INDICATOR([setenv])dnl
  AC_REQUIRE([gl_FUNC_SETENV_SEPARATE])dnl
])dnl

dnl# checks for funcs related to errors:
AC_DEFUN([gl_ERROR_UMBRELLA],[
  dnl# consider moving to requiring now that we are in a defun-ed macro:
  if test "x${ac_cv_lib_error_at_line}" = "x"; then
    test -z "${ac_cv_lib_error_at_line}"
    AC_FUNC_ERROR_AT_LINE
  fi
  AC_REQUIRE([gl_ERROR])
  if test "x${ac_cv_lib_error_at_line}" = "xno"; then
    AC_LIBOBJ([error])dnl
    gl_PREREQ_ERROR
  fi
])dnl

dnl# checks related to fchmodat():
AC_DEFUN([gl_FCHMODAT_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_FCHMODAT])
  if test $HAVE_FCHMODAT = 0; then
    AC_LIBOBJ([fchmodat])
  fi
  AC_REQUIRE([AC_C_INLINE]) dnl# because 'inline' is used in "openat.h"
  gl_MODULE_INDICATOR([fchmodat]) dnl# for "openat.h"
  gl_SYS_STAT_MODULE_INDICATOR([fchmodat])dnl
])dnl

dnl# checks related to fchownat():
AC_DEFUN([gl_FCHOWNAT_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_FCHOWNAT])
  if test ${HAVE_FCHOWNAT} = 0 || test ${REPLACE_FCHOWNAT} = 1; then
    AC_LIBOBJ([fchownat])
  fi
  AC_REQUIRE([AC_C_INLINE]) dnl# because 'inline' is used in "openat.h"
  gl_MODULE_INDICATOR([fchownat]) dnl# for "openat.h"
  gl_UNISTD_MODULE_INDICATOR([fchownat])dnl
])dnl

dnl# checks related to fflush():
AC_DEFUN([gl_FFLUSH_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_FFLUSH])
  if test ${REPLACE_FFLUSH} = 1; then
    AC_LIBOBJ([fflush])dnl
    gl_PREREQ_FFLUSH
  fi
  gl_MODULE_INDICATOR([fflush])dnl
  gl_STDIO_MODULE_INDICATOR([fflush])dnl
])dnl

dnl# checks related to file name functions:
AC_DEFUN([gl_FILE_NAME_UMBRELLA],[
  AC_REQUIRE([gl_FILE_NAME_CONCAT])dnl
  AC_REQUIRE([gl_FILE_NAME_CONCAT_LGPL])dnl
  gl_MODULE_INDICATOR([filenamecat])dnl
])dnl

dnl# checks related to fork():
AC_DEFUN([AC_FORK_UMBRELLA],[
  AC_REQUIRE([AC_FUNC_FORK])dnl
  AC_REQUIRE([gl_FUNC_FORKPTY])dnl
])dnl

dnl# checks related to __fpending():
AC_DEFUN([gl_FPENDING_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_FPENDING])
  if test "x${ac_cv_func___fpending}" = "xno"; then
    AC_LIBOBJ([fpending])dnl
    gl_PREREQ_FPENDING
  fi
])dnl

dnl# checks related to fread():
AC_DEFUN([gl_FREAD_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_FREADAHEAD])
  if test "x${ac_cv_func___freadahead}" = "xno"; then
    AC_LIBOBJ([freadahead])
  fi
  AC_REQUIRE([gl_FUNC_FREADPTR])
  if test "x${ac_cv_func___freadptr}" = "xno"; then
    AC_LIBOBJ([freadptr])
  fi
  AC_REQUIRE([gl_FUNC_FREADSEEK])dnl
  AC_REQUIRE([AC_FUNC_FSEEKO])dnl
])dnl

dnl# checks related to getdelim():
AC_DEFUN([gl_GETDELIM_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_GETDELIM])
  if test ${HAVE_GETDELIM} = 0 || test ${REPLACE_GETDELIM} = 1; then
    AC_LIBOBJ([getdelim])dnl
    gl_PREREQ_GETDELIM
  fi
  gl_STDIO_MODULE_INDICATOR([getdelim])dnl
  AC_REQUIRE([gl_GETNDELIM2])dnl
])dnl

dnl# checks related to getline():
AC_DEFUN([gl_GETLINE_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_GETLINE])
  if test ${REPLACE_GETLINE} = 1; then
    AC_LIBOBJ([getline])dnl
    gl_PREREQ_GETLINE
  fi
  gl_STDIO_MODULE_INDICATOR([getline])dnl
  AC_REQUIRE([gl_GETNLINE])dnl
])dnl

dnl# checks related to getopt():
AC_DEFUN([gl_GETOPT_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_GETOPT_GNU])dnl
  AC_REQUIRE([gl_FUNC_GETOPT_POSIX])dnl
  dnl# only do this check once, after both the "_GNU" and "_POSIX" versions
  dnl# have run:
  if test ${REPLACE_GETOPT} = 1; then
    AC_LIBOBJ([getopt])dnl
    AC_LIBOBJ([getopt1])dnl
    gl_PREREQ_GETOPT
  fi
  gl_MODULE_INDICATOR_FOR_TESTS([getopt-gnu])dnl
])dnl

dnl# checks related to IO functions:
AC_DEFUN([gl_IO_FUNCS_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_GLIBC_UNLOCKED_IO])dnl
  AC_REQUIRE([gl_FUNC_IOCTL])dnl
])dnl

dnl# checks related to the isnan() family of functions:
AC_DEFUN([gl_ISNAN_UMBRELLA],[
  AC_REQUIRE([gl_ISNAN])dnl
  gl_MATH_MODULE_INDICATOR([isnan])dnl
  AC_REQUIRE([gl_FUNC_ISNAND])
  if test ${HAVE_ISNAND} = 0 || test ${REPLACE_ISNAN} = 1; then
    AC_LIBOBJ([isnand])dnl
    gl_PREREQ_ISNAND
  fi
  gl_MATH_MODULE_INDICATOR([isnand])dnl
  AC_REQUIRE([gl_FUNC_ISNAND_NO_LIBM])
  if test "x${gl_func_isnand_no_libm}" != "xyes"; then
    AC_LIBOBJ([isnand])dnl
    gl_PREREQ_ISNAND
  fi
  AC_REQUIRE([gl_FUNC_ISNANF])
  if test ${HAVE_ISNANF} = 0 || test ${REPLACE_ISNAN} = 1; then
    AC_LIBOBJ([isnanf])dnl
    gl_PREREQ_ISNANF
  fi
  gl_MATH_MODULE_INDICATOR([isnanf])dnl
  AC_REQUIRE([gl_FUNC_ISNANF_NO_LIBM])
  if test "x${gl_func_isnanf_no_libm}" != "xyes"; then
    AC_LIBOBJ([isnanf])dnl
    gl_PREREQ_ISNANF
  fi
  AC_REQUIRE([gl_FUNC_ISNANL])
  if test ${HAVE_ISNANL} = 0 || test ${REPLACE_ISNAN} = 1; then
    AC_LIBOBJ([isnanl])dnl
    gl_PREREQ_ISNANL
  fi
  gl_MATH_MODULE_INDICATOR([isnanl])dnl
  AC_REQUIRE([gl_FUNC_ISNANL_NO_LIBM])
  if test "x${gl_func_isnanl_no_libm}" != "xyes"; then
    AC_LIBOBJ([isnanl])dnl
    gl_PREREQ_ISNANL
  fi
])dnl

dnl# checks related to the locale:
AC_DEFUN([gl_LOCALE_UMBRELLA],[
  AC_REQUIRE([gl_LOCALCHARSET])
  export LOCALCHARSET_TESTS_ENVIRONMENT="CHARSETALIASDIR=\"\$(abs_top_builddir)/${gl_source_base}\""
  AC_SUBST([LOCALCHARSET_TESTS_ENVIRONMENT])dnl
  AC_REQUIRE([gl_FUNC_LOCALECONV])
  if test ${REPLACE_LOCALECONV} = 1; then
    AC_LIBOBJ([localeconv])dnl
    gl_PREREQ_LOCALECONV
  fi
  gl_LOCALE_MODULE_INDICATOR([localeconv])dnl
  AC_REQUIRE([gl_LOCALENAME])dnl
])dnl

dnl# checks related to malloc():
AC_DEFUN([gl_MALLOC_UMBRELLA],[
  dnl# consider requiring instead, now that we are inside a defun-ed macro:
  if test "x${ac_cv_func_malloc_0_nonnull}" = "x"; then
    test -z "${ac_cv_func_malloc_0_nonnull}"
    AC_FUNC_MALLOC
  fi
  AC_REQUIRE([gl_FUNC_MALLOC_GNU])dnl
  AC_REQUIRE([gl_FUNC_MALLOC_POSIX])dnl
  AC_REQUIRE([gl_CHECK_MALLOC_POSIX])dnl
  AC_REQUIRE([gl_MALLOCA])dnl
  AC_REQUIRE([XORG_MEMORY_CHECK_FLAGS])dnl
  AC_REQUIRE([XORG_CHECK_MALLOC_ZERO])dnl
])dnl

dnl# checks related to memchr():
AC_DEFUN([gl_MEMCHR_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_MEMCHR])
  if test ${HAVE_MEMCHR} = 0 || test ${REPLACE_MEMCHR} = 1; then
    AC_LIBOBJ([memchr])dnl
    gl_PREREQ_MEMCHR
  fi
  gl_STRING_MODULE_INDICATOR([memchr])dnl
  AC_REQUIRE([gl_FUNC_MEMCHR_OBSOLETE])dnl
  AC_REQUIRE([gl_FUNC_MEMRCHR])
  if test "x${ac_cv_func_memrchr}" = "xno"; then
    AC_LIBOBJ([memrchr])dnl
    gl_PREREQ_MEMRCHR
  fi
  gl_STRING_MODULE_INDICATOR([memrchr])dnl
  AC_REQUIRE([gl_FUNC_RAWMEMCHR])
  if test ${HAVE_RAWMEMCHR} = 0; then
    AC_LIBOBJ([rawmemchr])dnl
    gl_PREREQ_RAWMEMCHR
    if test "x${ac_cv_header_bp_sym_h}" = "x"; then
      test -z "${ac_cv_header_bp_sym_h}"
      gl_PREREQ_MEMCHR
    fi
  fi
  gl_STRING_MODULE_INDICATOR([rawmemchr])dnl
])dnl

dnl# checks related to mempcpy():
AC_DEFUN([gl_MEMPCPY_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_MEMPCPY])
  if test ${HAVE_MEMPCPY} = 0; then
    AC_LIBOBJ([mempcpy])dnl
    gl_PREREQ_MEMPCPY
  fi
  gl_STRING_MODULE_INDICATOR([mempcpy])dnl
])dnl

dnl# checks for functions beginning with the "mem" prefix:
AC_DEFUN([gl_MEM_FUNCS_UMBRELLA],[
  AC_REQUIRE([gl_MEMCHR_UMBRELLA])dnl
  AC_REQUIRE([AC_FUNC_MEMCMP])dnl
  AC_REQUIRE([gl_MEMPCPY_UMBRELLA])dnl
])dnl

dnl# checks related to mktime():
AC_DEFUN([gl_MKTIME_UMBRELLA],[
  AC_REQUIRE([AC_FUNC_MKTIME])dnl
  AC_REQUIRE([gl_FUNC_MKTIME])dnl
  gl_TIME_MODULE_INDICATOR([mktime])dnl
  AC_REQUIRE([gl_FUNC_MKTIME_INTERNAL])dnl
  dnl# only do this once, after both the internal and non-internal checks
  dnl# have run:
  if test ${REPLACE_MKTIME} = 1; then
    AC_LIBOBJ([mktime])dnl
    gl_PREREQ_MKTIME
  fi
])dnl

dnl# checks related to mmap():
AC_DEFUN([gl_MMAP_UMBRELLA],[
  AC_REQUIRE([AC_FUNC_MMAP])dnl
  AC_REQUIRE([gl_FUNC_MMAP_ANON])dnl
])dnl

dnl# checks for functions related to mounting:
AC_DEFUN([gl_MOUNT_UMBRELLA],[
  dnl# consider requiring instead, now that we are inside a defun-ed macro:
  if test "x${ac_cv_func_getmntent}" = "x"; then
    test -z "${ac_cv_func_getmntent}"
    AC_FUNC_GETMNTENT
  fi
  AC_REQUIRE([gl_LIST_MOUNTED_FILE_SYSTEMS])dnl
  AC_REQUIRE([gl_MOUNTLIST])
  if test "x${gl_cv_list_mounted_fs}" = "xyes"; then
    AC_LIBOBJ([mountlist])dnl
    gl_PREREQ_MOUNTLIST_EXTRA
  fi
])dnl

dnl# checks for msvc things:
AC_DEFUN([gl_MSVC_UMBRELLA],[
  AC_REQUIRE([gl_MSVC_INVAL])
  if test ${HAVE_MSVC_INVALID_PARAMETER_HANDLER} = 1; then
    AC_LIBOBJ([msvc-inval])
  fi
])dnl

dnl# checks related to obstacks:
AC_DEFUN([gl_OBSTACK_UMBRELLA],[
  AC_REQUIRE([AC_FUNC_OBSTACK])dnl
  AC_REQUIRE([gl_FUNC_OBSTACK_PRINTF])dnl
  AC_REQUIRE([gl_FUNC_OBSTACK_PRINTF_POSIX])dnl
  dnl# only do this check once, after both the un-suffixed and
  dnl# "_POSIX" versions have run:
  if test "x${ac_cv_func_obstack_printf}" = "xno" || test ${REPLACE_OBSTACK_PRINTF} = 1; then
    AC_LIBOBJ([obstack_printf])
  fi
  gl_STDIO_MODULE_INDICATOR([obstack-printf])dnl
  gl_STDIO_MODULE_INDICATOR([obstack-printf-posix])dnl
])dnl

dnl# checks related to opening things:
AC_DEFUN([gl_OPEN_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_FDOPEN])
  if test ${REPLACE_FDOPEN} = 1; then
    AC_LIBOBJ([fdopen])dnl
    gl_PREREQ_FDOPEN
  fi
  gl_STDIO_MODULE_INDICATOR([fdopen])dnl
  AC_REQUIRE([gl_FUNC_FDOPENDIR])
  if test ${HAVE_FDOPENDIR} = 0 || test ${REPLACE_FDOPENDIR} = 1; then
    AC_LIBOBJ([fdopendir])
  fi
  gl_DIRENT_MODULE_INDICATOR([fdopendir])dnl
  gl_MODULE_INDICATOR([fdopendir])dnl
  AC_REQUIRE([gl_FUNC_OPENAT])
  if test ${HAVE_OPENAT} = 0 || test ${REPLACE_OPENAT} = 1; then
    AC_LIBOBJ([openat])
    gl_PREREQ_OPENAT
  fi
  gl_MODULE_INDICATOR([openat]) dnl# for getcwd.c (if it exists)
  gl_FCNTL_MODULE_INDICATOR([openat])dnl
  AC_REQUIRE([gl_OPENAT_SAFER])dnl
  gl_MODULE_INDICATOR([openat-safer])dnl
  AC_REQUIRE([gl_FUNC_OPENPTY])dnl
])dnl

dnl# checks related to pipes:
AC_DEFUN([gl_PIPE_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_PIPE2])dnl
  gl_UNISTD_MODULE_INDICATOR([pipe2])dnl
  gl_MODULE_INDICATOR([pipe2-safer])dnl
])dnl

dnl# checks related to polling:
AC_DEFUN([gl_POLL_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_POLL])
  if test ${HAVE_POLL} = 0 || test ${REPLACE_POLL} = 1; then
    AC_LIBOBJ([poll])dnl
    gl_PREREQ_POLL
  fi
  gl_POLL_MODULE_INDICATOR([poll])dnl
  dnl# 'select()' is sometimes considered an alternative to 'poll()':
  AC_REQUIRE([AC_FUNC_SELECT_ARGTYPES])dnl
])dnl

dnl# checks for the printf() family of functions:
AC_DEFUN([gl_PRINTF_FAMILY_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_OBSTACK_PRINTF])dnl
  AC_REQUIRE([gl_FUNC_OBSTACK_PRINTF_POSIX])dnl
  AC_REQUIRE([gl_FUNC_PRINTF_FREXP])dnl
  AC_REQUIRE([gl_FUNC_PRINTF_FREXPL])dnl
  AC_REQUIRE([gl_FUNC_VASNPRINTF])dnl
  AC_REQUIRE([gl_FUNC_VASNPRINTF_POSIX])dnl
  AC_REQUIRE([AC_FUNC_VPRINTF])dnl
])dnl

dnl# checks related to quoting:
AC_DEFUN([gl_QUOTE_UMBRELLA],[
  AC_REQUIRE([gl_QUOTE])dnl
  AC_REQUIRE([gl_QUOTEARG])dnl
])dnl

dnl# checks for the readlink() family of functions:
AC_DEFUN([gl_READLINK_FAMILY_UMBRELLA],[
  AC_REQUIRE([AC_FUNC_AREADLINKAT])dnl
  AC_REQUIRE([gl_FUNC_READLINK])
  if test ${HAVE_READLINK} = 0 || test ${REPLACE_READLINK} = 1; then
    AC_LIBOBJ([readlink])dnl
    gl_PREREQ_READLINK
  fi
  gl_UNISTD_MODULE_INDICATOR([readlink])dnl
  AC_REQUIRE([gl_FUNC_READLINK_SEPARATE])dnl
  AC_REQUIRE([gl_FUNC_READLINKAT])
  if test ${HAVE_READLINKAT} = 0; then
    AC_LIBOBJ([readlinkat])
  fi
  gl_MODULE_INDICATOR([readlinkat])dnl
  gl_UNISTD_MODULE_INDICATOR([readlinkat])dnl
  gl_MODULE_INDICATOR([xreadlinkat])dnl
])dnl

dnl# checks related to realloc():
AC_DEFUN([gl_REALLOC_UMBRELLA],[
  dnl# consider requiring instead, now that we are inside a defun-ed macro:
  if test "x${ac_cv_func_realloc_0_nonnull}" = "x"; then
    test -z "${ac_cv_func_realloc_0_nonnull}"
    AC_FUNC_REALLOC
  fi
  AC_REQUIRE([gl_FUNC_REALLOC_GNU])dnl
  AC_REQUIRE([gl_FUNC_REALLOC_POSIX])dnl
  dnl# only do this check once, after both the "_GNU" and "_POSIX" versions
  dnl# have run:
  if test ${REPLACE_REALLOC} = 1; then
    AC_LIBOBJ([realloc])
  fi
  gl_MODULE_INDICATOR([realloc-gnu])dnl
  gl_STDLIB_MODULE_INDICATOR([realloc-posix])dnl
])dnl

dnl# checks related to the stat() family of functions:
AC_DEFUN([gl_STAT_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_FSTAT])
  if test ${REPLACE_FSTAT} = 1; then
    AC_LIBOBJ([fstat])dnl
    gl_PREREQ_FSTAT
  fi
  gl_SYS_STAT_MODULE_INDICATOR([fstat])dnl
  AC_REQUIRE([gl_FUNC_FSTATAT])
  if test ${HAVE_FSTATAT} = 0 || test ${REPLACE_FSTATAT} = 1; then
    AC_LIBOBJ([fstatat])
  fi
  gl_MODULE_INDICATOR([fstatat]) dnl# for "openat.h"
  gl_SYS_STAT_MODULE_INDICATOR([fstatat])dnl
  AC_REQUIRE([gl_FUNC_FTS])
  if test "x${ac_cv_func_fstatfs}" != "xyes"; then
    AC_LIBOBJ([fts])
  fi
  AC_REQUIRE([AC_FUNC_LSTAT])dnl
  AC_REQUIRE([AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK])dnl
  AC_REQUIRE([AC_FUNC_STAT])dnl
  AC_REQUIRE([AC_HEADER_STAT])dnl
])dnl

dnl# checks related to strchrnul:
AC_DEFUN([gl_STRCHRNUL_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_STRCHRNUL])
  if test ${HAVE_STRCHRNUL} = 0 || test ${REPLACE_STRCHRNUL} = 1; then
    AC_LIBOBJ([strchrnul])dnl
    gl_PREREQ_STRCHRNUL
  fi
  gl_STRING_MODULE_INDICATOR([strchrnul])dnl
])dnl

dnl# checks related to strndup():
AC_DEFUN([gl_STRNDUP_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_STRNDUP])
  if test ${HAVE_STRNDUP} = 0 || test ${REPLACE_STRNDUP} = 1; then
    AC_LIBOBJ([strndup])
  fi
  gl_STRING_MODULE_INDICATOR([strndup])dnl
  AC_REQUIRE([gl_XSTRNDUP])dnl
])dnl

dnl# checks related to strerror_r():
AC_DEFUN([AC_STRERROR_R_UMBRELLA],[
  dnl# consider requiring instead, now that we are inside a defun-ed macro:
  if test "x${ac_cv_func_strerror_r}" = "x"; then
    test -z "${ac_cv_func_strerror_r}"
    AC_FUNC_STRERROR_R
  fi
])dnl

dnl# checks related to strnlen():
AC_DEFUN([gl_STRNLEN_UMBRELLA],[
  AC_REQUIRE([AC_FUNC_STRNLEN])dnl
  AC_REQUIRE([gl_FUNC_STRNLEN])
  if test ${HAVE_DECL_STRNLEN} = 0 || test ${REPLACE_STRNLEN} = 1; then
    AC_LIBOBJ([strnlen])dnl
    gl_PREREQ_STRNLEN
  fi
  gl_STRING_MODULE_INDICATOR([strnlen])dnl
])dnl

dnl# checks related to strsignal():
AC_DEFUN([gl_STRSIGNAL_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_STRSIGNAL])
  if test ${HAVE_STRSIGNAL} = 0 || test ${REPLACE_STRSIGNAL} = 1; then
    AC_LIBOBJ([strsignal])dnl
    gl_PREREQ_STRSIGNAL
  fi
  gl_STRING_MODULE_INDICATOR([strsignal])dnl
])dnl

dnl# checks for functions beginning with the "str" prefix:
AC_DEFUN([gl_STR_FUNCS_UMBRELLA],[
  AC_REQUIRE([gl_STRCHRNUL_UMBRELLA])dnl
  AC_REQUIRE([gl_STRNDUP_UMBRELLA])dnl
  AC_REQUIRE([AC_STRERROR_R_UMBRELLA])dnl
  AC_REQUIRE([gl_STRNLEN_UMBRELLA])dnl
  AC_REQUIRE([gl_STRSIGNAL_UMBRELLA])dnl
])dnl

dnl# checks related to ptys, pts-es, ttys, and such:
AC_DEFUN([gl_TERMINAL_FUNCS_UMBRELLA],[
  AC_REQUIRE([gl_FUNC_FORKPTY])dnl
  AC_REQUIRE([gl_FUNC_LOGIN_TTY])dnl
  AC_REQUIRE([gl_FUNC_OPENPTY])dnl
  AC_REQUIRE([gl_FUNC_PTSNAME])dnl
  AC_REQUIRE([gl_FUNC_PTSNAME_R])dnl
])dnl

dnl# checks for text functions:
AC_DEFUN([gl_TEXT_FUNCS_UMBRELLA],[
  AC_REQUIRE([gl_LOCALE_UMBRELLA])dnl
  AC_REQUIRE([gl_FUNC_NL_LANGINFO])dnl
  AC_REQUIRE([gl_PRINTF_FAMILY_UMBRELLA])dnl
  AC_REQUIRE([gl_QUOTE_UMBRELLA])dnl
  AC_REQUIRE([gl_STR_FUNCS_UMBRELLA])dnl
  AC_REQUIRE([gl_WIDE_CHAR_FUNCS_UMBRELLA])dnl
])dnl

dnl# checks for wide character related things:
AC_DEFUN([gl_WIDE_CHAR_FUNCS_UMBRELLA],[
  AC_REQUIRE([gl_BTOWC_UMBRELLA])dnl
  AC_REQUIRE([AC_FUNC_MBRTOWC])dnl
  AC_REQUIRE([gl_FUNC_WCTOB])dnl
])dnl

dnl# checks for functions beginning with the "x" prefix that simply wrap
dnl# the un-prefixed version of them:
AC_DEFUN([gl_XWRAPPING_FUNCS_UMBRELLA],[
  AC_REQUIRE([gl_XALLOC])dnl
  AC_REQUIRE([gl_XGETCWD])dnl
  AC_REQUIRE([gl_XSIZE])dnl
  AC_REQUIRE([gl_XSTRNDUP])dnl
])dnl

dnl# all of the previous "_UMBRELLA" macros:
AC_DEFUN([gl_ALL_FUNC_UMBRELLAS_META_UMBRELLA],[
  AC_REQUIRE([AC_ALLOCA_UMBRELLA])dnl
  AC_REQUIRE([gl_ALLOC_FUNCS_UMBRELLA])dnl
  AC_REQUIRE([AC_FUNC_AREADLINKAT])dnl
  AC_REQUIRE([gl_BTOWC_UMBRELLA])dnl
  AC_REQUIRE([gl_CANONICALIZE_UMBRELLA])dnl
  AC_REQUIRE([gl_CHDIR_UMBRELLA])dnl
  AC_REQUIRE([gl_CHOWN_UMBRELLA])dnl
  AC_REQUIRE([gl_CLOSE_UMBRELLA])dnl
  AC_REQUIRE([gl_CWD_UMBRELLA])dnl
  AC_REQUIRE([gl_DIRNAME_UMBRELLA])dnl
  AC_REQUIRE([gl_DUP_UMBRELLA])dnl
  AC_REQUIRE([gl_ENVIRON_FUNCS_UMBRELLA])dnl
  AC_REQUIRE([gl_ERROR_UMBRELLA])dnl
  AC_REQUIRE([gl_FCHMODAT_UMBRELLA])dnl
  AC_REQUIRE([gl_FCHOWNAT_UMBRELLA])dnl
  AC_REQUIRE([gl_FFLUSH_UMBRELLA])dnl
  AC_REQUIRE([gl_FILE_NAME_UMBRELLA])dnl
  AC_REQUIRE([AC_FORK_UMBRELLA])dnl
  AC_REQUIRE([gl_FPENDING_UMBRELLA])dnl
  AC_REQUIRE([gl_FREAD_UMBRELLA])dnl
  AC_REQUIRE([gl_GETDELIM_UMBRELLA])dnl
  AC_REQUIRE([gl_GETLINE_UMBRELLA])dnl
  AC_REQUIRE([gl_GETOPT_UMBRELLA])dnl
  AC_REQUIRE([gl_IO_FUNCS_UMBRELLA])dnl
  AC_REQUIRE([gl_ISNAN_UMBRELLA])dnl
  AC_REQUIRE([gl_LOCALE_UMBRELLA])dnl
  AC_REQUIRE([gl_MALLOC_UMBRELLA])dnl
  AC_REQUIRE([gl_MEMCHR_UMBRELLA])dnl
  AC_REQUIRE([gl_MEMPCPY_UMBRELLA])dnl
  AC_REQUIRE([gl_MEM_FUNCS_UMBRELLA])dnl
  AC_REQUIRE([gl_MKTIME_UMBRELLA])dnl
  AC_REQUIRE([gl_MMAP_UMBRELLA])dnl
  AC_REQUIRE([gl_MOUNT_UMBRELLA])dnl
  AC_REQUIRE([gl_MSVC_UMBRELLA])dnl
  AC_REQUIRE([gl_OBSTACK_UMBRELLA])dnl
  AC_REQUIRE([gl_OPEN_UMBRELLA])dnl
  AC_REQUIRE([gl_PIPE_UMBRELLA])dnl
  AC_REQUIRE([gl_POLL_UMBRELLA])dnl
  AC_REQUIRE([gl_PRINTF_FAMILY_UMBRELLA])dnl
  AC_REQUIRE([gl_QUOTE_UMBRELLA])dnl
  AC_REQUIRE([gl_READLINK_FAMILY_UMBRELLA])dnl
  AC_REQUIRE([gl_REALLOC_UMBRELLA])dnl
  AC_REQUIRE([gl_STAT_UMBRELLA])dnl
  AC_REQUIRE([gl_STRCHRNUL_UMBRELLA])dnl
  AC_REQUIRE([gl_STRNDUP_UMBRELLA])dnl
  AC_REQUIRE([AC_STRERROR_R_UMBRELLA])dnl
  AC_REQUIRE([gl_STRNLEN_UMBRELLA])dnl
  AC_REQUIRE([gl_STRSIGNAL_UMBRELLA])dnl
  AC_REQUIRE([gl_STR_FUNCS_UMBRELLA])dnl
  AC_REQUIRE([gl_TERMINAL_FUNCS_UMBRELLA])dnl
  AC_REQUIRE([gl_TEXT_FUNCS_UMBRELLA])dnl
  AC_REQUIRE([gl_WIDE_CHAR_FUNCS_UMBRELLA])dnl
  AC_REQUIRE([gl_XWRAPPING_FUNCS_UMBRELLA])dnl
])dnl

