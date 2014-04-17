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
AC_CANONICAL_TARGET
gl_USE_SYSTEM_EXTENSIONS
gl_DOUBLE_SLASH_ROOT
gl_PATHMAX
AC_CHECK_FILE([/etc/fstab])

# automake
AC_MSG_CHECKING([for some automake things...])
AC_MSG_RESULT([... ])
AM_INIT_AUTOMAKE([1.6 foreign no-dependencies])
AM_MAINTAINER_MODE
AM_PROG_AR
gl_COMMON_JUST_BODY
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
AC_MSG_RESULT([... ])
LT_INIT([dlopen])
LT_LANG([C])

# Checks for programs.
AC_MSG_CHECKING([for some programs...])
AC_MSG_RESULT([... ])
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
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

# Checks for libraries.
AC_MSG_CHECKING([for some libraries...])
AC_MSG_RESULT([... ])
LT_LIB_M
gl_PTY_LIB
AC_CHECK_LIB([crypt],[crypt],[],[
  AC_CHECK_LIB([crypt],[main])
])
AC_SEARCH_LIBS([crypt],[crypt System crypto c pub gnu iberty])
AC_SEARCH_LIBS([dupfd],[c System magic pub gnu iberty])

# Checks for header files.
AC_MSG_CHECKING([for miscellaneous headers...])
AC_MSG_RESULT([... ])
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
gl_MATH_H
gl_POLL_H
gl_PTY_H
gl_HEADER_STRING_H
gl_HEADER_STRINGS_H
gl_HEADER_SYS_SOCKET
gl_SYS_SOCKET_MODULE_INDICATOR([recv])
gl_HEADER_SYS_STAT_H
gl_STDINT_H
gl_TERMIOS_H
gl_HEADER_TIME_H
gl_UNISTD_H
gl_UNISTD_SAFER
gl_WCHAR_H
AC_CHECK_HEADERS_IF_NOT_CACHED([features.h getopt.h langinfo.h math.h \
                                sys/ioctl.h sys/param.h sys/socket.h \
                                sys/time.h sys/vfs.h termios.h wchar.h])
AC_CHECK_HEADERS([OS.h alloc.h assert.h errno.h fcntl.h float.h fstab.h \
                  fts.h ftw.h io.h iostream.h lcrypt.h libintl.h limits.h \
                  locale.h malloc.h malloc/malloc.h mm.h module.h netdb.h \
                  nl_types.h ptms.h publib.h publib/strutil.h \
                  stdarg.h stddef.h stdio.h stdio_ext.h stream.h \
                  stropts.h strutil.h swapctl.h swap.h sys/cdefs.h \
                  sys/fcntl.h termio.h time.h utmp.h utmpx.h values.h])
dnl# keep autoscan happy:
if test "x" = "y"; then
  test -x `which autoscan`
  AC_CHECK_HEADERS([langinfo.h sys/ioctl.h sys/param.h sys/socket.h \
                    sys/time.h sys/vfs.h wchar.h])
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_MSG_CHECKING([into the characteristics of your C compiler...])
AC_MSG_RESULT([... ])
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
fi
gl_EXTERN_INLINE
AC_C_PROTOTYPES
AC_C_VOLATILE
gl_CYCLE_CHECK
gl_I_RING
gl_MULTIARCH
gl_SAME
AC_CHECK_DECLS_ONCE([exit_failure])
AC_MSG_CHECKING([for some types...])
AC_MSG_RESULT([... ])
gl_INTTYPES_INCOMPLETE
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
gt_TYPE_WCHAR_T
gt_TYPE_WINT_T
AC_MSG_CHECKING([for some structs and struct members...])
AC_MSG_RESULT([... ])
AC_STRUCT_DIRENT_D_INO
AC_STRUCT_DIRENT_D_TYPE
AC_CHECK_MEMBERS([struct stat.st_blksize])
AC_STRUCT_ST_BLOCKS
AC_STRUCT_TIMEZONE dnl# also checks "_STRUCT_TM"

# Checks for library functions.
AC_MSG_CHECKING([for some miscellaneous functions...])
AC_MSG_RESULT([... ])
AC_FUNC_ALLOCA
gl_FUNC_ALLOCA
gl_FUNC_BTOWC
if test ${HAVE_BTOWC} = 0 || test ${REPLACE_BTOWC} = 1; then
  AC_LIBOBJ([btowc])
  gl_PREREQ_BTOWC
fi
gl_WCHAR_MODULE_INDICATOR([btowc])
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
gl_FUNC_MEMRCHR
if test "x${ac_cv_func_memrchr}" = "xno"; then
  AC_LIBOBJ([memrchr])
  gl_PREREQ_MEMRCHR
fi
gl_STRING_MODULE_INDICATOR([memrchr])
AC_FUNC_MMAP
gl_FUNC_MMAP_ANON
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
AC_FUNC_STAT
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
gl_FUNC_STRSIGNAL
if test ${HAVE_STRSIGNAL} = 0 || test ${REPLACE_STRSIGNAL} = 1; then
  AC_LIBOBJ([strsignal])
  gl_PREREQ_STRSIGNAL
fi
gl_STRING_MODULE_INDICATOR([strsignal])
gl_FUNC_VASNPRINTF
gl_FUNC_WCTOB
gl_XALLOC
gl_XSIZE
gl_XSTRNDUP
AC_CHECK_FUNCS_IF_NOT_CACHED([btowc dup2 fchdir ioctl mempcpy pathconf \
                              snprintf strndup])
AC_CHECK_FUNCS([abort assert atexit close dupfd fflush getcwd gettext \
                localeconv lseek mblen mbrlen mbtowc memchr memmove \
                memset printf read recv select shm_open sprintf \
                strcasecmp strchr strdup strerror strncasecmp strrchr \
                strspn system sysconf vasprintf wctomb])
# fstab-related functions:
AC_CHECK_FUNCS([getfsent getfsspec getfsfile setfsent endfsent])
# ftw-related functions:
AC_CHECK_FUNCS([fts_open fts_children fts_close fts_read])
# alternative ftw-related functions:
AC_CHECK_FUNCS([opendir readdir closedir])
# IOKit/Kext functions:
AC_CHECK_FUNCS([KextManagerLoadKextWithURL])
# CoreFoundation functions:
AC_CHECK_FUNCS([CFBundleCopyLocalizedString CFStringCreateCopy \
                CFStringCreateMutable CFStringGetSystemEncoding \
                CFStringRef])
# functions that we might want replacements for, but do not have the
# source files to replace them yet:
unset ac_cv_func_getmntent
AC_CHECK_FUNCS([catopen catgets catclose crypt ecvt fcvt \
                getmntent setmntent addmntent endmntent \
                hasmntopt sbrk brk shmget swapon swapoff])
# functions that we might want replacements for, and have source files for:
unset ac_cv_func_btowc
unset ac_cv_func_wctob
unset ac_cv_func_poll
AC_REPLACE_FUNCS([btowc wctob dysize fclose fcloseall poll])
# keep autoscan happy:
if test "x" = "y"; then
  test -x `which autoscan`
  AC_CHECK_FUNCS([btowc dup2 fchdir mempcpy pathconf strndup])
fi

# Output:
AC_CONFIG_FILES([Makefile \
autoscan/Makefile \
libftw0/Makefile \
poll/poll-emulator/Makefile])
AC_CONFIG_SUBDIRS([argp/argp-standalone-1.3])
AC_OUTPUT
