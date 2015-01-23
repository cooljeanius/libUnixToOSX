# manywarnings.m4 serial 6
dnl# Copyright (C) 2008-2012 Free Software Foundation, Inc.
dnl# This file is free software; the Free Software Foundation
dnl# gives unlimited permission to copy and/or distribute it,
dnl# with or without modifications, as long as this notice is preserved.

dnl# From Simon Josefsson

# gl_MANYWARN_COMPLEMENT(OUTVAR, LISTVAR, REMOVEVAR)
# --------------------------------------------------
# Copy LISTVAR to OUTVAR except for the entries in REMOVEVAR.
# Elements separated by whitespace.  In set logic terms, the function
# does OUTVAR = LISTVAR \ REMOVEVAR.
AC_DEFUN([gl_MANYWARN_COMPLEMENT],
[
  gl_warn_set=""
  set x $2; shift
  for gl_warn_item
  do
    case " $3 " in
      *" ${gl_warn_item} "*)
        ;;
      *)
        gl_warn_set="${gl_warn_set} ${gl_warn_item}"
        ;;
    esac
  done
  $1=${gl_warn_set}
])dnl

# gl_MANYWARN_ALL_GCC(VARIABLE)
# -----------------------------
# Add all documented GCC warning parameters to variable VARIABLE.
# Note that you need to test them using gl_WARN_ADD if you want to
# make sure your gcc understands it.
AC_DEFUN([gl_MANYWARN_ALL_GCC],
[
  dnl# First, check if -Wno-missing-field-initializers is needed.
  dnl# -Wmissing-field-initializers is implied by -W, but that issues
  dnl# warnings with GCC version before 4.7, for the common idiom
  dnl# of initializing types on the stack to zero, using { 0, }
  AC_REQUIRE([AC_PROG_CC])
  if test -n "${GCC}"; then

    dnl# First, check -W -Werror -Wno-missing-field-initializers is
    dnl# supported with the current $CC $CFLAGS $CPPFLAGS.
    AC_MSG_CHECKING([whether -Wno-missing-field-initializers is supported])
    AC_CACHE_VAL([gl_cv_cc_nomfi_supported],[
      gl_save_CFLAGS="${CFLAGS}"
      CFLAGS="${CFLAGS} -W -Werror -Wno-missing-field-initializers"
      AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
                        [gl_cv_cc_nomfi_supported=yes],
                        [gl_cv_cc_nomfi_supported=no])
      CFLAGS="${gl_save_CFLAGS}"])
    AC_MSG_RESULT([${gl_cv_cc_nomfi_supported}])dnl

    if test "x${gl_cv_cc_nomfi_supported}" = "xyes"; then
      dnl# Now check whether -Wno-missing-field-initializers is needed
      dnl# for the { 0, } construct.
      AC_MSG_CHECKING([whether -Wno-missing-field-initializers is needed])
      AC_CACHE_VAL([gl_cv_cc_nomfi_needed],[
        gl_save_CFLAGS="$CFLAGS"
        CFLAGS="$CFLAGS -W -Werror"
        AC_COMPILE_IFELSE(
          [AC_LANG_PROGRAM(
             [[void f (void)
               {
                 typedef struct { int a; int b; } s_t;
                 s_t s1 = { 0, };
               }
             ]],
             [[]])],
          [gl_cv_cc_nomfi_needed=no],
          [gl_cv_cc_nomfi_needed=yes])
        CFLAGS="${gl_save_CFLAGS}"
      ])
      AC_MSG_RESULT([${gl_cv_cc_nomfi_needed}])
    fi

    dnl# Next, check if -Werror -Wuninitialized is useful with the
    dnl# user's choice of ${CFLAGS}; some versions of gcc warn that it
    dnl# has no effect if -O is not also used
    AC_MSG_CHECKING([whether -Wuninitialized is supported])
    AC_CACHE_VAL([gl_cv_cc_uninitialized_supported],[
      gl_save_CFLAGS="${CFLAGS}"
      CFLAGS="${CFLAGS} -Werror -Wuninitialized"
      AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([[]],[[]])],
        [gl_cv_cc_uninitialized_supported=yes],
        [gl_cv_cc_uninitialized_supported=no])
      CFLAGS="${gl_save_CFLAGS}"])
    AC_MSG_RESULT([${gl_cv_cc_uninitialized_supported}])

  fi

  # List all gcc warning categories.
  # To compare this list to your installed GCC's, run this Bash command:
  #
  # comm -3 \
  #  <(sed -n 's/^  *\(-[^ ]*\) .*/\1/p' manywarnings.m4 | sort) \
  #  <(gcc --help=warnings | sed -n 's/^  \(-[^ ]*\) .*/\1/p' | sort |
  #      grep -v -x -f <(
  #         awk '/^[^#]/ {print $1}' ../build-aux/gcc-warning.spec))

  gl_manywarn_set=""
  for gl_manywarn_item in \
    -W \
    -Wabi \
    -Waddress \
    -Waggregate-return \
    -Waggressive-loop-optimizations \
    -Wall \
    -Warray-bounds \
    -Wattributes \
    -Wbad-function-cast \
    -Wbuiltin-macro-redefined \
    -Wcast-align \
    -Wcast-qual \
    -Wchar-subscripts \
    -Wclobbered \
    -Wcomment \
    -Wcomments \
    -Wconversion \
    -Wcoverage-mismatch \
    -Wcpp \
    -Wc++-compat \
    -Wdate-time \
    -Wdeclaration-after-statement \
    -Wdeprecated \
    -Wdeprecated-declarations \
    -Wdisabled-optimization \
    -Wdiscarded-qualifiers \
    -Wdiv-by-zero \
    -Wdouble-promotion \
    -Wempty-body \
    -Wendif-labels \
    -Wenum-compare \
    -Wextra \
    -Wfloat-conversion \
    -Wfloat-equal \
    -Wformat-contains-nul \
    -Wformat-extra-args \
    -Wformat-nonliteral \
    -Wformat-security \
    -Wformat-signedness \
    -Wformat-y2k \
    -Wformat-zero-length \
    -Wformat=2 \
    -Wfree-nonheap-object \
    -Wignored-qualifiers \
    -Wimplicit \
    -Wimplicit-function-declaration \
    -Wimplicit-int \
    -Winit-self \
    -Winline \
    -Wint-to-pointer-cast \
    -Winvalid-memory-model \
    -Winvalid-pch \
    -Wjump-misses-init \
    -Wlogical-not-parentheses \
    -Wlogical-op \
    -Wlong-long \
    -Wmain \
    -Wmaybe-uninitialized \
    -Wmissing-braces \
    -Wmissing-declarations \
    -Wmissing-field-initializers \
    -Wmissing-format-attribute \
    -Wmissing-include-dirs \
    -Wmissing-noreturn \
    -Wmissing-parameter-type \
    -Wmissing-prototypes \
    -Wmudflap \
    -Wmultichar \
    -Wnarrowing \
    -Wnested-externs \
    -Wnonnull \
    -Wold-style-declaration \
    -Wold-style-definition \
    -Wopenmp-simd \
    -Woverflow \
    -Woverlength-strings \
    -Woverride-init \
    -Wpacked \
    -Wpacked-bitfield-compat \
    -Wpadded \
    -Wparentheses \
    -Wpedantic \
    -Wpedantic-ms-format \
    -Wpointer-arith \
    -Wpointer-sign \
    -Wpointer-to-int-cast \
    -Wpragmas \
    -Wredundant-decls \
    -Wreturn-local-addr \
    -Wreturn-type \
    -Wsequence-point \
    -Wshadow \
    -Wshadow-ivar \
    -Wsign-compare \
    -Wsign-conversion \
    -Wsizeof-pointer-memaccess \
    -Wstack-protector \
    -Wstrict-aliasing \
    -Wstrict-overflow \
    -Wstrict-prototypes \
    -Wsuggest-attribute=const \
    -Wsuggest-attribute=format \
    -Wsuggest-attribute=noreturn \
    -Wsuggest-attribute=pure \
    -Wswitch \
    -Wswitch-bool \
    -Wswitch-default \
    -Wswitch-enum \
    -Wsync-nand \
    -Wsystem-headers \
    -Wtraditional \
    -Wtraditional-conversion \
    -Wtrampolines \
    -Wtrigraphs \
    -Wtype-limits \
    -Wundef \
    -Wuninitialized \
    -Wunknown-pragmas \
    -Wunreachable-code \
    -Wunsafe-loop-optimizations \
    -Wunsuffixed-float-constants \
    -Wunused \
    -Wunused-but-set-parameter \
    -Wunused-but-set-variable \
    -Wunused-function \
    -Wunused-label \
    -Wunused-local-typedefs \
    -Wunused-macros \
    -Wunused-parameter \
    -Wunused-result \
    -Wunused-value \
    -Wunused-variable \
    -Wvarargs \
    -Wvariadic-macros \
    -Wvector-operation-performance \
    -Wvla \
    -Wvolatile-register-var \
    -Wwrite-strings \
     \
    \
    ; do
    gl_manywarn_set="${gl_manywarn_set} ${gl_manywarn_item}"
  done

  # gcc --help=warnings outputs an unusual form for this option; list
  # it here so that the above 'comm' command does NOT report a false match:
  gl_manywarn_set="${gl_manywarn_set} -Wnormalized=nfkc"

  AC_LANG_CASE([C++],[
    for gl_manywarn_cplusplus_item in \
      -Wabi-tag \
      -Wc++0x-compat \
      -Wc++11-compat \
      -Wconditionally-supported \
      -Wconversion-null \
      -Wctor-dtor-privacy \
      -Wdelete-incomplete \
      -Wdelete-non-virtual-dtor \
      -Weffc++ \
      -Winherited-variadic-ctor \
      -Winvalid-offsetof \
      -Wliteral-suffix \
      -Wnoexcept \
      -Wnon-template-friend \
      -Wold-style-cast \
      -Woverloaded-virtual \
      -Wpmf-conversions \
      -Wreorder \
      -Wsign-promo \
      -Wstrict-null-sentinel \
      -Wuseless-cast \
      -Wvirtual-move-assign \
      -Wzero-as-null-pointer-constant \
      \
      ; do
      gl_manywarn_set="${gl_manywarn_set} ${gl_manywarn_cplusplus_item}"
    done
  ])dnl

  # These are needed for older GCC versions.
  if test -n "${GCC}"; then
    case `(${CC} --version) 2>/dev/null` in
      'gcc (GCC) '[[0-3]].* | \
      'gcc (GCC) '4.[[0-7]].*)
        gl_manywarn_set="${gl_manywarn_set} -fdiagnostics-show-option"
        gl_manywarn_set="${gl_manywarn_set} -funit-at-a-time"
          ;;
    esac
  fi

  # Disable the missing-field-initializers warning if needed:
  if test "x${gl_cv_cc_nomfi_needed}" = "xyes"; then
    gl_manywarn_set="${gl_manywarn_set} -Wno-missing-field-initializers"
  fi

  # Likewise with the unintialized-variable warning:
  if test "x${gl_cv_cc_uninitialized_supported}" = "xno"; then
    gl_manywarn_set="${gl_manywarn_set} -Wno-uninitialized"
  fi

  $1=${gl_manywarn_set}
])dnl
