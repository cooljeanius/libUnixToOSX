#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libUnixToOSX],[0.0.1],[/dev/null])
AN_OSX_WARNINGS_DUMMY_MACRO
AC_CONFIG_SRCDIR([alloc.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_LIBOBJ_DIR([.])
AC_SUBST([top_srcdir])

# Check system characteristics.
AC_MSG_CHECKING([the characteristics of your system])
AC_MSG_RESULT([... .. . ])
AC_CANONICAL_TARGET
gl_USE_SYSTEM_EXTENSIONS
gl_DOUBLE_SLASH_ROOT
gl_PATHMAX
AC_CHECK_FILE([/etc/fstab])

# automake
AC_MSG_CHECKING([for some automake things...])
AC_MSG_RESULT([... .. . ])
dnl#TODO: eventually switch to gnits strictness:
AM_INIT_AUTOMAKE([1.6 foreign no-dependencies subdir-objects])
AM_MAINTAINER_MODE
AM_PROG_AR
gl_COMMON_JUST_BODY
gl_CONFIGMAKE_PREP
gl_RELOCATABLE_NOP
gl_RELOCATABLE_LIBRARY
if test "x${RELOCATABLE}" = "xyes"; then
  AC_LIBOBJ([progreloc])
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
AH_TOP([
#ifndef __CONFIG_H__
#define __CONFIG_H__ 1
])
AH_BOTTOM([
#endif /* !__CONFIG_H__ */

/* EOF */
])

# libtool
AC_MSG_CHECKING([for some libtool things...])
AC_MSG_RESULT([... .. . ])
LT_INIT([dlopen])
LT_LANG([C])

# Checks for programs.
AC_MSG_CHECKING([for some programs...])
AC_MSG_RESULT([... .. . ])
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_GCC_TRADITIONAL
AC_DEFUN([AC_REQUIRE_GREPS],[
  AC_REQUIRE([AC_PROG_GREP])
  AC_REQUIRE([AC_PROG_EGREP])
  AC_REQUIRE([AC_PROG_FGREP])
])
AC_REQUIRE_GREPS
AC_PROG_INSTALL
AM_PROG_INSTALL_STRIP
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_DEFUN([AC_REQUIRE_RANLIB],[
  AC_REQUIRE([AC_PROG_RANLIB])
])
if test "x${RANLIB}" = "x"; then
  test -z "${RANLIB}"
  AC_REQUIRE_RANLIB
else
  test ! -z "${RANLIB}" && export RANLIB
  AC_SUBST([RANLIB])
fi
AC_DEFUN([AC_REQUIRE_SED],[
  AC_REQUIRE([AC_PROG_SED])
])
AC_REQUIRE_SED
dnl# TODO: use "otool -L" as a substitute for "ldd" when applicable:
AC_CHECK_PROG([LDD],[ldd])
if test "x${LDD}" = "x" && test "x${ac_cv_prog_ac_ct_OBJDUMP}" = "x"; then
  test -z "${OBJDUMP}"
  gl_LDD
fi
dnl# FIXME: are all of these correct?
AC_CHECK_PROG([LSMOD],[lsmod])
if test "x${LSMOD}" = "x" || test "x${LSMOD}" = "xno"; then
  AC_CHECK_PROG([KEXTUTIL],[kextutil])
  AC_CHECK_PROG([KEXTSTAT],[kextstat])
  AC_CHECK_PROG([KEXTLOAD],[kextload])
  AC_CHECK_PROG([KMODUNLOAD],[kmodunload])
fi

# Compiler warnings:
AC_MSG_CHECKING([which compiler warnings are supported...])
AC_MSG_RESULT([... .. . ])
dnl#TODO: add a configure flag to enable the warnings conditionally:
gl_MANYWARN_ALL_GCC([warnings_to_check])
warnings_to_skip=""
warnings_to_skip="${warnings_to_skip} -Wsystem-headers"         # unfixable
warnings_to_skip="${warnings_to_skip} -Wvla"        # warnings in gettext.h
warnings_to_skip="${warnings_to_skip} -Wsuggest-attribute=format"     # ???
warnings_to_skip="${warnings_to_skip} -Wsuggest-attribute=pure"       # ???
gl_MANYWARN_COMPLEMENT([actual_warnings_to_check],
                       [${warnings_to_check}],
                       [${warnings_to_skip}])
for fsf_gcc_warnflag in ${actual_warnings_to_check}; do
  gl_WARN_ADD([${fsf_gcc_warnflag}])
done
# manywarnings.m4 is missing these Apple-gcc-specific flags:
for apple_gcc_warnflag in -Wmost -Wfour-char-constants -Wnewline-eof -Wshorten-64-to-32 -Wextra-tokens -Waltivec-long-deprecated; do
dnl# (was actually just a typo)
  gl_WARN_ADD([${apple_gcc_warnflag}])
done

# Checks for libraries.
AC_MSG_CHECKING([for some libraries...])
AC_MSG_RESULT([... .. . ])
LT_LIB_M
gl_PTY_LIB
AC_CHECK_LIB([crypt],[crypt],[],[
  AC_CHECK_LIB([crypt],[main])
])
AC_SEARCH_LIBS([crypt],[crypt System crypto c pub gnu iberty])
AC_SEARCH_LIBS([dupfd],[c System magic pub gnu iberty])

# Threading.
AC_MSG_CHECKING([for threading library characteristics...])
AC_MSG_RESULT([... .. . ])
gl_THREADLIB_EARLY
gl_LOCK
gl_THREADLIB
gl_THREAD
gl_TLS

# Checks for header files.
AC_MSG_CHECKING([for headers for which predefined checks exist...])
AC_MSG_RESULT([... .. . ])
AC_SYS_POSIX_TERMIOS
AC_HEADER_ASSERT
AC_HEADER_DIRENT
AC_HEADER_STAT
AC_HEADER_STDBOOL dnl# also "_CHECK"s it
AC_HEADER_TIME
AC_HEADER_TIOCGWINSZ
gl_DIRENT_H
gl_DIRENT_SAFER
gl_MODULE_INDICATOR([dirent-safer])
gl_FCNTL_H
if test "x${NEXT_FCNTL_H}" = "x"; then
  test -z "${NEXT_FCNTL_H}" && export NEXT_FCNTL_H="<fcntl.h>"
  AC_SUBST([NEXT_FCNTL_H])
fi
gl_FCNTL_SAFER
gl_MODULE_INDICATOR([fcntl-safer])
gl_FLOAT_H
if test ${REPLACE_FLOAT_LDBL} = 1; then
  AC_LIBOBJ([float])
fi
if test ${REPLACE_ITOLD} = 1; then
  AC_LIBOBJ([itold])
fi
gl_GETOPT_CHECK_HEADERS
gl_LOCALE_H
gl_MATH_H
gl_POLL_H
gl_PTY_H
gl_HEADER_STRING_H
gl_HEADER_STRINGS_H
gl_HEADER_SYS_SOCKET
gl_SYS_SOCKET_MODULE_INDICATOR([recv])
gl_HEADER_SYS_STAT_H
gl_STDDEF_H
gl_STDINT_H
gl_TERMIOS_H
gl_HEADER_TIME_H
gl_UNISTD_H
gl_UNISTD_SAFER
gl_WCHAR_H
AC_MSG_CHECKING([for miscellaneous other headers...])
AC_MSG_RESULT([... .. . ])
AC_CHECK_HEADERS_IF_NOT_CACHED([features.h getopt.h langinfo.h \
                                mach-o/dyld.h math.h search.h stdio_ext.h \
                                sys/fs_types.h sys/ioctl.h sys/param.h \
                                sys/socket.h sys/statvfs.h sys/time.h \
                                sys/vfs.h termios.h xlocale.h wchar.h])
AC_CHECK_HEADERS([OS.h alloc.h assert.h bits/libc-lock.h cdefs.h \
                  errno.h fcntl.h float.h fshelp.h fstab.h \
                  fts.h ftw.h gnu-versions.h iconv.h io.h iostream.h \
                  lcrypt.h libcharset.h libintl.h \
                  libio/iolibio.h libio/libioP.h \
                  limits.h locale.h malloc.h malloc/malloc.h mm.h \
                  mntent.h mnttab.h module.h netdb.h nl_types.h os2.h \
                  process.h ptms.h publib.h publib/strutil.h \
                  shlib-compat.h stdarg.h stddef.h stdio.h stream.h \
                  stropts.h strutil.h swapctl.h swap.h sys/cdefs.h \
                  sys/fcntl.h sys/fstyp.h sys/mntent.h sys/mnttab.h \
                  sys/statfs.h termio.h time.h utmp.h utmpx.h \
                  values.h wctype.h winbase.h windows.h])
# CoreFoundation headers:
AC_CHECK_HEADERS([CoreFoundation/CFString.h CoreFoundation/CFLocale.h \
                  CoreFoundation/CFPreferences.h])
dnl# keep autoscan happy:
if test "x" = "y"; then
  test -x `which autoscan`
  AC_CHECK_HEADERS([langinfo.h stdio_ext.h sys/ioctl.h sys/param.h \
                    sys/socket.h sys/statvfs.h sys/time.h sys/vfs.h \
                    wchar.h])
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_MSG_CHECKING([into the characteristics of your C compiler...])
AC_MSG_RESULT([... .. . ])
AC_SYS_LARGEFILE
AC_C_BIGENDIAN
AC_C_CHAR_UNSIGNED
AC_C_CONST
if test "x${ac_cv_c_inline}" = "x"; then
  test -z "${ac_cv_c_inline}"
  AC_C_INLINE
elif test "x${gl_cv_c_inline_effective}" = "x"; then
  test -z "${gl_cv_c_inline_effective}"
  gl_INLINE
  gl_EXTERN_INLINE
fi
if test "x${ac_cv_c_restrict}" = "x"; then
  test -z "${ac_cv_c_restrict}"
  AC_C_RESTRICT
fi
AC_C_PROTOTYPES
AC_C_VOLATILE
gl_CYCLE_CHECK
gl_I_RING
gl_MULTIARCH
gl_SAME
AC_MSG_CHECKING([for some declarations...])
AC_MSG_RESULT([... .. . ])
dnl# might have to get rid of the "_ONCE"s if they jump elsewehere...
AC_CHECK_DECLS_ONCE([exit_failure])
AC_CHECK_DECLS_ONCE([program_invocation_name],[],[],[#include <errno.h>])
AC_CHECK_DECLS_ONCE([program_invocation_short_name],[],[],
                    [#include <errno.h>])
AC_CHECK_DECLS_ONCE([kCFStringEncodingASCII])
AC_CHECK_DECLS_ONCE([kCFPreferencesCurrentApplication])
AC_MSG_CHECKING([for some types...])
AC_MSG_RESULT([... .. . ])
gl_INTTYPES_INCOMPLETE
AC_CHECK_SIZEOF([int])
AC_CHECK_ALIGNOF([int])
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INTMAX_T
if test "x${ac_cv_type_mode_t}" = "x"; then
  test -z "${ac_cv_type_mode_t}"
  AC_TYPE_MODE_T
fi
AC_TYPE_OFF_T
gl_TYPE_OFF_T
AC_CHECK_TYPES([ptrdiff_t])
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UID_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINTMAX_T
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
dnl#TODO: check to see if we need CoreFoundation for these next 3:
AC_CHECK_TYPES([CFLocaleRef])
AC_CHECK_TYPES([CFStringRef])
AC_CHECK_TYPES([CFTypeRef])
AC_CHECK_TYPES([__darwin_mbstate_t])
dnl#TODO: check where this comes from:
AC_CHECK_TYPES([locale_t])
AC_CHECK_TYPES([dev_t])
AC_CHECK_TYPES([ino_t])
if test "x${ac_cv_type_nlink_t}" = "x"; then
  test -z "${ac_cv_type_nlink_t}"
  AC_CHECK_TYPES([nlink_t])
fi
dnl#TODO: check to see if _DARWIN_C_SOURCE needs to be defined for this:
AC_CHECK_TYPES([Dl_info])
AC_MSG_CHECKING([for some structs and struct members...])
AC_MSG_RESULT([... .. . ])
AC_STRUCT_DIRENT_D_INO
AC_STRUCT_DIRENT_D_TYPE
AC_CHECK_MEMBERS([struct stat.st_blksize])
AC_STRUCT_ST_BLOCKS
AC_CHECK_MEMBERS([struct statvfs.f_mntfromname])
AC_CHECK_MEMBERS([struct statvfs.f_mntonname])
AC_CHECK_MEMBERS([struct statvfs.f_fstypename])
AC_STRUCT_TIMEZONE dnl# also checks "_STRUCT_TM"

# Checks for library functions.
AC_MSG_CHECKING([for functions for which predefined checks exist...])
AC_MSG_RESULT([... .. . ])
AC_FUNC_ALLOCA
gl_FUNC_ALLOCA
gl_MODULE_INDICATOR([areadlinkat])
gl_MODULE_INDICATOR([areadlinkat-with-size])
gl_FUNC_BTOWC
if test ${HAVE_BTOWC} = 0 || test ${REPLACE_BTOWC} = 1; then
  AC_LIBOBJ([btowc])
  gl_PREREQ_BTOWC
fi
gl_WCHAR_MODULE_INDICATOR([btowc])
gl_FUNC_CANONICALIZE_FILENAME_MODE
gl_MODULE_INDICATOR([canonicalize])
gl_MODULE_INDICATOR_FOR_TESTS([canonicalize])
gl_STDLIB_MODULE_INDICATOR([canonicalize_file_name])
gl_CANONICALIZE_LGPL
if test ${HAVE_CANONICALIZE_FILE_NAME} = 0 || test ${REPLACE_CANONICALIZE_FILE_NAME} = 1; then
  AC_LIBOBJ([canonicalize-lgpl])
fi
gl_MODULE_INDICATOR([canonicalize-lgpl])
dnl# "canonicalize_file_name" is already indicated above
gl_STDLIB_MODULE_INDICATOR([realpath])
gl_CANONICALIZE_LGPL_SEPARATE
gl_UNISTD_MODULE_INDICATOR([chdir])
gl_FUNC_CHDIR_LONG
if test "x${gl_cv_have_arbitrary_file_name_length_limit}" = "xyes"; then
  AC_LIBOBJ([chdir-long])
  gl_PREREQ_CHDIR_LONG
fi
gl_CHDIR_SAFER
gl_MODULE_INDICATOR_FOR_TESTS([cloexec])
gl_FUNC_CLOSE
if test ${REPLACE_CLOSE} = 1; then
  AC_LIBOBJ([close])
fi
gl_UNISTD_MODULE_INDICATOR([close])
AC_FUNC_CLOSEDIR_VOID
gl_CLOSEOUT
gl_CLOSE_STREAM
gl_MODULE_INDICATOR([close-stream])
gl_DIRNAME
gl_DIRNAME_LGPL
gl_MODULE_INDICATOR([dirname])
gl_FUNC_DUP
if test ${REPLACE_DUP} = 1; then
  AC_LIBOBJ([dup])
  gl_PREREQ_DUP
fi
gl_UNISTD_MODULE_INDICATOR([dup])
gl_FUNC_DUP2
if test ${HAVE_DUP2} = 0 || test ${REPLACE_DUP2} = 1; then
  AC_LIBOBJ([dup2])
  gl_PREREQ_DUP2
fi
gl_UNISTD_MODULE_INDICATOR([dup2])
gl_FUNC_DUP2_OBSOLETE
gl_FUNC_DUP3
gl_UNISTD_MODULE_INDICATOR([dup3])
gl_ENVIRON
gl_UNISTD_MODULE_INDICATOR([environ])
if test "x${ac_cv_lib_error_at_line}" = "x"; then
  test -z "${ac_cv_lib_error_at_line}"
  AC_FUNC_ERROR_AT_LINE
fi
gl_ERROR
if test "x${ac_cv_lib_error_at_line}" = "xno"; then
  AC_LIBOBJ([error])
  gl_PREREQ_ERROR
fi
gl_FUNC_FCHDIR
gl_UNISTD_MODULE_INDICATOR([fchdir])
gl_FUNC_FCLOSE
if test ${REPLACE_FCLOSE} = 1; then
  AC_LIBOBJ([fclose])
fi
gl_STDIO_MODULE_INDICATOR([fclose])
gl_FUNC_FDOPEN
if test ${REPLACE_FDOPEN} = 1; then
  AC_LIBOBJ([fdopen])
  gl_PREREQ_FDOPEN
fi
gl_STDIO_MODULE_INDICATOR([fdopen])
gl_FUNC_FDOPENDIR
if test ${HAVE_FDOPENDIR} = 0 || test ${REPLACE_FDOPENDIR} = 1; then
  AC_LIBOBJ([fdopendir])
fi
gl_DIRENT_MODULE_INDICATOR([fdopendir])
gl_MODULE_INDICATOR([fdopendir])
gl_FUNC_FFLUSH
if test ${REPLACE_FFLUSH} = 1; then
  AC_LIBOBJ([fflush])
  gl_PREREQ_FFLUSH
fi
gl_MODULE_INDICATOR([fflush])
gl_STDIO_MODULE_INDICATOR([fflush])
gl_FILE_NAME_CONCAT
gl_FILE_NAME_CONCAT_LGPL
gl_MODULE_INDICATOR([filenamecat])
gl_FUNC_FORKPTY
gl_FUNC_FPENDING
if test "x${ac_cv_func___fpending}" = "xno"; then
  AC_LIBOBJ([fpending])
  gl_PREREQ_FPENDING
fi
AC_FUNC_FSEEKO
gl_FUNC_FSTAT
if test ${REPLACE_FSTAT} = 1; then
  AC_LIBOBJ([fstat])
  gl_PREREQ_FSTAT
fi
gl_SYS_STAT_MODULE_INDICATOR([fstat])
gl_FUNC_FSTATAT
if test ${HAVE_FSTATAT} = 0 || test ${REPLACE_FSTATAT} = 1; then
  AC_LIBOBJ([fstatat])
fi
gl_MODULE_INDICATOR([fstatat]) dnl# for "openat.h"
gl_SYS_STAT_MODULE_INDICATOR([fstatat])
gl_FUNC_FTS
if test "x${ac_cv_func_fstatfs}" != "xyes"; then
  AC_LIBOBJ([fts])
fi
gl_FUNC_GETOPT_GNU
gl_FUNC_GETOPT_POSIX
dnl# only do this check once, after both the "_GNU" and "_POSIX" versions
dnl# have run:
if test ${REPLACE_GETOPT} = 1; then
  AC_LIBOBJ([getopt])
  AC_LIBOBJ([getopt1])
  gl_PREREQ_GETOPT
fi
gl_MODULE_INDICATOR_FOR_TESTS([getopt-gnu])
if test "x${ac_cv_func_getmntent}" = "x"; then
  test -z "${ac_cv_func_getmntent}"
  AC_FUNC_GETMNTENT
fi
gl_FUNC_IOCTL
gl_ISNAN
gl_MATH_MODULE_INDICATOR([isnan])
gl_FUNC_ISNAND
if test ${HAVE_ISNAND} = 0 || test ${REPLACE_ISNAN} = 1; then
  AC_LIBOBJ([isnand])
  gl_PREREQ_ISNAND
fi
gl_MATH_MODULE_INDICATOR([isnand])
gl_FUNC_ISNAND_NO_LIBM
if test "x${gl_func_isnand_no_libm}" != "xyes"; then
  AC_LIBOBJ([isnand])
  gl_PREREQ_ISNAND
fi
gl_FUNC_ISNANF
if test ${HAVE_ISNANF} = 0 || test ${REPLACE_ISNAN} = 1; then
  AC_LIBOBJ([isnanf])
  gl_PREREQ_ISNANF
fi
gl_MATH_MODULE_INDICATOR([isnanf])
gl_FUNC_ISNANF_NO_LIBM
if test "x${gl_func_isnanf_no_libm}" != "xyes"; then
  AC_LIBOBJ([isnanf])
  gl_PREREQ_ISNANF
fi
gl_FUNC_ISNANL
if test ${HAVE_ISNANL} = 0 || test ${REPLACE_ISNAN} = 1; then
  AC_LIBOBJ([isnanl])
  gl_PREREQ_ISNANL
fi
gl_MATH_MODULE_INDICATOR([isnanl])
gl_FUNC_ISNANL_NO_LIBM
if test "x${gl_func_isnanl_no_libm}" != "xyes"; then
  AC_LIBOBJ([isnanl])
  gl_PREREQ_ISNANL
fi
gl_LIST_MOUNTED_FILE_SYSTEMS
gl_LOCALCHARSET
export LOCALCHARSET_TESTS_ENVIRONMENT="CHARSETALIASDIR=\"\$(abs_top_builddir)/${gl_source_base}\""
AC_SUBST([LOCALCHARSET_TESTS_ENVIRONMENT])
gl_FUNC_LOCALECONV
if test ${REPLACE_LOCALECONV} = 1; then
  AC_LIBOBJ([localeconv])
  gl_PREREQ_LOCALECONV
fi
gl_LOCALE_MODULE_INDICATOR([localeconv])
gl_LOCALENAME
gl_FUNC_LOGIN_TTY
AC_FUNC_LSTAT dnl# also checks whether it "_FOLLOWS_SLASHED_SYMLINK"
if test "x${ac_cv_func_malloc_0_nonnull}" = "x"; then
  test -z "${ac_cv_func_malloc_0_nonnull}"
  AC_FUNC_MALLOC
fi
gl_FUNC_MALLOC_GNU
gl_FUNC_MALLOC_POSIX
gl_CHECK_MALLOC_POSIX
gl_MALLOCA
AC_FUNC_MBRTOWC
AC_FUNC_MEMCMP
gl_FUNC_MEMPCPY
if test ${HAVE_MEMPCPY} = 0; then
  AC_LIBOBJ([mempcpy])
  gl_PREREQ_MEMPCPY
fi
gl_STRING_MODULE_INDICATOR([mempcpy])
gl_FUNC_MEMRCHR
if test "x${ac_cv_func_memrchr}" = "xno"; then
  AC_LIBOBJ([memrchr])
  gl_PREREQ_MEMRCHR
fi
gl_STRING_MODULE_INDICATOR([memrchr])
AC_FUNC_MMAP
gl_FUNC_MMAP_ANON
gl_MOUNTLIST
if test "x${gl_cv_list_mounted_fs}" = "xyes"; then
  AC_LIBOBJ([mountlist])
  gl_PREREQ_MOUNTLIST_EXTRA
fi
gl_FUNC_NL_LANGINFO
gl_MSVC_INVAL
if test ${HAVE_MSVC_INVALID_PARAMETER_HANDLER} = 1; then
  AC_LIBOBJ([msvc-inval])
fi
AC_FUNC_OBSTACK
gl_FUNC_OBSTACK_PRINTF
gl_FUNC_OBSTACK_PRINTF_POSIX
dnl# only do this check once, after both the un-suffixed and
dnl# "_POSIX" versions have run:
if test "x${ac_cv_func_obstack_printf}" = "xno" || test ${REPLACE_OBSTACK_PRINTF} = 1; then
  AC_LIBOBJ([obstack_printf])
fi
gl_STDIO_MODULE_INDICATOR([obstack-printf])
gl_STDIO_MODULE_INDICATOR([obstack-printf-posix])
gl_FUNC_OPENAT
if test ${HAVE_OPENAT} = 0 || test ${REPLACE_OPENAT} = 1; then
  AC_LIBOBJ([openat])
  gl_PREREQ_OPENAT
fi
gl_MODULE_INDICATOR([openat]) dnl# for getcwd.c (if it exists)
gl_FCNTL_MODULE_INDICATOR([openat])
gl_OPENAT_SAFER
gl_MODULE_INDICATOR([openat-safer])
gl_FUNC_OPENPTY
gl_FUNC_POLL
if test ${HAVE_POLL} = 0 || test ${REPLACE_POLL} = 1; then
  AC_LIBOBJ([poll])
  gl_PREREQ_POLL
fi
gl_POLL_MODULE_INDICATOR([poll])
gl_FUNC_PRINTF_FREXP
gl_FUNC_PRINTF_FREXPL
gl_FUNC_PTSNAME
gl_FUNC_PTSNAME_R
gl_QUOTE
gl_QUOTEARG
gl_FUNC_RAWMEMCHR
if test ${HAVE_RAWMEMCHR} = 0; then
  AC_LIBOBJ([rawmemchr])
  gl_PREREQ_RAWMEMCHR
fi
gl_STRING_MODULE_INDICATOR([rawmemchr])
gl_FUNC_READLINK
if test ${HAVE_READLINK} = 0 || test ${REPLACE_READLINK} = 1; then
  AC_LIBOBJ([readlink])
  gl_PREREQ_READLINK
fi
gl_UNISTD_MODULE_INDICATOR([readlink])
gl_FUNC_READLINK_SEPARATE
gl_FUNC_READLINKAT
if test ${HAVE_READLINKAT} = 0; then
  AC_LIBOBJ([readlinkat])
fi
gl_UNISTD_MODULE_INDICATOR([readlinkat])
if test "x${ac_cv_func_realloc_0_nonnull}" = "x"; then
  test -z "${ac_cv_func_realloc_0_nonnull}"
  AC_FUNC_REALLOC
fi
gl_FUNC_REALLOC_GNU
gl_FUNC_REALLOC_POSIX
dnl# only do this check once, after both the "_GNU" and "_POSIX" versions
dnl# have run:
if test ${REPLACE_REALLOC} = 1; then
  AC_LIBOBJ([realloc])
fi
gl_MODULE_INDICATOR([realloc-gnu])
gl_STDLIB_MODULE_INDICATOR([realloc-posix])
gl_SAVE_CWD
AC_FUNC_SELECT_ARGTYPES
gl_FUNC_SETENV
if test ${HAVE_SETENV} = 0 || test ${REPLACE_SETENV} = 1; then
  AC_LIBOBJ([setenv])
fi
gl_STDLIB_MODULE_INDICATOR([setenv])
gl_FUNC_SETENV_SEPARATE
AC_FUNC_STAT
gl_FUNC_STRCHRNUL
if test ${HAVE_STRCHRNUL} = 0 || test ${REPLACE_STRCHRNUL} = 1; then
  AC_LIBOBJ([strchrnul])
  gl_PREREQ_STRCHRNUL
fi
gl_STRING_MODULE_INDICATOR([strchrnul])
gl_FUNC_STRNDUP
if test ${HAVE_STRNDUP} = 0 || test ${REPLACE_STRNDUP} = 1; then
  AC_LIBOBJ([strndup])
fi
gl_STRING_MODULE_INDICATOR([strndup])
if test "x${ac_cv_func_strerror_r}" = "x"; then
  test -z "${ac_cv_func_strerror_r}"
  AC_FUNC_STRERROR_R
fi
AC_FUNC_STRNLEN
gl_FUNC_STRNLEN
if test ${HAVE_DECL_STRNLEN} = 0 || test ${REPLACE_STRNLEN} = 1; then
  AC_LIBOBJ([strnlen])
  gl_PREREQ_STRNLEN
fi
gl_STRING_MODULE_INDICATOR([strnlen])
gl_FUNC_STRSIGNAL
if test ${HAVE_STRSIGNAL} = 0 || test ${REPLACE_STRSIGNAL} = 1; then
  AC_LIBOBJ([strsignal])
  gl_PREREQ_STRSIGNAL
fi
gl_STRING_MODULE_INDICATOR([strsignal])
gl_FUNC_VASNPRINTF
AC_FUNC_VPRINTF
gl_FUNC_WCTOB
gl_XALLOC
gl_XGETCWD
gl_MODULE_INDICATOR([xreadlinkat])
gl_XSIZE
gl_XSTRNDUP
AC_MSG_CHECKING([for miscellaneous other functions...])
AC_MSG_RESULT([... .. . ])
AC_CHECK_FUNCS([GetDriveType])
AC_CHECK_FUNCS_IF_NOT_CACHED([__fpending _NSGetExecutablePath btowc dup2 \
                              fchdir getcwd getmnt getmntinfo ioctl \
                              listmntent mempcpy pathconf setenv \
                              setlocale snprintf strndup])
AC_CHECK_FUNCS_ONCE([readlinkat])
AC_CHECK_FUNCS([abort assert atexit atoi clearenv close dladdr dupfd \
                fflush fgets freemntlist gettext getvfsbytype iswprint \
                localeconv lseek mblen mbrlen mbtowc memchr memmove \
                memset mntctl printf read recv select shm_open sprintf \
                strcasecmp strchr strdup strerror strncasecmp strrchr \
                strsep strspn strstr strtoul system sysconf \
                vasprintf wctomb])
# endianness functions:
AC_CHECK_FUNCS([htonl htons ntohl ntohs])
# fstab-related functions:
AC_CHECK_FUNCS([getfsent getfsspec getfsfile setfsent endfsent])
# ftw-related functions:
AC_CHECK_FUNCS([fts_open fts_children fts_close fts_read])
# alternative ftw-related functions:
AC_CHECK_FUNCS([opendir readdir closedir])
# IOKit/Kext function(s) (might need some special flags):
AC_CHECK_FUNCS([KextManagerLoadKextWithURL])
# CoreFoundation functions (might need some special flags):
AC_CHECK_FUNCS([CFBundleCopyLocalizedString CFGetTypeID \
                CFLocaleGetIdentifier CFRelease CFStringCreateCopy \
                CFStringCreateMutable CFStringGetCString \
                CFStringGetSystemEncoding CFStringGetTypeID \
                CFStringRef])
AC_CHECK_FUNCS_IF_NOT_CACHED([CFLocaleCopyCurrent \
                              CFPreferencesCopyAppValue])
# functions that we might want replacements for, but do not have the
# source files to replace them yet:
AC_CHECK_FUNCS([catopen catgets catclose crypt ecvt fcvt \
                setmntent addmntent endmntent \
                hasmntopt sbrk brk shmget swapon swapoff])
# functions that we might want replacements for, and have source files for:
unset ac_cv_func_btowc
unset ac_cv_func_wctob
unset ac_cv_func_getmntent
unset ac_cv_func_poll
AC_REPLACE_FUNCS([btowc wctob dysize fclose fcloseall getmntent poll])
# keep autoscan happy:
if test "x" = "y"; then
  test -x `which autoscan`
  AC_CHECK_FUNCS([__fpending btowc dup2 fchdir getcwd mempcpy pathconf \
                  setenv strndup])
fi

# Output:
AC_CONFIG_FILES([Makefile \
autoscan/Makefile \
libftw0/Makefile \
poll/poll-emulator/Makefile])
AC_CONFIG_SUBDIRS([argp/argp-standalone-1.3])
AC_OUTPUT
