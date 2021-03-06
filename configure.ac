dnl#                                               -*- Autoconf -*-
dnl# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])dnl
AC_INIT([libUnixToOSX],[0.0.1],[/dev/null])dnl
AC_CONFIG_SRCDIR([alloc.h])dnl
AC_CONFIG_HEADERS([config.h])dnl
AC_CONFIG_AUX_DIR([build-aux])dnl
AC_CONFIG_MACRO_DIR([m4])dnl
AC_CONFIG_LIBOBJ_DIR([.])dnl
AC_SUBST([top_srcdir])dnl

dnl# force some aux files to be present:
AC_REQUIRE_AUX_FILE([mkinstalldirs])dnl
AC_REQUIRE_AUX_FILE([config.libpath])dnl
AC_REQUIRE_AUX_FILE([git-version-gen])dnl
AC_REQUIRE_AUX_FILE([gitlog-to-changelog])dnl
AC_REQUIRE_AUX_FILE([install-reloc])dnl
AC_REQUIRE_AUX_FILE([reloc-ldflags])dnl
AC_REQUIRE_AUX_FILE([depcomp])dnl

# Check system characteristics.
AC_MSG_CHECKING([the characteristics of your system])
AC_MSG_RESULT([... .. . ])
AC_CANONICAL_TARGET
gl_SYSTEM_SPECIFIC_MACROS
AN_OSX_WARNINGS_DUMMY_MACRO
AC_CHECK_FILE([/etc/fstab])dnl

# automake:
AC_MSG_CHECKING([for some automake things...])
AC_MSG_RESULT([... .. . ])
dnl#TODO: eventually switch to gnits strictness:
AM_INIT_AUTOMAKE([1.6 foreign no-dependencies subdir-objects])dnl
AM_MAINTAINER_MODE
AM_PROG_AR
gl_COMMON_SEMI_UMBRELLA
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
LT_PREREQ([2.4.2])dnl

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
gl_UNKNOWN_WARNINGS_ARE_ERRORS
dnl#TODO: add a configure flag to enable the warnings conditionally:
gl_MANYWARN_ALL_GCC([warnings_to_check])
warnings_to_skip=""
warnings_to_skip="${warnings_to_skip} -W"          # redundant with -Wextra
warnings_to_skip="${warnings_to_skip} -Wabi" # need numerical arg w/new GCC
warnings_to_skip="${warnings_to_skip} -Wsystem-headers"         # unfixable
warnings_to_skip="${warnings_to_skip} -Wvla"        # warnings in gettext.h
warnings_to_skip="${warnings_to_skip} -Wsuggest-attribute=const"      # ???
warnings_to_skip="${warnings_to_skip} -Wsuggest-attribute=format"     # ???
warnings_to_skip="${warnings_to_skip} -Wsuggest-attribute=noreturn"   # ???
warnings_to_skip="${warnings_to_skip} -Wsuggest-attribute=pure"       # ???
warnings_to_skip="${warnings_to_skip} -Wmissing-format-attribute"     # ???
warnings_to_skip="${warnings_to_skip} -Wtraditional"     # not for new code
warnings_to_skip="${warnings_to_skip} -Wcast-qual"      # I use casts a lot
warnings_to_skip="${warnings_to_skip} -Wcast-align"              # likewise
warnings_to_skip="${warnings_to_skip} -Wredundant-decls"  # redundancy=good
warnings_to_skip="${warnings_to_skip} -Wpedantic"        # too many for now
if test "x${GCC}" = "xyes"; then
 warnings_to_skip="${warnings_to_skip} -Wpadded" # no idea how to fix w/gcc
fi
warnings_to_skip="${warnings_to_skip} -Wcomments"   # redundant w/-Wcomment
warnings_to_skip="${warnings_to_skip} -Wmudflap"      # no longer supported
warnings_to_skip="${warnings_to_skip} -Wconditionally-supported" # C++ only
warnings_to_skip="${warnings_to_skip} -Wdelete-incomplete"       # C++ only
warnings_to_skip="${warnings_to_skip} -Wshadow-ivar"     # ObjC/ObjC++ only
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
                       [${warnings_to_skip}])dnl
  ## loop through all of them:
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
      -Wnonportable-cfstrings \
      \
      ; do
      dnl# (was actually just a typo)
      gl_WARN_ADD([${apple_gcc_warnflag}])
    done
    ;;
esac

dnl# These next ones are linker warnings, which we do need to keep
dnl# conditionalized on the vendor, because preprocessor macro
dnl# declarations tell us nothing about what the linker accepts.
dnl# Before we can check them, though, we need to make sure that this
dnl# variable is defined first, to prevent aclocal/autoconf/autom4te/gm4
dnl# from choking on the comma when it is used in arguments to the macro
dnl# that we use:
if test "x${acl_cv_wl}" = "x"; then
  test -z "${acl_cv_wl}" && export acl_cv_wl='-Wl,'
fi
AC_SUBST([acl_cv_wl])
WARN_LDFLAGS=""
dnl# ok, now that set of vendor cases I was mentioning:
case ${host_vendor} in 
  apple*)
    dnl#FIXME: make sure these flags are actually used properly
    dnl# everywhere:
    test -n "${LD_WARN_FILE}"
    gl_WARN_ADD([${acl_cv_wl}-warn_compact_unwind],[WARN_LDFLAGS])
    gl_WARN_ADD([${acl_cv_wl}-warn_weak_exports],[WARN_LDFLAGS])
    gl_WARN_ADD([${acl_cv_wl}-warn_stabs],[WARN_LDFLAGS])
    gl_WARN_ADD([${acl_cv_wl}-warn_commons],[WARN_LDFLAGS])
    test -n "${LD_WARN_COMMONS}"
    ;;
esac
AC_SUBST([WARN_LDFLAGS])dnl

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
AC_CHECK_HEADERS_IF_NOT_CACHED([bp-sym.h errno.h fcntl.h features.h \
                                getopt.h inttypes.h langinfo.h mach-o/dyld.h \
                                math.h poll.h search.h stdio_ext.h \
                                sys/fs_types.h sys/ioctl.h sys/param.h \
                                sys/socket.h sys/statvfs.h sys/time.h \
                                sys/vfs.h termios.h unistd.h xlocale.h \
                                wchar.h])dnl
  ## now regular header checks:
AC_CHECK_HEADERS([_types/_nl_item.h \
                  OS.h alloc.h assert.h bits/libc-lock.h cdefs.h \
                  float.h fshelp.h fstab.h \
                  fts.h ftw.h gnu-versions.h iconv.h io.h iostream.h \
                  lcrypt.h libcharset.h libintl.h \
                  libio/iolibio.h libio/libioP.h \
                  limits.h locale.h malloc.h malloc/malloc.h mm.h \
                  mntent.h mnttab.h module.h netdb.h nl_types.h os2.h \
                  process.h ptms.h publib.h publib/strutil.h \
                  shlib-compat.h stdarg.h stddef.h stdio.h stream.h \
                  stropts.h strutil.h swapctl.h swap.h \
                  sys/_types/_ct_rune_t.h sys/_types/_mbstate_t.h \
                  sys/_types/_null.h sys/_types/_rune_t.h \
                  sys/_types/_size_t.h sys/_types/_time_t.h \
                  sys/_types/_wchar_t.h sys/cdefs.h sys/event.h \
                  sys/fcntl.h sys/fstyp.h sys/ipc.h sys/mntent.h \
                  sys/mnttab.h sys/mount.h sys/shm.h sys/statfs.h \
                  termio.h time.h utmp.h utmpx.h values.h \
                  wctype.h winbase.h windows.h])dnl
  ## CoreFoundation headers:
AC_CHECK_HEADERS([CoreFoundation/CFString.h CoreFoundation/CFLocale.h \
                  CoreFoundation/CFPreferences.h \
                  CoreFoundation/CoreFoundation.h])
dnl# keep autoscan happy:
if test "x" = "Y0"; then
  test -x "`which autoscan`" || echo "no autoscan!" >&2
  AC_CHECK_HEADERS([bp-sym.h fcntl.h inttypes.h langinfo.h stdio_ext.h \
                    sys/ioctl.h sys/param.h sys/socket.h sys/statvfs.h \
                    sys/time.h sys/vfs.h unistd.h wchar.h])dnl
  ## should never actually get here though...
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_MSG_CHECKING([into the characteristics of your C compiler...])
AC_MSG_RESULT([... .. . ])
AC_C_CHARACTERISTICS_UMBRELLA
gl_C_MISC
AC_MSG_CHECKING([for some declarations...])
AC_MSG_RESULT([... .. . ])
dnl# might have to get rid of the "_ONCE"s if they jump elsewehere...
AC_CHECK_DECLS_ONCE([cuserid])dnl
AC_CHECK_DECLS_ONCE([exit_failure])dnl
AC_CHECK_DECLS_ONCE([program_invocation_name],[],[],
                    [#include <errno.h>])dnl
AC_CHECK_DECLS_ONCE([program_invocation_short_name],[],[],
                    [#include <errno.h>])dnl
AC_CHECK_DECLS_ONCE([kCFStringEncodingASCII])dnl
AC_CHECK_DECLS_ONCE([kCFPreferencesCurrentApplication])dnl
AC_CHECK_DECLS_ONCE([_STAT_VER])dnl
AC_MSG_CHECKING([for some types...])
AC_MSG_RESULT([... .. . ])
AC_CHECK_SIZEOF([char])dnl
AC_CHECK_ALIGNOF([char])dnl
AC_CHECK_SIZEOF([short])dnl
AC_CHECK_ALIGNOF([short])dnl
AC_CHECK_SIZEOF([int])dnl
AC_CHECK_ALIGNOF([int])dnl
AC_CHECK_SIZEOF([long])dnl
AC_CHECK_ALIGNOF([long])dnl
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
AC_CHECK_TYPES([ino_t])dnl
AC_CHECK_TYPES([key_t])dnl
AC_CHECK_TYPES([nfds_t])dnl
AC_CHECK_TYPES([nl_catd])dnl
AC_CHECK_TYPES([nl_item])dnl
  ## TODO: macro-ize:
if test "x${ac_cv_type_nlink_t}" = "x"; then
  test -z "${ac_cv_type_nlink_t}"
  AC_CHECK_TYPES([nlink_t])dnl
  ## ok
fi
if test "x${ac_cv_type_off_t}" = "xyes"; then
  AC_CHECK_SIZEOF([off_t])dnl
  AC_CHECK_ALIGNOF([off_t])dnl
  ## might be bigger than expected...
fi
AC_CHECK_TYPES([off64_t],[
  AC_CHECK_SIZEOF([off64_t])dnl
  AC_CHECK_ALIGNOF([off64_t])dnl
],[
  if test "x${ac_cv_type_off64_t}" != "x"; then
    test -n "${ac_cv_type_off64_t}" && unset ac_cv_type_off64_t
  fi
  if test "x${ac_cv_type_off_t}" = "xyes"; then
    _AC_CHECK_TYPE_OLD([off64_t],[off_t])
  elif test "x${ac_cv_type_long_long_int}" = "xyes"; then
    _AC_CHECK_TYPE_OLD([off64_t],[long long int])
  else
    _AC_CHECK_TYPE_OLD([off64_t],[long int])
  fi
])dnl
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
  ## avoid printing "(cached)" a bunch of times:
AC_CHECK_FUNCS_IF_NOT_CACHED([__fpending _NSGetExecutablePath abort btowc \
                              close dup2 fchdir fstatfs ftruncate getcwd \
                              getdelim getmnt getmntinfo getpagesize ioctl \
                              listmntent memchr mempcpy pathconf setenv \
                              setlocale snprintf strndup])
AC_CHECK_FUNCS_ONCE([readlinkat])dnl
  ## now regular function checks:
AC_CHECK_FUNCS([accept assert atexit atoi chsize clearenv connect \
                dladdr dupfd end execve fflush fgets freemntlist \
                fstatfs64 fstat64 ftok ftruncate64 fxstat64 \
                gencat getrlimit gettext getvfsbytype iswprint \
                kevent kevent64 kqueue localeconv lseek mblen mbrlen \
                mbtowc memmove memset mntctl posix_fallocate \
                pread64 pwrite64 printf read recv select send \
                shm_open shmat shmctl shmdt sprintf statfs statfs64 \
                strcasecmp strchr strdup strerror strncasecmp strrchr \
                strsep strspn strstr strtod strtoul system sysconf \
                vasprintf wctomb wcwidth write])dnl
  ## endianness functions:
AC_CHECK_FUNCS([htonl htons ntohl ntohs])dnl
  ## fstab-related functions:
AC_CHECK_FUNCS([getfsent getfsspec getfsfile setfsent endfsent])dnl
  ## ftw-related functions:
AC_CHECK_FUNCS([fts_open fts_children fts_close fts_read])dnl
  ## alternative ftw-related functions:
AC_CHECK_FUNCS([opendir readdir closedir])dnl
  ## IOKit/Kext function(s) (might need some special flags):
AC_CHECK_FUNCS([KextManagerLoadKextWithURL])dnl
  ## CoreFoundation functions (might need some special flags):
AC_CHECK_FUNCS([CFBundleCopyLocalizedString CFGetTypeID \
                CFLocaleGetIdentifier CFRelease CFStringCreateCopy \
                CFStringCreateMutable CFStringGetCString \
                CFStringGetSystemEncoding CFStringGetTypeID \
                CFStringRef])dnl
AC_CHECK_FUNCS_IF_NOT_CACHED([CFLocaleCopyCurrent \
                              CFPreferencesCopyAppValue])dnl
  ## functions that we might want replacements for, but do not have the
  ## source files to replace them yet:
dnl# (move from "_CHECK" to "_REPLACE" once we do have source files)
unset ac_cv_func_catgets
AC_CHECK_FUNCS([catopen catgets catclose crypt ecvt fcvt gcvt \
                setmntent addmntent endmntent \
                hasmntopt sbrk brk shmget swapon swapoff])
  ## functions that we might want replacements for, and have source files for:
unset ac_cv_func_btowc
unset ac_cv_func_wctob
unset ac_cv_func_getmntent
unset ac_cv_func_poll
AC_REPLACE_FUNCS([btowc wctob dysize fclose fcloseall getmntent poll \
                  cuserid])dnl
  ## keep autoscan happy:
if test "x" = "Y0"; then
  test -x "`which autoscan`" || echo "no autoscan!" >&2
  AC_CHECK_FUNCS([__fpending btowc dup2 fchdir ftruncate getcwd getdelim \
                  getpagesize memchr mempcpy pathconf setenv strndup])dnl
  ## should never actually get here though...
fi

# Output:
AC_CONFIG_FILES([Makefile \
autoscan/Makefile \
libftw0/Makefile \
poll/poll-emulator/Makefile
poll/poll-emulator/Makefile_nonAutomake])dnl
AC_CONFIG_SUBDIRS([argp/argp-standalone-1.3])dnl
AC_OUTPUT
