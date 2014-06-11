dnl#                                               -*- Autoconf -*-
dnl# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])dnl
AC_INIT([libUnixToOSX],[0.0.1],[/dev/null])dnl
AN_OSX_WARNINGS_DUMMY_MACRO
AC_CONFIG_SRCDIR([alloc.h])dnl
AC_CONFIG_HEADERS([config.h])dnl
AC_CONFIG_AUX_DIR([build-aux])dnl
AC_CONFIG_MACRO_DIR([m4])dnl
AC_CONFIG_LIBOBJ_DIR([.])dnl
AC_SUBST([top_srcdir])dnl

# Check system characteristics.
AC_MSG_CHECKING([the characteristics of your system])
AC_MSG_RESULT([... .. . ])
AC_CANONICAL_TARGET
gl_SYSTEM_SPECIFIC_MACROS
AC_CHECK_FILE([/etc/fstab])dnl

# automake:
AC_MSG_CHECKING([for some automake things...])
AC_MSG_RESULT([... .. . ])
dnl#TODO: eventually switch to gnits strictness:
AM_INIT_AUTOMAKE([1.6 foreign no-dependencies subdir-objects])dnl
AM_MAINTAINER_MODE
AM_PROG_AR
gl_COMMON_JUST_BODY
gl_CONFIGMAKE_PREP
gl_RELOCATABILITY_UMBRELLA
AH_TOP([
#ifndef __CONFIG_H__
#define __CONFIG_H__ 1
])dnl
AH_BOTTOM([
#endif /* !__CONFIG_H__ */

/* EOF */
])dnl

# libtool
AC_MSG_CHECKING([for some libtool things...])
AC_MSG_RESULT([... .. . ])
LT_REQUIRE_PREREQS
LT_INIT([dlopen])dnl
LT_LANG([C])dnl

# Checks for programs.
AC_MSG_CHECKING([for some programs...])
AC_MSG_RESULT([... .. . ])
AC_REQUIRE_COMPILER
AC_FILESYSTEM_OPERATION_PROGS
unset ac_cv_prog_ac_ct_RANLIB
AC_REQUIRE_RANLIB_ONCE
AC_TEXT_FILTER_PROGS
AC_REQUIRE_LINKER
AC_PROG_KERNEL_TOOLS
AC_REQUIRE_LINT

# Compiler warnings:
AC_MSG_CHECKING([which compiler warnings are supported...])
AC_MSG_RESULT([... .. . ])
dnl#TODO: add a configure flag to enable the warnings conditionally:
gl_MANYWARN_ALL_GCC([warnings_to_check])
warnings_to_skip=""
warnings_to_skip="${warnings_to_skip} -Wsystem-headers"         # unfixable
warnings_to_skip="${warnings_to_skip} -Wvla"        # warnings in gettext.h
warnings_to_skip="${warnings_to_skip} -Wsuggest-attribute=const"      # ???
warnings_to_skip="${warnings_to_skip} -Wsuggest-attribute=format"     # ???
warnings_to_skip="${warnings_to_skip} -Wsuggest-attribute=noreturn"   # ???
warnings_to_skip="${warnings_to_skip} -Wsuggest-attribute=pure"       # ???
warnings_to_skip="${warnings_to_skip} -Wmissing-format-attribute"     # ???
warnings_to_skip="${warnings_to_skip} -Wtraditional"     # not for new code
warnings_to_skip="${warnings_to_skip} -Wcast-qual"      # I use casts a lot
warnings_to_skip="${warnings_to_skip} -Wredundant-decls"  # redundancy=good
warnings_to_skip="${warnings_to_skip} -Wpedantic"        # too many for now
warnings_to_skip="${warnings_to_skip} -Wpadded"        # no idea how to fix
case ${host_cpu} in
  aarch64 | powerpc64 | x86_64)
    warnings_to_skip="${warnings_to_skip} -Wlong-long"  # "long long"=64bit
    ;;
esac
# skip when optimization has not been explicitly requested:
if test x${CFLAGS+set} = xset; then
  case "${CFLAGS}" in
    *"-O0"* ) 
      warnings_to_skip="${warnings_to_skip} -Wunsafe-loop-optimizations"
      ;;
    *"-O"* )
      ;;
  esac
else
  warnings_to_skip="${warnings_to_skip} -Wunsafe-loop-optimizations"
fi
gl_MANYWARN_COMPLEMENT([actual_warnings_to_check],
                       [${warnings_to_check}],
                       [${warnings_to_skip}])
for fsf_gcc_warnflag in ${actual_warnings_to_check}; do
  gl_WARN_ADD([${fsf_gcc_warnflag}])
done
case ${host_vendor} in
  apple)
    # manywarnings.m4 is missing these Apple-gcc-specific flags:
    for apple_gcc_warnflag in \
      -Wmost \
      -Wfour-char-constants \
      -Wnewline-eof \
      -Wshorten-64-to-32 \
      -Wextra-tokens \
      -Waltivec-long-deprecated \
      \
      ; do
      dnl# (was actually just a typo)
      gl_WARN_ADD([${apple_gcc_warnflag}])
    done
    ;;
esac

# Checks for libraries.
AC_MSG_CHECKING([for some libraries...])
AC_MSG_RESULT([... .. . ])
LT_LIB_M
gl_PTY_LIB
AC_LIB_CRYPT
AC_SEARCH_LIBS([dupfd],[c System magic pub gnu iberty])dnl

# Threading.
AC_MSG_CHECKING([for threading library characteristics...])
AC_MSG_RESULT([... .. . ])
gl_THREAD_UMBRELLA

# Checks for header files.
AC_MSG_CHECKING([for headers for which predefined checks exist...])
AC_MSG_RESULT([... .. . ])
AC_HEADER_UMBRELLA
gl_HEADER_UMBRELLA
AC_MSG_CHECKING([for miscellaneous other headers...])
AC_MSG_RESULT([... .. . ])
AC_CHECK_HEADERS_IF_NOT_CACHED([bp-sym.h features.h getopt.h langinfo.h \
                                mach-o/dyld.h math.h search.h stdio_ext.h \
                                sys/fs_types.h sys/ioctl.h sys/param.h \
                                sys/socket.h sys/statvfs.h sys/time.h \
                                sys/vfs.h termios.h xlocale.h wchar.h])dnl
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
                  values.h wctype.h winbase.h windows.h])dnl
# CoreFoundation headers:
AC_CHECK_HEADERS([CoreFoundation/CFString.h CoreFoundation/CFLocale.h \
                  CoreFoundation/CFPreferences.h])
dnl# keep autoscan happy:
if test "x" = "y"; then
  test -x `which autoscan`
  AC_CHECK_HEADERS([bp-sym.h langinfo.h stdio_ext.h sys/ioctl.h \
                    sys/param.h sys/socket.h sys/statvfs.h sys/time.h \
                    sys/vfs.h wchar.h])
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_MSG_CHECKING([into the characteristics of your C compiler...])
AC_MSG_RESULT([... .. . ])
AC_C_CHARACTERISTICS_UMBRELLA
gl_C_MISC
AC_MSG_CHECKING([for some declarations...])
AC_MSG_RESULT([... .. . ])
dnl# might have to get rid of the "_ONCE"s if they jump elsewehere...
AC_CHECK_DECLS_ONCE([exit_failure])dnl
AC_CHECK_DECLS_ONCE([program_invocation_name],[],[],
                    [#include <errno.h>])dnl
AC_CHECK_DECLS_ONCE([program_invocation_short_name],[],[],
                    [#include <errno.h>])dnl
AC_CHECK_DECLS_ONCE([kCFStringEncodingASCII])dnl
AC_CHECK_DECLS_ONCE([kCFPreferencesCurrentApplication])dnl
AC_MSG_CHECKING([for some types...])
AC_MSG_RESULT([... .. . ])
AC_CHECK_SIZEOF([int])dnl
AC_CHECK_ALIGNOF([int])dnl
AC_CHECK_TYPES([ptrdiff_t])dnl
AC_TYPES_UMBRELLA
dnl#TODO: check to see if we need CoreFoundation for these next 3:
AC_CHECK_TYPES([CFLocaleRef])dnl
AC_CHECK_TYPES([CFStringRef])dnl
AC_CHECK_TYPES([CFTypeRef])dnl
AC_CHECK_TYPES([__darwin_mbstate_t])dnl
dnl#TODO: check where this comes from:
AC_CHECK_TYPES([locale_t])dnl
AC_CHECK_TYPES([dev_t])dnl
AC_CHECK_TYPES([ino_t])
if test "x${ac_cv_type_nlink_t}" = "x"; then
  test -z "${ac_cv_type_nlink_t}"
  AC_CHECK_TYPES([nlink_t])
fi
dnl#TODO: check to see if _DARWIN_C_SOURCE needs to be defined for this:
AC_CHECK_TYPES([Dl_info])dnl
AC_MSG_CHECKING([for some structs and struct members...])
AC_MSG_RESULT([... .. . ])
AC_STRUCTS_UMBRELLA
AC_CHECK_MEMBERS([struct stat.st_blksize])dnl
AC_CHECK_MEMBERS([struct statvfs.f_mntfromname])dnl
AC_CHECK_MEMBERS([struct statvfs.f_mntonname])dnl
AC_CHECK_MEMBERS([struct statvfs.f_fstypename])dnl

# Checks for library functions.
AC_MSG_CHECKING([for functions for which predefined checks exist...])
AC_MSG_RESULT([... .. . ])
gl_ALL_FUNC_UMBRELLAS_META_UMBRELLA
AC_MSG_CHECKING([for miscellaneous other functions...])
AC_MSG_RESULT([... .. . ])
AC_CHECK_FUNCS([GetDriveType])dnl
AC_CHECK_FUNCS_IF_NOT_CACHED([__fpending _NSGetExecutablePath btowc dup2 \
                              fchdir getcwd getdelim getmnt getmntinfo \
                              ioctl listmntent memchr mempcpy pathconf \
                              setenv setlocale snprintf strndup])dnl
AC_CHECK_FUNCS_ONCE([readlinkat])dnl
AC_CHECK_FUNCS([abort assert atexit atoi clearenv close dladdr dupfd \
                fflush fgets freemntlist gettext getvfsbytype iswprint \
                localeconv lseek mblen mbrlen mbtowc memmove \
                memset mntctl printf read recv select shm_open sprintf \
                strcasecmp strchr strdup strerror strncasecmp strrchr \
                strsep strspn strstr strtoul system sysconf \
                vasprintf wctomb])dnl
# endianness functions:
AC_CHECK_FUNCS([htonl htons ntohl ntohs])dnl
# fstab-related functions:
AC_CHECK_FUNCS([getfsent getfsspec getfsfile setfsent endfsent])dnl
# ftw-related functions:
AC_CHECK_FUNCS([fts_open fts_children fts_close fts_read])dnl
# alternative ftw-related functions:
AC_CHECK_FUNCS([opendir readdir closedir])dnl
# IOKit/Kext function(s) (might need some special flags):
AC_CHECK_FUNCS([KextManagerLoadKextWithURL])dnl
# CoreFoundation functions (might need some special flags):
AC_CHECK_FUNCS([CFBundleCopyLocalizedString CFGetTypeID \
                CFLocaleGetIdentifier CFRelease CFStringCreateCopy \
                CFStringCreateMutable CFStringGetCString \
                CFStringGetSystemEncoding CFStringGetTypeID \
                CFStringRef])dnl
AC_CHECK_FUNCS_IF_NOT_CACHED([CFLocaleCopyCurrent \
                              CFPreferencesCopyAppValue])dnl
# functions that we might want replacements for, but do not have the
# source files to replace them yet:
dnl# (move from "_CHECK" to "_REPLACE" once we do have source files)
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
  AC_CHECK_FUNCS([__fpending btowc dup2 fchdir getcwd getdelim memchr \
                  mempcpy pathconf setenv strndup])
fi

# Output:
AC_CONFIG_FILES([Makefile \
autoscan/Makefile \
libftw0/Makefile \
poll/poll-emulator/Makefile])dnl
AC_CONFIG_SUBDIRS([argp/argp-standalone-1.3])dnl
AC_OUTPUT
