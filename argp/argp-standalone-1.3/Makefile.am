# From glibc

# Copyright (C) 1997, 2003, 2004 Free Software Foundation, Inc.
# This file is part of the GNU C Library.

# The GNU C Library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public License as
# published by the Free Software Foundation; either version 2 of the
# License, or (at your option) any later version.

# The GNU C Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.

# You should have received a copy of the GNU Library General Public
# License along with the GNU C Library; see the file COPYING.LIB.  If
# not, write to the Free Software Foundation, Inc.,
# 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

## inherit macros from parent project:
ACLOCAL_AMFLAGS = -I../../m4 --system-acdir=/sw/share/gnulib/m4 --install
AUTOMAKE_OPTIONS = 1.8 foreign no-dependencies subdir-objects
SUBDIRS = . testsuite

LIBOBJS = @LIBOBJS@

noinst_LIBRARIES = libargp.a
check_PROGRAMS = argp-test
TESTS = $(check_PROGRAMS)
noinst_HEADERS = argp.h argp-fmtstream.h argp-namefrob.h # argp-comp.h

EXTRA_DIST = mempcpy.c strchrnul.c strndup.c Versions ../TODO

## Leaves out argp-fs-xinl.c and argp-xinl.c (which do NOT exist here):
libargp_a_SOURCES = argp-ba.c argp-eexst.c argp-fmtstream.c \
		    argp-help.c argp-parse.c argp-pv.c \
		    argp-pvh.c argp-stdint.h

libargp_a_LIBADD = $(LIBOBJS)

argp_test_LDADD = libargp.a

AM_CPPFLAGS = -I../..

DISTCLEANFILES = .DS_Store ../.DS_Store *~ autoscan.log

EXTRA_DIST += ../../rawmemchr.h

BUILT_SOURCES = argp-stdint.h

MOSTLYCLEANFILES = @MAINT@ argp-stdint.h

DISTCLEANFILES += argp-stdint.h

## extend the automake verbosity control:
AM_V_v = $(am__v_v_@AM_V@)
am__v_v_ = $(am__v_v_@AM_DEFAULT_V@)
am__v_v_0 =
am__v_v_1 = -v

argp-stdint.h: stamp-h1
	@test -f $@ || rm -f $<
	@test -f $@ || $(MAKE) $(AM_MAKEFLAGS) $<
	@test -f $@ || (cd $(top_builddir) && $(SHELL) ./config.status $@)

## distcheck puts some stuff a level above here, but be careful and only
## clean these files if they still have their originals in the proper
## places (further down in this rule):
.PHONY: distclean-local
distclean-local:
	rm -f $(AM_V_v) @PACKAGE_TARNAME@-@PACKAGE_VERSION@.tar.gz
	rm -rf $(AM_V_v) autom4te.cache || rmdir autom4te.cache
	rm -rf $(AM_V_v) .deps || rmdir .deps
	-(test -w @PACKAGE_TARNAME@-@PACKAGE_VERSION@ && (rm -rf @PACKAGE_TARNAME@-@PACKAGE_VERSION@ || rmdir @PACKAGE_TARNAME@-@PACKAGE_VERSION@)) || stat @PACKAGE_TARNAME@-*.* || echo "it can be difficult to distclean the results of distcheck"
	-(find . -name .DS_Store -delete 2>&1) || test -x "`which find`"
	if ((test -e mempcpy.c || test -e ../../mempcpy.c) && test -w ../mempcpy.c); then \
	  rm -f $(AM_V_v) ../mempcpy.c; \
	fi
	if ((test -e strchrnul.c || test -e ../../strchrnul.c) && test -w ../strchrnul.c); then \
	  rm -f $(AM_V_v) ../strchrnul.c; \
	fi
	if ((test -e strndup.c || test -e ../../strndup.c) && test -w ../strndup.c); then \
	  rm -f $(AM_V_v) ../strndup.c; \
	fi
	if (test -e ../../malloc.c && test -w ../malloc.c); then \
	  rm -f $(AM_V_v) ../malloc.c; \
	fi
	if (test -e ../../rawmemchr.c && test -w ../rawmemchr.c); then \
	  rm -f $(AM_V_v) ../rawmemchr.c; \
	fi
	if (test -e ../../rawmemchr.h && test -w ../rawmemchr.h); then \
	  rm -f $(AM_V_v) ../rawmemchr.h; \
	fi
	if (test -e ../../realloc.c && test -w ../realloc.c); then \
	  rm -f $(AM_V_v) ../realloc.c; \
	fi
	if (test -e ../../strnlen.c && test -w ../strnlen.c); then \
	  rm -f $(AM_V_v) ../strnlen.c; \
	fi
	if (test -d ../../m4 && test -w ../m4); then \
	  (rm -rf $(AM_V_v) ../m4 || rmdir ../m4); \
	fi
	if (test -d ../../build-aux && test -w ../build-aux); then \
	  (rm -rf $(AM_V_v) ../build-aux || rmdir ../build-aux); \
	fi

nodist_noinst_DATA = @MAINT@ configure.scan
configure.scan: @MAINT@ distclean-local
	autoscan || (touch configure.scan && mkdir autom4te.cache)

MAINTAINERCLEANFILES = configure.scan

headers: $(BUILT_SOURCES)
	ls *.h
.PHONY: headers

## ---------- ##
## ansi2knr.  ##
## ---------- ##

EXTRA_DIST += ansi2knr.c ansi2knr.1

noinst_MANS = ansi2knr.1

## Substitution from AM_ANSI_C_PROTOTYPES. This makes it be built only when
## necessary.
ANSI2KNR = @ANSI2KNR@
ansi2knr: ansi2knr.$(OBJEXT)
	$(AM_V_CCLD)$(LINK) ansi2knr.$(OBJEXT) $(LIBS)
ansi2knr.$(OBJEXT): ansi2knr.c $(CONFIG_HEADER)

## ------------------- ##
## Cleaning ansi2knr.  ##
## ------------------- ##

.PHONY: clean-krextra

clean-local: clean-krextra
clean-krextra:
## Why `clean' and not somewhere else?  Not `mostlyclean' because
## people usually do NOT want to recompile this file. And not
## `distclean' because of our informal rule: if `make' built it, then
## `clean' should delete it; if `configure' built it, then `distclean'
## should remove it (and if the maintainer built it, then
## maintainer-clean should remove it).
	-rm -f ansi2knr

## --------------------------------- ##
## Cleaning the output of ansi2knr.  ##
## --------------------------------- ##

.PHONY: mostlyclean-kr

mostlyclean-local: mostlyclean-kr
mostlyclean-kr:
## Only delete *_.c when ansi2knr is actually in use, so as to avoid
## deleting sources that happen to end in "_" after being truncated on a
## DOS 8.3 filesystem with srcdir==builddir.
	-test "$U" = "" || rm -f *_.c

###########################################################################
### seeing as we specify the "no-dependencies" option in our automake
### options, manually list dependencies here:
## (ansi2knr.$(OBJEXT) is done above)
argp-ba.o: argp-ba.c
argp-eexst.o: argp-eexst.c config.h argp.h
argp-fmtstream.o: argp-fmtstream.c config.h argp-fmtstream.h argp.h \
  argp-namefrob.h
argp-help.o: argp-help.c config.h argp.h argp-fmtstream.h argp-namefrob.h
argp-parse.o: argp-parse.c config.h argp.h argp-namefrob.h
argp-pv.o: argp-pv.c
argp-pvh.o: argp-pvh.c
argp-test.o: argp-test.c config.h argp.h
mempcpy.o: mempcpy.c
strchrnul.o: strchrnul.c
strndup.o: strndup.c
