# Makefile for poll(2) emulator
#
# $Id$
#--------------------------------------------------------------------------
###########################################################################
# Definitions that you need to edit:
###########################################################################
#--------------------------------------------------------------------------
# Installation prefix:
MYPREFIX = @prefix@
LIBDIR = $(MYPREFIX)/lib
INCDIR = $(MYPREFIX)/include/sys

#--------------------------------------------------------------------------
# Platform-specific bits:
#

########
# *BSD #
########
# For GNU CC on *BSD. Should work for FreeBSD, NetBSD, OpenBSD and BSD/OS

############
# Mac OS X #
############
# Benjamin Reed <ranger@befunk.com>:
# On Mac OS X, comment out the above lines, and uncomment these instead.
LINK_SHARED = $(CC) $(LDFLAGS) -install_name $(MYPREFIX)/lib/$(SHLIB) \
	      -compatibility_version $(COMPAT_VERSION) \
	      -current_version $(VERSION) -dynamiclib
SHLIB_EXT = dylib
SHLIB_NOVER = $(LIB_NAME).$(SHLIB_EXT)
SHLIB = $(LIB_NAME).$(VERSION).$(SHLIB_EXT)
SHLIB_INSTALLED	= $(LIBDIR)/$(LIB_NAME).$(MAJOR).$(SHLIB_EXT)

# NOTE: If you have linkage problems on the Mac (see the POSSIBLE ISSUES
# section in the INSTALL file), uncomment the following definition. Be sure
# to use the same -D option when compiling source code that uses this
# library. (ok, uncommented)
POLL_RENAME = -Dpoll=pollemu

#--------------------------------------------------------------------------
# If you have a BSD-compatible install(1), use:
INSTALL = install -c

# If you do not have a BSD-compatible install(1), use:
INSTALL_SH = ./install.sh -c

#--------------------------------------------------------------------------
# Compilation and Linkage:
MAJOR = 1
MINOR = 5
MICRO = 1
VERSION = $(MAJOR).$(MINOR).$(MICRO)
COMPAT_VERSION = 1.5
CC = @CC@
LIB_NAME = libpoll_static
LIB = $(LIB_NAME).a
CFLAGS = @CFLAGS@ @WARN_CFLAGS@
COMPILE_STATIC = $(CC) $(CFLAGS) -c 
COMPILE_SHARED = $(CC) $(CFLAGS) -c -fPIC 
RANLIB = @RANLIB@
CPPFLAGS = $(POLL_RENAME)
AR = @AR@
ARFLAGS = rv

## automake-specific things:
check_PROGRAMS = polltest
polltest_SOURCES = polltest.c pollemu.h
lib_LIBRARIES = libpoll.a
libpoll_a_SOURCES = pollemu.c pollemu.h
lib_LTLIBRARIES = libpoll_lt.la
libpoll_lt_la_SOURCES = $(libpoll_a_SOURCES)
libpoll_lt_la_CFLAGS = $(CFLAGS) $(CPPFLAGS)
# libtool versioning is messed up and inconsistent with what is intuitive:
libpoll_lt_la_LDFLAGS = -version-info 0:$(MINOR):0
polltest_LDADD = libpoll_lt.la
sysincdir = $(prefix)/include/sys
sysinc_HEADERS = pollemu.h
DISTCLEANFILES = .DS_Store
EXTRA_DIST = CHANGELOG.md LICENSE Makefile_hardcoded README.md
dist_noinst_SCRIPTS = install.sh

###########################################################################
# There should be no need to edit past this point, unless...
###########################################################################

SUFFIXES = .po .ao

.c.po:
	$(AM_V_CC)$(COMPILE_SHARED) $(CPPFLAGS) $< -o $*.po
.c.ao:
	$(AM_V_CC)$(COMPILE_STATIC) $(CPPFLAGS) $< -o $*.ao

all: libs
.PHONY: all
libs: $(SHLIB) $(LIB)
.PHONY: libs
test: polltest
.PHONY: test
check-local: test
.PHONY: check-local

dirs:
	@echo "creating directories..."
	$(INSTALL) -m 755 -d $(LIBDIR)
	$(INSTALL) -m 755 -d $(INCDIR)
.PHONY: dirs

install_pollemu: all dirs
	$(INSTALL) -m 755 $(SHLIB) $(LIB) $(LIBDIR)
	$(LN_S) -fv $(SHLIB) $(SHLIB_INSTALLED)
	$(LN_S) -fv $(SHLIB) $(LIBDIR)/$(SHLIB_NOVER)
	$(INSTALL_DATA) pollemu.h $(INCDIR)
.PHONY: install_pollemu

clean-local:
	-rm -fv *.po *.o *.ao $(LIB) $(SHLIB) $(SHLIB_NOVER) polltest
.PHONY: clean-local
distclean-local: clean-local
.PHONY: distclean-local
mostlyclean-local: clean-local
.PHONY: mostlyclean-local

$(SHLIB): pollemu.po
	$(AM_V_CCLD)$(LINK_SHARED) -o $@ $<
$(LIB): pollemu.ao
	$(AR) $(ARFLAGS) $@ $<
build_polltest_manually: polltest.o $(LIB)
	$(AM_V_CC)$(CC) $(CFLAGS) -o polltest $< $(LIB)
.PHONY: build_polltest_manually
