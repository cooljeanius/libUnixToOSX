TS_SH = ex1-test permute-test
TS_PROGS =

TS_ALL = $(TS_PROGS) $(TS_SH)

check_PROGRAMS = $(TS_PROGS) ex1 ex3 ex4

check_SCRIPTS = $(TS_SH) run-tests

TESTS = $(check_PROGRAMS) $(check_SCRIPTS)

AM_TESTS_FD_REDIRECT = 2>&1

## These just print usage information; not sure why that counts as a FAIL:
XFAIL_TESTS = ex3 ex4

LDADD = ../libargp.a

EXTRA_DIST = $(check_SCRIPTS)
CLEANFILES = test.out

.PHONY: check-local
check-local: $(TS_ALL) $(srcdir)/run-tests
	srcdir="$(srcdir)" $(srcdir)/run-tests $(TS_ALL)
