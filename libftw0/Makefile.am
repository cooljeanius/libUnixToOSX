## automake Makefile for libUnixToOSX/libftw0

AUTOMAKE_OPTIONS = foreign no-dependencies

## WARN_CFLAGS is subst-ed by all the calls to "gl_WARN_ADD":
AM_WARNFLAGS = $(WARN_CFLAGS)
AM_CFLAGS = -fno-common $(AM_WARNFLAGS)
AM_CPPFLAGS = -I.
AM_ARFLAGS = r
AM_LDFLAGS = -dynamiclib

lib_LTLIBRARIES = libftw.la

include_HEADERS = ftw.h

libftw_la_SOURCES = ftw.c ftw.h
libftw_la_LDFLAGS = -version-info 1:1:0

EXTRA_DIST = README LICENSE @MAINT@ Fink/libftw0.info Fink/libftw0.patch

## extend the automake verbosity control:
AM_V_v = $(am__v_v_@AM_V@)
am__v_v_ = $(am__v_v_@AM_DEFAULT_V@)
am__v_v_0 =
am__v_v_1 = -v

all: libftw.0$(SOEXT) libftw$(SOEXT) libftw.a

libftw.0.1.0.dylib: ftw.o
	$(AM_V_CCLD)$(CC) $(AM_LDFLAGS) -install_name ${libdir}/libftw.0.dylib -compatibility_version 1 -current_version 1 -o $@ $<

libftw.0.dylib libftw.dylib: libftw.0.1.0.dylib
	$(LN_S) -f $(AM_V_v) $< $@

libftw.a: ftw.o $(libftw_la_SOURCES)
	$(AR) $(AM_ARFLAGS) $@ $<
	$(RANLIB) $@

CLEANFILES = libftw.0.1.0.dylib libftw.0.dylib libftw.dylib libftw.a

DISTCLEANFILES = .DS_Store

## seeing as we specify the "no-dependencies" option in our automake
## options, manually list dependencies here:
ftw.o: ftw.c ftw.h
