AM_CFLAGS = -fno-common
AM_CPPFLAGS = -I.
AM_ARFLAGS = r
AM_LDFLAGS = -dynamiclib

lib_LTLIBRARIES = libftw.la

include_HEADERS = ftw.h

libftw_la_SOURCES = ftw.c ftw.h
libftw_la_LDFLAGS = -version-info 1:1:0

EXTRA_DIST = README LICENSE

all: libftw.0.dylib libftw.dylib libftw.a

libftw.0.1.0.dylib: ftw.o
	$(CC) $(AM_LDFLAGS) -install_name ${libdir}/libftw.0.dylib -compatibility_version 1 -current_version 1 -o $@ $<

libftw.0.dylib libftw.dylib: libftw.0.1.0.dylib
	$(LN_S) $< $@

libftw.a: ftw.o $(libftw_la_SOURCES)
	$(AR) $(AM_ARFLAGS) $@ $<
	$(RANLIB) $@

CLEANFILES = libftw.0.1.0.dylib libftw.0.dylib libftw.dylib libftw.a
