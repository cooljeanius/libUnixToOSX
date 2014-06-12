## automake Makefile for argp-standalone testsuite

TS_SH = ex1-test permute-test
TS_PROGS =

MY_TS_SH_HERE = ./ex1-test ./permute-test

TS_ALL = $(TS_PROGS) $(TS_SH)

check_PROGRAMS = $(TS_PROGS) ex1 ex3 ex4

ex1_SOURCES = ex1.c
ex3_SOURCES = ex3.c
ex4_SOURCES = ex4.c

check_SCRIPTS = $(TS_SH) run-tests
noinst_SCRIPTS = $(check_SCRIPTS)
check_DATA = $(MY_TS_SH_HERE)

TESTS = $(check_PROGRAMS) $(check_SCRIPTS)

TESTS_ENVIRONMENT = srcdir="$(srcdir)"

AM_TESTS_FD_REDIRECT = 2>&1

## These just print usage information; not sure why that counts as a FAIL:
XFAIL_TESTS = ex3 ex4
##FIXME: run-tests has some problems with the vpath used for distcheck:
SKIP_TESTS = run-tests
DISABLE_HARD_ERRORS = 1

AM_CPPFLAGS = -I.. -I$(top_srcdir)

LDADD = ../libargp.a

EXTRA_DIST = $(check_SCRIPTS)
CLEANFILES = test.out
DISTCLEANFILES = .DS_Store
BUILT_SOURCES = atconfig
MOSTLYCLEANFILES = @MAINT@ atconfig
DISTCLEANFILES += atconfig

atconfig: ../config.status
	(cd .. && $(SHELL) ./config.status testsuite/atconfig) || (cd $(top_builddir) && ./config.status ./testsuite/atconfig)

.PHONY: distclean-local
distclean-local:
	rm -rfv .deps || rmdir .deps

.PHONY: check-local
check-local: $(TS_ALL) $(srcdir)/run-tests atconfig Makefile
	$(MAKE) $(AM_MAKEFLAGS) $(MY_TS_SH_HERE)
	srcdir="$(srcdir)" $(srcdir)/run-tests $(TS_ALL)

run-tests: $(MY_TS_SH_HERE)
	if test "x$(srcdir)" != "x."; then \
	  if test -e $(srcdir)/$@ -a ! -e $@; then \
	    cp -v $(srcdir)/$@ .; \
	  fi; \
	fi

## even though the rule is the same, put it separately to avoid circular
## dependencies:
$(MY_TS_SH_HERE):
	if test "x$(srcdir)" != "x."; then \
	  if test -e $(srcdir)/$@ -a ! -e $@; then \
	    cp -v $(srcdir)/$@ .; \
	  fi; \
	fi

../libargp.a: ../Makefile
	if test -e ../Makefile; then $(MAKE) -C .. libargp.a; fi
