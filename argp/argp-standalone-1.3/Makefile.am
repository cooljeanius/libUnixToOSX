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

# inherit macros from parent project:
ACLOCAL_AMFLAGS = -I../../m4 --system-acdir=/sw/share/gnulib/m4 --install
AUTOMAKE_OPTIONS = 1.8 foreign subdir-objects
SUBDIRS = . testsuite

LIBOBJS = @LIBOBJS@

noinst_LIBRARIES = libargp.a
check_PROGRAMS = argp-test
noinst_HEADERS = argp.h argp-fmtstream.h argp-namefrob.h # argp-comp.h

EXTRA_DIST = mempcpy.c strchrnul.c strndup.c Versions

# Leaves out argp-fs-xinl.c and argp-xinl.c 
libargp_a_SOURCES = argp-ba.c argp-eexst.c argp-fmtstream.c \
		    argp-help.c argp-parse.c argp-pv.c \
		    argp-pvh.c

libargp_a_LIBADD = $(LIBOBJS)

argp_test_LDADD = libargp.a

## ---------- ##
## ansi2knr.  ##
## ---------- ##

## Substitution from AM_ANSI_C_PROTOTYPES. This makes it be built only when
## necessary.
ANSI2KNR = @ANSI2KNR@
ansi2knr: ansi2knr.$(OBJEXT)
	$(LINK) ansi2knr.$(OBJEXT) $(LIBS)
ansi2knr.$(OBJEXT): $(CONFIG_HEADER)

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
