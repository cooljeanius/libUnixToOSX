AUTOMAKE_OPTIONS = 1.6 foreign no-dependencies subdir-objects

ACLOCAL_AMFLAGS = -I m4 --system-acdir=/sw/share/gnulib/m4 --install

AM_CFLAGS = -Wall -Wimplicit

lib_LTLIBRARIES = libUnixToOSX.la

include_HEADERS = ftw_Apple.h
noinst_HEADERS = alloc.h dup.h dysize.h fclose.h
libUnixToOSX_la_SOURCES = alloc.h ftw_Apple.c ftw_Apple.h dup.h dysize.h \
			  fclose.h
libUnixToOSX_la_LIBADD = $(LTLIBOBJS) $(ALLOCA)

EXTRA_DIST = Readme.md

SUBDIRS = libftw0 autoscan poll/poll-emulator argp/argp-standalone-1.3

MOSTLYCLEANFILES = .DS_Store

BUILT_SOURCES = config.h

BUILT_SOURCES += $(ALLOCA_H)

# We need the following in order to create <alloca.h> when the system
# does NOT have one that works with the given compiler.
if GL_GENERATE_ALLOCA_H
alloca.h: alloca.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  cat $(srcdir)/alloca.in.h; \
	} > $@-t && \
	mv -f $@-t $@
else
alloca.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += alloca.h alloca.h-t

BUILT_SOURCES += fcntl.h

# The BUILT_SOURCES created by this Makefile snippet are not used via
# "#include" statements but through direct file reference. Therefore this
# snippet must be present in all Makefile.am that need it. This is ensured
# by the applicability of 'all' defined above.

BUILT_SOURCES += c++defs.h
# The c++defs.h that gets inserted into generated .h files is the same as
# build-aux/snippet/c++defs.h, except that it has the copyright header cut
# off.
c++defs.h: $(top_srcdir)/build-aux/snippet/c++defs.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	sed -n -e '/_GL_CXXDEFS/,$$p' \
	  < $(top_srcdir)/build-aux/snippet/c++defs.h \
	  > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += c++defs.h c++defs.h-t

CXXDEFS_H = c++defs.h

# The BUILT_SOURCES created by this Makefile snippet are not used via
# "#include" statements but through direct file reference. Therefore this
# snippet must be present in all Makefile.am that need it. This is ensured
# by the applicability of 'all' defined above.

BUILT_SOURCES += arg-nonnull.h
# The arg-nonnull.h that gets inserted into generated .h files is the same
# as build-aux/snippet/arg-nonnull.h, except that it has the copyright
# header cut off.
arg-nonnull.h: $(top_srcdir)/build-aux/snippet/arg-nonnull.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	sed -n -e '/GL_ARG_NONNULL/,$$p' \
	  < $(top_srcdir)/build-aux/snippet/arg-nonnull.h \
	  > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += arg-nonnull.h arg-nonnull.h-t

ARG_NONNULL_H = arg-nonnull.h

BUILT_SOURCES += warn-on-use.h
# The warn-on-use.h that gets inserted into generated .h files is the same
# as build-aux/snippet/warn-on-use.h, except that it has the copyright
# header cut off.
warn-on-use.h: $(top_srcdir)/build-aux/snippet/warn-on-use.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	sed -n -e '/^.ifndef/,$$p' \
	  < $(top_srcdir)/build-aux/snippet/warn-on-use.h \
	  > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += warn-on-use.h warn-on-use.h-t

WARN_ON_USE_H = warn-on-use.h

# We need the following in order to create <fcntl.h> when the system
# does NOT have one that works with the given compiler.
fcntl.h: fcntl.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(ARG_NONNULL_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_FCNTL_H''@|$(NEXT_FCNTL_H)|g' \
	      -e 's/@''GNULIB_FCNTL''@/$(GNULIB_FCNTL)/g' \
	      -e 's/@''GNULIB_NONBLOCKING''@/$(GNULIB_NONBLOCKING)/g' \
	      -e 's/@''GNULIB_OPEN''@/$(GNULIB_OPEN)/g' \
	      -e 's/@''GNULIB_OPENAT''@/$(GNULIB_OPENAT)/g' \
	      -e 's|@''HAVE_FCNTL''@|$(HAVE_FCNTL)|g' \
	      -e 's|@''HAVE_OPENAT''@|$(HAVE_OPENAT)|g' \
	      -e 's|@''REPLACE_FCNTL''@|$(REPLACE_FCNTL)|g' \
	      -e 's|@''REPLACE_OPEN''@|$(REPLACE_OPEN)|g' \
	      -e 's|@''REPLACE_OPENAT''@|$(REPLACE_OPENAT)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)' \
	      < $(srcdir)/fcntl.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += fcntl.h fcntl.h-t

BUILT_SOURCES += $(GETOPT_H)

# We need the following in order to create <getopt.h> when the system
# does NOT have one that works with the given compiler.
getopt.h: getopt.in.h $(top_builddir)/config.status $(ARG_NONNULL_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's|@''HAVE_GETOPT_H''@|$(HAVE_GETOPT_H)|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_GETOPT_H''@|$(NEXT_GETOPT_H)|g' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      < $(srcdir)/getopt.in.h; \
	} > $@-t && \
	mv -f $@-t $@
MOSTLYCLEANFILES += getopt.h getopt.h-t

BUILT_SOURCES += poll.h

# We need the following in order to create <poll.h> when the system
# does NOT have one.
poll.h: poll.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's|@''HAVE_POLL_H''@|$(HAVE_POLL_H)|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_POLL_H''@|$(NEXT_POLL_H)|g' \
	      -e 's/@''GNULIB_POLL''@/$(GNULIB_POLL)/g' \
	      -e 's|@''HAVE_POLL''@|$(HAVE_POLL)|g' \
	      -e 's|@''REPLACE_POLL''@|$(REPLACE_POLL)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)' \
	      < $(srcdir)/poll.in.h; \
	} > $@-t && \
	mv -f $@-t $@
MOSTLYCLEANFILES += poll.h poll.h-t

BUILT_SOURCES += dirent.h

# We need the following in order to create <dirent.h> when the system
# does NOT have one that works with the given compiler.
dirent.h: dirent.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(ARG_NONNULL_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's|@''HAVE_DIRENT_H''@|$(HAVE_DIRENT_H)|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_DIRENT_H''@|$(NEXT_DIRENT_H)|g' \
	      -e 's/@''GNULIB_OPENDIR''@/$(GNULIB_OPENDIR)/g' \
	      -e 's/@''GNULIB_READDIR''@/$(GNULIB_READDIR)/g' \
	      -e 's/@''GNULIB_REWINDDIR''@/$(GNULIB_REWINDDIR)/g' \
	      -e 's/@''GNULIB_CLOSEDIR''@/$(GNULIB_CLOSEDIR)/g' \
	      -e 's/@''GNULIB_DIRFD''@/$(GNULIB_DIRFD)/g' \
	      -e 's/@''GNULIB_FDOPENDIR''@/$(GNULIB_FDOPENDIR)/g' \
	      -e 's/@''GNULIB_SCANDIR''@/$(GNULIB_SCANDIR)/g' \
	      -e 's/@''GNULIB_ALPHASORT''@/$(GNULIB_ALPHASORT)/g' \
	      -e 's/@''HAVE_OPENDIR''@/$(HAVE_OPENDIR)/g' \
	      -e 's/@''HAVE_READDIR''@/$(HAVE_READDIR)/g' \
	      -e 's/@''HAVE_REWINDDIR''@/$(HAVE_REWINDDIR)/g' \
	      -e 's/@''HAVE_CLOSEDIR''@/$(HAVE_CLOSEDIR)/g' \
	      -e 's|@''HAVE_DECL_DIRFD''@|$(HAVE_DECL_DIRFD)|g' \
	      -e 's|@''HAVE_DECL_FDOPENDIR''@|$(HAVE_DECL_FDOPENDIR)|g' \
	      -e 's|@''HAVE_FDOPENDIR''@|$(HAVE_FDOPENDIR)|g' \
	      -e 's|@''HAVE_SCANDIR''@|$(HAVE_SCANDIR)|g' \
	      -e 's|@''HAVE_ALPHASORT''@|$(HAVE_ALPHASORT)|g' \
	      -e 's|@''REPLACE_OPENDIR''@|$(REPLACE_OPENDIR)|g' \
	      -e 's|@''REPLACE_CLOSEDIR''@|$(REPLACE_CLOSEDIR)|g' \
	      -e 's|@''REPLACE_DIRFD''@|$(REPLACE_DIRFD)|g' \
	      -e 's|@''REPLACE_FDOPENDIR''@|$(REPLACE_FDOPENDIR)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)' \
	      < $(srcdir)/dirent.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += dirent.h dirent.h-t

# The BUILT_SOURCES created by this Makefile snippet are not used via
# "#include" statements but through direct file reference. Therefore this
# snippet must be present in all Makefile.am that need it. This is ensured
# by the applicability of 'all' defined above.

BUILT_SOURCES += unused-parameter.h
# The unused-parameter.h that gets inserted into generated .h files is the
# same as build-aux/snippet/unused-parameter.h, except that it has the
# copyright header cut off.
unused-parameter.h: $(top_srcdir)/build-aux/snippet/unused-parameter.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	sed -n -e '/GL_UNUSED_PARAMETER/,$$p' \
	  < $(top_srcdir)/build-aux/snippet/unused-parameter.h \
	  > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += unused-parameter.h unused-parameter.h-t

UNUSED_PARAMETER_H = unused-parameter.h

fflush.c: $(UNUSED_PARAMETER_H)

BUILT_SOURCES += unistd.h

# We need the following in order to create an empty placeholder for
# <unistd.h> when the system doesn't have one.
unistd.h: unistd.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(ARG_NONNULL_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's|@''HAVE_UNISTD_H''@|$(HAVE_UNISTD_H)|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_UNISTD_H''@|$(NEXT_UNISTD_H)|g' \
	      -e 's|@''WINDOWS_64_BIT_OFF_T''@|$(WINDOWS_64_BIT_OFF_T)|g' \
	      -e 's/@''GNULIB_CHDIR''@/$(GNULIB_CHDIR)/g' \
	      -e 's/@''GNULIB_CHOWN''@/$(GNULIB_CHOWN)/g' \
	      -e 's/@''GNULIB_CLOSE''@/$(GNULIB_CLOSE)/g' \
	      -e 's/@''GNULIB_DUP''@/$(GNULIB_DUP)/g' \
	      -e 's/@''GNULIB_DUP2''@/$(GNULIB_DUP2)/g' \
	      -e 's/@''GNULIB_DUP3''@/$(GNULIB_DUP3)/g' \
	      -e 's/@''GNULIB_ENVIRON''@/$(GNULIB_ENVIRON)/g' \
	      -e 's/@''GNULIB_EUIDACCESS''@/$(GNULIB_EUIDACCESS)/g' \
	      -e 's/@''GNULIB_FACCESSAT''@/$(GNULIB_FACCESSAT)/g' \
	      -e 's/@''GNULIB_FCHDIR''@/$(GNULIB_FCHDIR)/g' \
	      -e 's/@''GNULIB_FCHOWNAT''@/$(GNULIB_FCHOWNAT)/g' \
	      -e 's/@''GNULIB_FDATASYNC''@/$(GNULIB_FDATASYNC)/g' \
	      -e 's/@''GNULIB_FSYNC''@/$(GNULIB_FSYNC)/g' \
	      -e 's/@''GNULIB_FTRUNCATE''@/$(GNULIB_FTRUNCATE)/g' \
	      -e 's/@''GNULIB_GETCWD''@/$(GNULIB_GETCWD)/g' \
	      -e 's/@''GNULIB_GETDOMAINNAME''@/$(GNULIB_GETDOMAINNAME)/g' \
	      -e 's/@''GNULIB_GETDTABLESIZE''@/$(GNULIB_GETDTABLESIZE)/g' \
	      -e 's/@''GNULIB_GETGROUPS''@/$(GNULIB_GETGROUPS)/g' \
	      -e 's/@''GNULIB_GETHOSTNAME''@/$(GNULIB_GETHOSTNAME)/g' \
	      -e 's/@''GNULIB_GETLOGIN''@/$(GNULIB_GETLOGIN)/g' \
	      -e 's/@''GNULIB_GETLOGIN_R''@/$(GNULIB_GETLOGIN_R)/g' \
	      -e 's/@''GNULIB_GETPAGESIZE''@/$(GNULIB_GETPAGESIZE)/g' \
	      -e 's/@''GNULIB_GETUSERSHELL''@/$(GNULIB_GETUSERSHELL)/g' \
	      -e 's/@''GNULIB_GROUP_MEMBER''@/$(GNULIB_GROUP_MEMBER)/g' \
	      -e 's/@''GNULIB_ISATTY''@/$(GNULIB_ISATTY)/g' \
	      -e 's/@''GNULIB_LCHOWN''@/$(GNULIB_LCHOWN)/g' \
	      -e 's/@''GNULIB_LINK''@/$(GNULIB_LINK)/g' \
	      -e 's/@''GNULIB_LINKAT''@/$(GNULIB_LINKAT)/g' \
	      -e 's/@''GNULIB_LSEEK''@/$(GNULIB_LSEEK)/g' \
	      -e 's/@''GNULIB_PIPE''@/$(GNULIB_PIPE)/g' \
	      -e 's/@''GNULIB_PIPE2''@/$(GNULIB_PIPE2)/g' \
	      -e 's/@''GNULIB_PREAD''@/$(GNULIB_PREAD)/g' \
	      -e 's/@''GNULIB_PWRITE''@/$(GNULIB_PWRITE)/g' \
	      -e 's/@''GNULIB_READ''@/$(GNULIB_READ)/g' \
	      -e 's/@''GNULIB_READLINK''@/$(GNULIB_READLINK)/g' \
	      -e 's/@''GNULIB_READLINKAT''@/$(GNULIB_READLINKAT)/g' \
	      -e 's/@''GNULIB_RMDIR''@/$(GNULIB_RMDIR)/g' \
	      -e 's/@''GNULIB_SETHOSTNAME''@/$(GNULIB_SETHOSTNAME)/g' \
	      -e 's/@''GNULIB_SLEEP''@/$(GNULIB_SLEEP)/g' \
	      -e 's/@''GNULIB_SYMLINK''@/$(GNULIB_SYMLINK)/g' \
	      -e 's/@''GNULIB_SYMLINKAT''@/$(GNULIB_SYMLINKAT)/g' \
	      -e 's/@''GNULIB_TTYNAME_R''@/$(GNULIB_TTYNAME_R)/g' \
	      -e 's/@''GNULIB_UNISTD_H_GETOPT''@/0$(GNULIB_${gl_include_guard_prefix}_UNISTD_H_GETOPT)/g' \
	      -e 's/@''GNULIB_UNISTD_H_NONBLOCKING''@/$(GNULIB_UNISTD_H_NONBLOCKING)/g' \
	      -e 's/@''GNULIB_UNISTD_H_SIGPIPE''@/$(GNULIB_UNISTD_H_SIGPIPE)/g' \
	      -e 's/@''GNULIB_UNLINK''@/$(GNULIB_UNLINK)/g' \
	      -e 's/@''GNULIB_UNLINKAT''@/$(GNULIB_UNLINKAT)/g' \
	      -e 's/@''GNULIB_USLEEP''@/$(GNULIB_USLEEP)/g' \
	      -e 's/@''GNULIB_WRITE''@/$(GNULIB_WRITE)/g' \
	      < $(srcdir)/unistd.in.h | \
	  sed -e 's|@''HAVE_CHOWN''@|$(HAVE_CHOWN)|g' \
	      -e 's|@''HAVE_DUP2''@|$(HAVE_DUP2)|g' \
	      -e 's|@''HAVE_DUP3''@|$(HAVE_DUP3)|g' \
	      -e 's|@''HAVE_EUIDACCESS''@|$(HAVE_EUIDACCESS)|g' \
	      -e 's|@''HAVE_FACCESSAT''@|$(HAVE_FACCESSAT)|g' \
	      -e 's|@''HAVE_FCHDIR''@|$(HAVE_FCHDIR)|g' \
	      -e 's|@''HAVE_FCHOWNAT''@|$(HAVE_FCHOWNAT)|g' \
	      -e 's|@''HAVE_FDATASYNC''@|$(HAVE_FDATASYNC)|g' \
	      -e 's|@''HAVE_FSYNC''@|$(HAVE_FSYNC)|g' \
	      -e 's|@''HAVE_FTRUNCATE''@|$(HAVE_FTRUNCATE)|g' \
	      -e 's|@''HAVE_GETDTABLESIZE''@|$(HAVE_GETDTABLESIZE)|g' \
	      -e 's|@''HAVE_GETGROUPS''@|$(HAVE_GETGROUPS)|g' \
	      -e 's|@''HAVE_GETHOSTNAME''@|$(HAVE_GETHOSTNAME)|g' \
	      -e 's|@''HAVE_GETLOGIN''@|$(HAVE_GETLOGIN)|g' \
	      -e 's|@''HAVE_GETPAGESIZE''@|$(HAVE_GETPAGESIZE)|g' \
	      -e 's|@''HAVE_GROUP_MEMBER''@|$(HAVE_GROUP_MEMBER)|g' \
	      -e 's|@''HAVE_LCHOWN''@|$(HAVE_LCHOWN)|g' \
	      -e 's|@''HAVE_LINK''@|$(HAVE_LINK)|g' \
	      -e 's|@''HAVE_LINKAT''@|$(HAVE_LINKAT)|g' \
	      -e 's|@''HAVE_PIPE''@|$(HAVE_PIPE)|g' \
	      -e 's|@''HAVE_PIPE2''@|$(HAVE_PIPE2)|g' \
	      -e 's|@''HAVE_PREAD''@|$(HAVE_PREAD)|g' \
	      -e 's|@''HAVE_PWRITE''@|$(HAVE_PWRITE)|g' \
	      -e 's|@''HAVE_READLINK''@|$(HAVE_READLINK)|g' \
	      -e 's|@''HAVE_READLINKAT''@|$(HAVE_READLINKAT)|g' \
	      -e 's|@''HAVE_SETHOSTNAME''@|$(HAVE_SETHOSTNAME)|g' \
	      -e 's|@''HAVE_SLEEP''@|$(HAVE_SLEEP)|g' \
	      -e 's|@''HAVE_SYMLINK''@|$(HAVE_SYMLINK)|g' \
	      -e 's|@''HAVE_SYMLINKAT''@|$(HAVE_SYMLINKAT)|g' \
	      -e 's|@''HAVE_UNLINKAT''@|$(HAVE_UNLINKAT)|g' \
	      -e 's|@''HAVE_USLEEP''@|$(HAVE_USLEEP)|g' \
	      -e 's|@''HAVE_DECL_ENVIRON''@|$(HAVE_DECL_ENVIRON)|g' \
	      -e 's|@''HAVE_DECL_FCHDIR''@|$(HAVE_DECL_FCHDIR)|g' \
	      -e 's|@''HAVE_DECL_FDATASYNC''@|$(HAVE_DECL_FDATASYNC)|g' \
	      -e 's|@''HAVE_DECL_GETDOMAINNAME''@|$(HAVE_DECL_GETDOMAINNAME)|g' \
	      -e 's|@''HAVE_DECL_GETLOGIN_R''@|$(HAVE_DECL_GETLOGIN_R)|g' \
	      -e 's|@''HAVE_DECL_GETPAGESIZE''@|$(HAVE_DECL_GETPAGESIZE)|g' \
	      -e 's|@''HAVE_DECL_GETUSERSHELL''@|$(HAVE_DECL_GETUSERSHELL)|g' \
	      -e 's|@''HAVE_DECL_SETHOSTNAME''@|$(HAVE_DECL_SETHOSTNAME)|g' \
	      -e 's|@''HAVE_DECL_TTYNAME_R''@|$(HAVE_DECL_TTYNAME_R)|g' \
	      -e 's|@''HAVE_OS_H''@|$(HAVE_OS_H)|g' \
	      -e 's|@''HAVE_SYS_PARAM_H''@|$(HAVE_SYS_PARAM_H)|g' \
	  | \
	  sed -e 's|@''REPLACE_CHOWN''@|$(REPLACE_CHOWN)|g' \
	      -e 's|@''REPLACE_CLOSE''@|$(REPLACE_CLOSE)|g' \
	      -e 's|@''REPLACE_DUP''@|$(REPLACE_DUP)|g' \
	      -e 's|@''REPLACE_DUP2''@|$(REPLACE_DUP2)|g' \
	      -e 's|@''REPLACE_FCHOWNAT''@|$(REPLACE_FCHOWNAT)|g' \
	      -e 's|@''REPLACE_FTRUNCATE''@|$(REPLACE_FTRUNCATE)|g' \
	      -e 's|@''REPLACE_GETCWD''@|$(REPLACE_GETCWD)|g' \
	      -e 's|@''REPLACE_GETDOMAINNAME''@|$(REPLACE_GETDOMAINNAME)|g' \
	      -e 's|@''REPLACE_GETLOGIN_R''@|$(REPLACE_GETLOGIN_R)|g' \
	      -e 's|@''REPLACE_GETGROUPS''@|$(REPLACE_GETGROUPS)|g' \
	      -e 's|@''REPLACE_GETPAGESIZE''@|$(REPLACE_GETPAGESIZE)|g' \
	      -e 's|@''REPLACE_ISATTY''@|$(REPLACE_ISATTY)|g' \
	      -e 's|@''REPLACE_LCHOWN''@|$(REPLACE_LCHOWN)|g' \
	      -e 's|@''REPLACE_LINK''@|$(REPLACE_LINK)|g' \
	      -e 's|@''REPLACE_LINKAT''@|$(REPLACE_LINKAT)|g' \
	      -e 's|@''REPLACE_LSEEK''@|$(REPLACE_LSEEK)|g' \
	      -e 's|@''REPLACE_PREAD''@|$(REPLACE_PREAD)|g' \
	      -e 's|@''REPLACE_PWRITE''@|$(REPLACE_PWRITE)|g' \
	      -e 's|@''REPLACE_READ''@|$(REPLACE_READ)|g' \
	      -e 's|@''REPLACE_READLINK''@|$(REPLACE_READLINK)|g' \
	      -e 's|@''REPLACE_RMDIR''@|$(REPLACE_RMDIR)|g' \
	      -e 's|@''REPLACE_SLEEP''@|$(REPLACE_SLEEP)|g' \
	      -e 's|@''REPLACE_SYMLINK''@|$(REPLACE_SYMLINK)|g' \
	      -e 's|@''REPLACE_TTYNAME_R''@|$(REPLACE_TTYNAME_R)|g' \
	      -e 's|@''REPLACE_UNLINK''@|$(REPLACE_UNLINK)|g' \
	      -e 's|@''REPLACE_UNLINKAT''@|$(REPLACE_UNLINKAT)|g' \
	      -e 's|@''REPLACE_USLEEP''@|$(REPLACE_USLEEP)|g' \
	      -e 's|@''REPLACE_WRITE''@|$(REPLACE_WRITE)|g' \
	      -e 's|@''UNISTD_H_HAVE_WINSOCK2_H''@|$(UNISTD_H_HAVE_WINSOCK2_H)|g' \
	      -e 's|@''UNISTD_H_HAVE_WINSOCK2_H_AND_USE_SOCKETS''@|$(UNISTD_H_HAVE_WINSOCK2_H_AND_USE_SOCKETS)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)'; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += unistd.h unistd.h-t

libUnixToOSX_la_SOURCES += i-ring.c

libUnixToOSX_la_SOURCES += creat-safer.c open-safer.c

libUnixToOSX_la_SOURCES += opendir-safer.c

libUnixToOSX_la_SOURCES += dup-safer.c fd-safer.c pipe-safer.c

libUnixToOSX_la_SOURCES += cloexec.c

libUnixToOSX_la_SOURCES += openat-safer.c

libUnixToOSX_la_SOURCES += openat-die.c

libUnixToOSX_la_SOURCES += cycle-check.c

libUnixToOSX_la_SOURCES += hash-triple.c

libUnixToOSX_la_SOURCES += hash-pjw.h hash-pjw.c

libUnixToOSX_la_SOURCES += hash.c

BUILT_SOURCES += inttypes.h

# We need the following in order to create <inttypes.h> when the system
# does NOT have one that works with the given compiler.
inttypes.h: inttypes.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(WARN_ON_USE_H) $(ARG_NONNULL_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's/@''HAVE_INTTYPES_H''@/$(HAVE_INTTYPES_H)/g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_INTTYPES_H''@|$(NEXT_INTTYPES_H)|g' \
	      -e 's/@''PRI_MACROS_BROKEN''@/$(PRI_MACROS_BROKEN)/g' \
	      -e 's/@''APPLE_UNIVERSAL_BUILD''@/$(APPLE_UNIVERSAL_BUILD)/g' \
	      -e 's/@''HAVE_LONG_LONG_INT''@/$(HAVE_LONG_LONG_INT)/g' \
	      -e 's/@''HAVE_UNSIGNED_LONG_LONG_INT''@/$(HAVE_UNSIGNED_LONG_LONG_INT)/g' \
	      -e 's/@''PRIPTR_PREFIX''@/$(PRIPTR_PREFIX)/g' \
	      -e 's/@''GNULIB_IMAXABS''@/$(GNULIB_IMAXABS)/g' \
	      -e 's/@''GNULIB_IMAXDIV''@/$(GNULIB_IMAXDIV)/g' \
	      -e 's/@''GNULIB_STRTOIMAX''@/$(GNULIB_STRTOIMAX)/g' \
	      -e 's/@''GNULIB_STRTOUMAX''@/$(GNULIB_STRTOUMAX)/g' \
	      -e 's/@''HAVE_DECL_IMAXABS''@/$(HAVE_DECL_IMAXABS)/g' \
	      -e 's/@''HAVE_DECL_IMAXDIV''@/$(HAVE_DECL_IMAXDIV)/g' \
	      -e 's/@''HAVE_DECL_STRTOIMAX''@/$(HAVE_DECL_STRTOIMAX)/g' \
	      -e 's/@''HAVE_DECL_STRTOUMAX''@/$(HAVE_DECL_STRTOUMAX)/g' \
	      -e 's/@''REPLACE_STRTOIMAX''@/$(REPLACE_STRTOIMAX)/g' \
	      -e 's/@''INT32_MAX_LT_INTMAX_MAX''@/$(INT32_MAX_LT_INTMAX_MAX)/g' \
	      -e 's/@''INT64_MAX_EQ_LONG_MAX''@/$(INT64_MAX_EQ_LONG_MAX)/g' \
	      -e 's/@''UINT32_MAX_LT_UINTMAX_MAX''@/$(UINT32_MAX_LT_UINTMAX_MAX)/g' \
	      -e 's/@''UINT64_MAX_EQ_ULONG_MAX''@/$(UINT64_MAX_EQ_ULONG_MAX)/g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)' \
	      < $(srcdir)/inttypes.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += inttypes.h inttypes.h-t

BUILT_SOURCES += math.h

# We need the following in order to create <math.h> when the system
# doesn't have one that works with the given compiler.
math.h: math.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(ARG_NONNULL_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */' && \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's|@''INCLUDE_NEXT_AS_FIRST_DIRECTIVE''@|$(INCLUDE_NEXT_AS_FIRST_DIRECTIVE)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_AS_FIRST_DIRECTIVE_MATH_H''@|$(NEXT_AS_FIRST_DIRECTIVE_MATH_H)|g' \
	      -e 's/@''GNULIB_ACOSF''@/$(GNULIB_ACOSF)/g' \
	      -e 's/@''GNULIB_ACOSL''@/$(GNULIB_ACOSL)/g' \
	      -e 's/@''GNULIB_ASINF''@/$(GNULIB_ASINF)/g' \
	      -e 's/@''GNULIB_ASINL''@/$(GNULIB_ASINL)/g' \
	      -e 's/@''GNULIB_ATANF''@/$(GNULIB_ATANF)/g' \
	      -e 's/@''GNULIB_ATANL''@/$(GNULIB_ATANL)/g' \
	      -e 's/@''GNULIB_ATAN2F''@/$(GNULIB_ATAN2F)/g' \
	      -e 's/@''GNULIB_CBRT''@/$(GNULIB_CBRT)/g' \
	      -e 's/@''GNULIB_CBRTF''@/$(GNULIB_CBRTF)/g' \
	      -e 's/@''GNULIB_CBRTL''@/$(GNULIB_CBRTL)/g' \
	      -e 's/@''GNULIB_CEIL''@/$(GNULIB_CEIL)/g' \
	      -e 's/@''GNULIB_CEILF''@/$(GNULIB_CEILF)/g' \
	      -e 's/@''GNULIB_CEILL''@/$(GNULIB_CEILL)/g' \
	      -e 's/@''GNULIB_COPYSIGN''@/$(GNULIB_COPYSIGN)/g' \
	      -e 's/@''GNULIB_COPYSIGNF''@/$(GNULIB_COPYSIGNF)/g' \
	      -e 's/@''GNULIB_COPYSIGNL''@/$(GNULIB_COPYSIGNL)/g' \
	      -e 's/@''GNULIB_COSF''@/$(GNULIB_COSF)/g' \
	      -e 's/@''GNULIB_COSL''@/$(GNULIB_COSL)/g' \
	      -e 's/@''GNULIB_COSHF''@/$(GNULIB_COSHF)/g' \
	      -e 's/@''GNULIB_EXPF''@/$(GNULIB_EXPF)/g' \
	      -e 's/@''GNULIB_EXPL''@/$(GNULIB_EXPL)/g' \
	      -e 's/@''GNULIB_EXP2''@/$(GNULIB_EXP2)/g' \
	      -e 's/@''GNULIB_EXP2F''@/$(GNULIB_EXP2F)/g' \
	      -e 's/@''GNULIB_EXP2L''@/$(GNULIB_EXP2L)/g' \
	      -e 's/@''GNULIB_EXPM1''@/$(GNULIB_EXPM1)/g' \
	      -e 's/@''GNULIB_EXPM1F''@/$(GNULIB_EXPM1F)/g' \
	      -e 's/@''GNULIB_EXPM1L''@/$(GNULIB_EXPM1L)/g' \
	      -e 's/@''GNULIB_FABSF''@/$(GNULIB_FABSF)/g' \
	      -e 's/@''GNULIB_FABSL''@/$(GNULIB_FABSL)/g' \
	      -e 's/@''GNULIB_FLOOR''@/$(GNULIB_FLOOR)/g' \
	      -e 's/@''GNULIB_FLOORF''@/$(GNULIB_FLOORF)/g' \
	      -e 's/@''GNULIB_FLOORL''@/$(GNULIB_FLOORL)/g' \
	      -e 's/@''GNULIB_FMA''@/$(GNULIB_FMA)/g' \
	      -e 's/@''GNULIB_FMAF''@/$(GNULIB_FMAF)/g' \
	      -e 's/@''GNULIB_FMAL''@/$(GNULIB_FMAL)/g' \
	      -e 's/@''GNULIB_FMOD''@/$(GNULIB_FMOD)/g' \
	      -e 's/@''GNULIB_FMODF''@/$(GNULIB_FMODF)/g' \
	      -e 's/@''GNULIB_FMODL''@/$(GNULIB_FMODL)/g' \
	      -e 's/@''GNULIB_FREXPF''@/$(GNULIB_FREXPF)/g' \
	      -e 's/@''GNULIB_FREXP''@/$(GNULIB_FREXP)/g' \
	      -e 's/@''GNULIB_FREXPL''@/$(GNULIB_FREXPL)/g' \
	      -e 's/@''GNULIB_HYPOT''@/$(GNULIB_HYPOT)/g' \
	      -e 's/@''GNULIB_HYPOTF''@/$(GNULIB_HYPOTF)/g' \
	      -e 's/@''GNULIB_HYPOTL''@/$(GNULIB_HYPOTL)/g' \
	      < $(srcdir)/math.in.h | \
	  sed -e 's/@''GNULIB_ILOGB''@/$(GNULIB_ILOGB)/g' \
	      -e 's/@''GNULIB_ILOGBF''@/$(GNULIB_ILOGBF)/g' \
	      -e 's/@''GNULIB_ILOGBL''@/$(GNULIB_ILOGBL)/g' \
	      -e 's/@''GNULIB_ISFINITE''@/$(GNULIB_ISFINITE)/g' \
	      -e 's/@''GNULIB_ISINF''@/$(GNULIB_ISINF)/g' \
	      -e 's/@''GNULIB_ISNAN''@/$(GNULIB_ISNAN)/g' \
	      -e 's/@''GNULIB_ISNANF''@/$(GNULIB_ISNANF)/g' \
	      -e 's/@''GNULIB_ISNAND''@/$(GNULIB_ISNAND)/g' \
	      -e 's/@''GNULIB_ISNANL''@/$(GNULIB_ISNANL)/g' \
	      -e 's/@''GNULIB_LDEXPF''@/$(GNULIB_LDEXPF)/g' \
	      -e 's/@''GNULIB_LDEXPL''@/$(GNULIB_LDEXPL)/g' \
	      -e 's/@''GNULIB_LOG''@/$(GNULIB_LOG)/g' \
	      -e 's/@''GNULIB_LOGF''@/$(GNULIB_LOGF)/g' \
	      -e 's/@''GNULIB_LOGL''@/$(GNULIB_LOGL)/g' \
	      -e 's/@''GNULIB_LOG10''@/$(GNULIB_LOG10)/g' \
	      -e 's/@''GNULIB_LOG10F''@/$(GNULIB_LOG10F)/g' \
	      -e 's/@''GNULIB_LOG10L''@/$(GNULIB_LOG10L)/g' \
	      -e 's/@''GNULIB_LOG1P''@/$(GNULIB_LOG1P)/g' \
	      -e 's/@''GNULIB_LOG1PF''@/$(GNULIB_LOG1PF)/g' \
	      -e 's/@''GNULIB_LOG1PL''@/$(GNULIB_LOG1PL)/g' \
	      -e 's/@''GNULIB_LOG2''@/$(GNULIB_LOG2)/g' \
	      -e 's/@''GNULIB_LOG2F''@/$(GNULIB_LOG2F)/g' \
	      -e 's/@''GNULIB_LOG2L''@/$(GNULIB_LOG2L)/g' \
	      -e 's/@''GNULIB_LOGB''@/$(GNULIB_LOGB)/g' \
	      -e 's/@''GNULIB_LOGBF''@/$(GNULIB_LOGBF)/g' \
	      -e 's/@''GNULIB_LOGBL''@/$(GNULIB_LOGBL)/g' \
	      -e 's/@''GNULIB_MODF''@/$(GNULIB_MODF)/g' \
	      -e 's/@''GNULIB_MODFF''@/$(GNULIB_MODFF)/g' \
	      -e 's/@''GNULIB_MODFL''@/$(GNULIB_MODFL)/g' \
	      -e 's/@''GNULIB_POWF''@/$(GNULIB_POWF)/g' \
	      -e 's/@''GNULIB_REMAINDER''@/$(GNULIB_REMAINDER)/g' \
	      -e 's/@''GNULIB_REMAINDERF''@/$(GNULIB_REMAINDERF)/g' \
	      -e 's/@''GNULIB_REMAINDERL''@/$(GNULIB_REMAINDERL)/g' \
	      -e 's/@''GNULIB_RINT''@/$(GNULIB_RINT)/g' \
	      -e 's/@''GNULIB_RINTF''@/$(GNULIB_RINTF)/g' \
	      -e 's/@''GNULIB_RINTL''@/$(GNULIB_RINTL)/g' \
	      -e 's/@''GNULIB_ROUND''@/$(GNULIB_ROUND)/g' \
	      -e 's/@''GNULIB_ROUNDF''@/$(GNULIB_ROUNDF)/g' \
	      -e 's/@''GNULIB_ROUNDL''@/$(GNULIB_ROUNDL)/g' \
	      -e 's/@''GNULIB_SIGNBIT''@/$(GNULIB_SIGNBIT)/g' \
	      -e 's/@''GNULIB_SINF''@/$(GNULIB_SINF)/g' \
	      -e 's/@''GNULIB_SINL''@/$(GNULIB_SINL)/g' \
	      -e 's/@''GNULIB_SINHF''@/$(GNULIB_SINHF)/g' \
	      -e 's/@''GNULIB_SQRTF''@/$(GNULIB_SQRTF)/g' \
	      -e 's/@''GNULIB_SQRTL''@/$(GNULIB_SQRTL)/g' \
	      -e 's/@''GNULIB_TANF''@/$(GNULIB_TANF)/g' \
	      -e 's/@''GNULIB_TANL''@/$(GNULIB_TANL)/g' \
	      -e 's/@''GNULIB_TANHF''@/$(GNULIB_TANHF)/g' \
	      -e 's/@''GNULIB_TRUNC''@/$(GNULIB_TRUNC)/g' \
	      -e 's/@''GNULIB_TRUNCF''@/$(GNULIB_TRUNCF)/g' \
	      -e 's/@''GNULIB_TRUNCL''@/$(GNULIB_TRUNCL)/g' \
	  | \
	  sed -e 's|@''HAVE_ACOSF''@|$(HAVE_ACOSF)|g' \
	      -e 's|@''HAVE_ACOSL''@|$(HAVE_ACOSL)|g' \
	      -e 's|@''HAVE_ASINF''@|$(HAVE_ASINF)|g' \
	      -e 's|@''HAVE_ASINL''@|$(HAVE_ASINL)|g' \
	      -e 's|@''HAVE_ATANF''@|$(HAVE_ATANF)|g' \
	      -e 's|@''HAVE_ATANL''@|$(HAVE_ATANL)|g' \
	      -e 's|@''HAVE_ATAN2F''@|$(HAVE_ATAN2F)|g' \
	      -e 's|@''HAVE_CBRT''@|$(HAVE_CBRT)|g' \
	      -e 's|@''HAVE_CBRTF''@|$(HAVE_CBRTF)|g' \
	      -e 's|@''HAVE_CBRTL''@|$(HAVE_CBRTL)|g' \
	      -e 's|@''HAVE_COPYSIGN''@|$(HAVE_COPYSIGN)|g' \
	      -e 's|@''HAVE_COPYSIGNL''@|$(HAVE_COPYSIGNL)|g' \
	      -e 's|@''HAVE_COSF''@|$(HAVE_COSF)|g' \
	      -e 's|@''HAVE_COSL''@|$(HAVE_COSL)|g' \
	      -e 's|@''HAVE_COSHF''@|$(HAVE_COSHF)|g' \
	      -e 's|@''HAVE_EXPF''@|$(HAVE_EXPF)|g' \
	      -e 's|@''HAVE_EXPL''@|$(HAVE_EXPL)|g' \
	      -e 's|@''HAVE_EXPM1''@|$(HAVE_EXPM1)|g' \
	      -e 's|@''HAVE_EXPM1F''@|$(HAVE_EXPM1F)|g' \
	      -e 's|@''HAVE_FABSF''@|$(HAVE_FABSF)|g' \
	      -e 's|@''HAVE_FABSL''@|$(HAVE_FABSL)|g' \
	      -e 's|@''HAVE_FMA''@|$(HAVE_FMA)|g' \
	      -e 's|@''HAVE_FMAF''@|$(HAVE_FMAF)|g' \
	      -e 's|@''HAVE_FMAL''@|$(HAVE_FMAL)|g' \
	      -e 's|@''HAVE_FMODF''@|$(HAVE_FMODF)|g' \
	      -e 's|@''HAVE_FMODL''@|$(HAVE_FMODL)|g' \
	      -e 's|@''HAVE_FREXPF''@|$(HAVE_FREXPF)|g' \
	      -e 's|@''HAVE_HYPOTF''@|$(HAVE_HYPOTF)|g' \
	      -e 's|@''HAVE_HYPOTL''@|$(HAVE_HYPOTL)|g' \
	      -e 's|@''HAVE_ILOGB''@|$(HAVE_ILOGB)|g' \
	      -e 's|@''HAVE_ILOGBF''@|$(HAVE_ILOGBF)|g' \
	      -e 's|@''HAVE_ILOGBL''@|$(HAVE_ILOGBL)|g' \
	      -e 's|@''HAVE_ISNANF''@|$(HAVE_ISNANF)|g' \
	      -e 's|@''HAVE_ISNAND''@|$(HAVE_ISNAND)|g' \
	      -e 's|@''HAVE_ISNANL''@|$(HAVE_ISNANL)|g' \
	      -e 's|@''HAVE_LDEXPF''@|$(HAVE_LDEXPF)|g' \
	      -e 's|@''HAVE_LOGF''@|$(HAVE_LOGF)|g' \
	      -e 's|@''HAVE_LOGL''@|$(HAVE_LOGL)|g' \
	      -e 's|@''HAVE_LOG10F''@|$(HAVE_LOG10F)|g' \
	      -e 's|@''HAVE_LOG10L''@|$(HAVE_LOG10L)|g' \
	      -e 's|@''HAVE_LOG1P''@|$(HAVE_LOG1P)|g' \
	      -e 's|@''HAVE_LOG1PF''@|$(HAVE_LOG1PF)|g' \
	      -e 's|@''HAVE_LOG1PL''@|$(HAVE_LOG1PL)|g' \
	      -e 's|@''HAVE_LOGBF''@|$(HAVE_LOGBF)|g' \
	      -e 's|@''HAVE_LOGBL''@|$(HAVE_LOGBL)|g' \
	      -e 's|@''HAVE_MODFF''@|$(HAVE_MODFF)|g' \
	      -e 's|@''HAVE_MODFL''@|$(HAVE_MODFL)|g' \
	      -e 's|@''HAVE_POWF''@|$(HAVE_POWF)|g' \
	      -e 's|@''HAVE_REMAINDER''@|$(HAVE_REMAINDER)|g' \
	      -e 's|@''HAVE_REMAINDERF''@|$(HAVE_REMAINDERF)|g' \
	      -e 's|@''HAVE_RINT''@|$(HAVE_RINT)|g' \
	      -e 's|@''HAVE_RINTL''@|$(HAVE_RINTL)|g' \
	      -e 's|@''HAVE_SINF''@|$(HAVE_SINF)|g' \
	      -e 's|@''HAVE_SINL''@|$(HAVE_SINL)|g' \
	      -e 's|@''HAVE_SINHF''@|$(HAVE_SINHF)|g' \
	      -e 's|@''HAVE_SQRTF''@|$(HAVE_SQRTF)|g' \
	      -e 's|@''HAVE_SQRTL''@|$(HAVE_SQRTL)|g' \
	      -e 's|@''HAVE_TANF''@|$(HAVE_TANF)|g' \
	      -e 's|@''HAVE_TANL''@|$(HAVE_TANL)|g' \
	      -e 's|@''HAVE_TANHF''@|$(HAVE_TANHF)|g' \
	      -e 's|@''HAVE_DECL_ACOSL''@|$(HAVE_DECL_ACOSL)|g' \
	      -e 's|@''HAVE_DECL_ASINL''@|$(HAVE_DECL_ASINL)|g' \
	      -e 's|@''HAVE_DECL_ATANL''@|$(HAVE_DECL_ATANL)|g' \
	      -e 's|@''HAVE_DECL_CBRTF''@|$(HAVE_DECL_CBRTF)|g' \
	      -e 's|@''HAVE_DECL_CBRTL''@|$(HAVE_DECL_CBRTL)|g' \
	      -e 's|@''HAVE_DECL_CEILF''@|$(HAVE_DECL_CEILF)|g' \
	      -e 's|@''HAVE_DECL_CEILL''@|$(HAVE_DECL_CEILL)|g' \
	      -e 's|@''HAVE_DECL_COPYSIGNF''@|$(HAVE_DECL_COPYSIGNF)|g' \
	      -e 's|@''HAVE_DECL_COSL''@|$(HAVE_DECL_COSL)|g' \
	      -e 's|@''HAVE_DECL_EXPL''@|$(HAVE_DECL_EXPL)|g' \
	      -e 's|@''HAVE_DECL_EXP2''@|$(HAVE_DECL_EXP2)|g' \
	      -e 's|@''HAVE_DECL_EXP2F''@|$(HAVE_DECL_EXP2F)|g' \
	      -e 's|@''HAVE_DECL_EXP2L''@|$(HAVE_DECL_EXP2L)|g' \
	      -e 's|@''HAVE_DECL_EXPM1L''@|$(HAVE_DECL_EXPM1L)|g' \
	      -e 's|@''HAVE_DECL_FLOORF''@|$(HAVE_DECL_FLOORF)|g' \
	      -e 's|@''HAVE_DECL_FLOORL''@|$(HAVE_DECL_FLOORL)|g' \
	      -e 's|@''HAVE_DECL_FREXPL''@|$(HAVE_DECL_FREXPL)|g' \
	      -e 's|@''HAVE_DECL_LDEXPL''@|$(HAVE_DECL_LDEXPL)|g' \
	      -e 's|@''HAVE_DECL_LOGL''@|$(HAVE_DECL_LOGL)|g' \
	      -e 's|@''HAVE_DECL_LOG10L''@|$(HAVE_DECL_LOG10L)|g' \
	      -e 's|@''HAVE_DECL_LOG2''@|$(HAVE_DECL_LOG2)|g' \
	      -e 's|@''HAVE_DECL_LOG2F''@|$(HAVE_DECL_LOG2F)|g' \
	      -e 's|@''HAVE_DECL_LOG2L''@|$(HAVE_DECL_LOG2L)|g' \
	      -e 's|@''HAVE_DECL_LOGB''@|$(HAVE_DECL_LOGB)|g' \
	      -e 's|@''HAVE_DECL_REMAINDER''@|$(HAVE_DECL_REMAINDER)|g' \
	      -e 's|@''HAVE_DECL_REMAINDERL''@|$(HAVE_DECL_REMAINDERL)|g' \
	      -e 's|@''HAVE_DECL_RINTF''@|$(HAVE_DECL_RINTF)|g' \
	      -e 's|@''HAVE_DECL_ROUND''@|$(HAVE_DECL_ROUND)|g' \
	      -e 's|@''HAVE_DECL_ROUNDF''@|$(HAVE_DECL_ROUNDF)|g' \
	      -e 's|@''HAVE_DECL_ROUNDL''@|$(HAVE_DECL_ROUNDL)|g' \
	      -e 's|@''HAVE_DECL_SINL''@|$(HAVE_DECL_SINL)|g' \
	      -e 's|@''HAVE_DECL_SQRTL''@|$(HAVE_DECL_SQRTL)|g' \
	      -e 's|@''HAVE_DECL_TANL''@|$(HAVE_DECL_TANL)|g' \
	      -e 's|@''HAVE_DECL_TRUNC''@|$(HAVE_DECL_TRUNC)|g' \
	      -e 's|@''HAVE_DECL_TRUNCF''@|$(HAVE_DECL_TRUNCF)|g' \
	      -e 's|@''HAVE_DECL_TRUNCL''@|$(HAVE_DECL_TRUNCL)|g' \
	  | \
	  sed -e 's|@''REPLACE_CBRTF''@|$(REPLACE_CBRTF)|g' \
	      -e 's|@''REPLACE_CBRTL''@|$(REPLACE_CBRTL)|g' \
	      -e 's|@''REPLACE_CEIL''@|$(REPLACE_CEIL)|g' \
	      -e 's|@''REPLACE_CEILF''@|$(REPLACE_CEILF)|g' \
	      -e 's|@''REPLACE_CEILL''@|$(REPLACE_CEILL)|g' \
	      -e 's|@''REPLACE_EXPM1''@|$(REPLACE_EXPM1)|g' \
	      -e 's|@''REPLACE_EXPM1F''@|$(REPLACE_EXPM1F)|g' \
	      -e 's|@''REPLACE_EXP2''@|$(REPLACE_EXP2)|g' \
	      -e 's|@''REPLACE_EXP2L''@|$(REPLACE_EXP2L)|g' \
	      -e 's|@''REPLACE_FABSL''@|$(REPLACE_FABSL)|g' \
	      -e 's|@''REPLACE_FLOOR''@|$(REPLACE_FLOOR)|g' \
	      -e 's|@''REPLACE_FLOORF''@|$(REPLACE_FLOORF)|g' \
	      -e 's|@''REPLACE_FLOORL''@|$(REPLACE_FLOORL)|g' \
	      -e 's|@''REPLACE_FMA''@|$(REPLACE_FMA)|g' \
	      -e 's|@''REPLACE_FMAF''@|$(REPLACE_FMAF)|g' \
	      -e 's|@''REPLACE_FMAL''@|$(REPLACE_FMAL)|g' \
	      -e 's|@''REPLACE_FMOD''@|$(REPLACE_FMOD)|g' \
	      -e 's|@''REPLACE_FMODF''@|$(REPLACE_FMODF)|g' \
	      -e 's|@''REPLACE_FMODL''@|$(REPLACE_FMODL)|g' \
	      -e 's|@''REPLACE_FREXPF''@|$(REPLACE_FREXPF)|g' \
	      -e 's|@''REPLACE_FREXP''@|$(REPLACE_FREXP)|g' \
	      -e 's|@''REPLACE_FREXPL''@|$(REPLACE_FREXPL)|g' \
	      -e 's|@''REPLACE_HUGE_VAL''@|$(REPLACE_HUGE_VAL)|g' \
	      -e 's|@''REPLACE_HYPOT''@|$(REPLACE_HYPOT)|g' \
	      -e 's|@''REPLACE_HYPOTF''@|$(REPLACE_HYPOTF)|g' \
	      -e 's|@''REPLACE_HYPOTL''@|$(REPLACE_HYPOTL)|g' \
	      -e 's|@''REPLACE_ILOGB''@|$(REPLACE_ILOGB)|g' \
	      -e 's|@''REPLACE_ILOGBF''@|$(REPLACE_ILOGBF)|g' \
	      -e 's|@''REPLACE_ISFINITE''@|$(REPLACE_ISFINITE)|g' \
	      -e 's|@''REPLACE_ISINF''@|$(REPLACE_ISINF)|g' \
	      -e 's|@''REPLACE_ISNAN''@|$(REPLACE_ISNAN)|g' \
	      -e 's|@''REPLACE_ITOLD''@|$(REPLACE_ITOLD)|g' \
	      -e 's|@''REPLACE_LDEXPL''@|$(REPLACE_LDEXPL)|g' \
	      -e 's|@''REPLACE_LOG''@|$(REPLACE_LOG)|g' \
	      -e 's|@''REPLACE_LOGF''@|$(REPLACE_LOGF)|g' \
	      -e 's|@''REPLACE_LOGL''@|$(REPLACE_LOGL)|g' \
	      -e 's|@''REPLACE_LOG10''@|$(REPLACE_LOG10)|g' \
	      -e 's|@''REPLACE_LOG10F''@|$(REPLACE_LOG10F)|g' \
	      -e 's|@''REPLACE_LOG10L''@|$(REPLACE_LOG10L)|g' \
	      -e 's|@''REPLACE_LOG1P''@|$(REPLACE_LOG1P)|g' \
	      -e 's|@''REPLACE_LOG1PF''@|$(REPLACE_LOG1PF)|g' \
	      -e 's|@''REPLACE_LOG1PL''@|$(REPLACE_LOG1PL)|g' \
	      -e 's|@''REPLACE_LOG2''@|$(REPLACE_LOG2)|g' \
	      -e 's|@''REPLACE_LOG2F''@|$(REPLACE_LOG2F)|g' \
	      -e 's|@''REPLACE_LOG2L''@|$(REPLACE_LOG2L)|g' \
	      -e 's|@''REPLACE_LOGB''@|$(REPLACE_LOGB)|g' \
	      -e 's|@''REPLACE_LOGBF''@|$(REPLACE_LOGBF)|g' \
	      -e 's|@''REPLACE_LOGBL''@|$(REPLACE_LOGBL)|g' \
	      -e 's|@''REPLACE_MODF''@|$(REPLACE_MODF)|g' \
	      -e 's|@''REPLACE_MODFF''@|$(REPLACE_MODFF)|g' \
	      -e 's|@''REPLACE_MODFL''@|$(REPLACE_MODFL)|g' \
	      -e 's|@''REPLACE_NAN''@|$(REPLACE_NAN)|g' \
	      -e 's|@''REPLACE_REMAINDER''@|$(REPLACE_REMAINDER)|g' \
	      -e 's|@''REPLACE_REMAINDERF''@|$(REPLACE_REMAINDERF)|g' \
	      -e 's|@''REPLACE_REMAINDERL''@|$(REPLACE_REMAINDERL)|g' \
	      -e 's|@''REPLACE_ROUND''@|$(REPLACE_ROUND)|g' \
	      -e 's|@''REPLACE_ROUNDF''@|$(REPLACE_ROUNDF)|g' \
	      -e 's|@''REPLACE_ROUNDL''@|$(REPLACE_ROUNDL)|g' \
	      -e 's|@''REPLACE_SIGNBIT''@|$(REPLACE_SIGNBIT)|g' \
	      -e 's|@''REPLACE_SIGNBIT_USING_GCC''@|$(REPLACE_SIGNBIT_USING_GCC)|g' \
	      -e 's|@''REPLACE_SQRTL''@|$(REPLACE_SQRTL)|g' \
	      -e 's|@''REPLACE_TRUNC''@|$(REPLACE_TRUNC)|g' \
	      -e 's|@''REPLACE_TRUNCF''@|$(REPLACE_TRUNCF)|g' \
	      -e 's|@''REPLACE_TRUNCL''@|$(REPLACE_TRUNCL)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)'; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += math.h math.h-t

BUILT_SOURCES += $(STDINT_H)

# We need the following in order to create <stdint.h> when the system
# does NOT have one that works with the given compiler.
if GL_GENERATE_STDINT_H
stdint.h: stdint.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's/@''HAVE_STDINT_H''@/$(HAVE_STDINT_H)/g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_STDINT_H''@|$(NEXT_STDINT_H)|g' \
	      -e 's/@''HAVE_SYS_TYPES_H''@/$(HAVE_SYS_TYPES_H)/g' \
	      -e 's/@''HAVE_INTTYPES_H''@/$(HAVE_INTTYPES_H)/g' \
	      -e 's/@''HAVE_SYS_INTTYPES_H''@/$(HAVE_SYS_INTTYPES_H)/g' \
	      -e 's/@''HAVE_SYS_BITYPES_H''@/$(HAVE_SYS_BITYPES_H)/g' \
	      -e 's/@''HAVE_WCHAR_H''@/$(HAVE_WCHAR_H)/g' \
	      -e 's/@''HAVE_LONG_LONG_INT''@/$(HAVE_LONG_LONG_INT)/g' \
	      -e 's/@''HAVE_UNSIGNED_LONG_LONG_INT''@/$(HAVE_UNSIGNED_LONG_LONG_INT)/g' \
	      -e 's/@''APPLE_UNIVERSAL_BUILD''@/$(APPLE_UNIVERSAL_BUILD)/g' \
	      -e 's/@''BITSIZEOF_PTRDIFF_T''@/$(BITSIZEOF_PTRDIFF_T)/g' \
	      -e 's/@''PTRDIFF_T_SUFFIX''@/$(PTRDIFF_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_SIG_ATOMIC_T''@/$(BITSIZEOF_SIG_ATOMIC_T)/g' \
	      -e 's/@''HAVE_SIGNED_SIG_ATOMIC_T''@/$(HAVE_SIGNED_SIG_ATOMIC_T)/g' \
	      -e 's/@''SIG_ATOMIC_T_SUFFIX''@/$(SIG_ATOMIC_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_SIZE_T''@/$(BITSIZEOF_SIZE_T)/g' \
	      -e 's/@''SIZE_T_SUFFIX''@/$(SIZE_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_WCHAR_T''@/$(BITSIZEOF_WCHAR_T)/g' \
	      -e 's/@''HAVE_SIGNED_WCHAR_T''@/$(HAVE_SIGNED_WCHAR_T)/g' \
	      -e 's/@''WCHAR_T_SUFFIX''@/$(WCHAR_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_WINT_T''@/$(BITSIZEOF_WINT_T)/g' \
	      -e 's/@''HAVE_SIGNED_WINT_T''@/$(HAVE_SIGNED_WINT_T)/g' \
	      -e 's/@''WINT_T_SUFFIX''@/$(WINT_T_SUFFIX)/g' \
	      < $(srcdir)/stdint.in.h; \
	} > $@-t && \
	mv $@-t $@
else
stdint.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += stdint.h stdint.h-t

libUnixToOSX_la_SOURCES += exitfail.c

libUnixToOSX_la_SOURCES += same.c

libUnixToOSX_la_SOURCES += bitrotate.h

libUnixToOSX_la_SOURCES += dirname.c basename.c

libUnixToOSX_la_SOURCES += dirname-lgpl.c basename-lgpl.c stripslash.c

libUnixToOSX_la_SOURCES += xalloc-die.c

libUnixToOSX_la_SOURCES += xmalloc.c

libUnixToOSX_la_SOURCES += xstrndup.h xstrndup.c

libUnixToOSX_la_SOURCES += xsize.h

libUnixToOSX_la_SOURCES += printf-frexp.c

libUnixToOSX_la_SOURCES += printf-frexpl.c

BUILT_SOURCES += $(FLOAT_H)

# We need the following in order to create <float.h> when the system
# does NOT have one that works with the given compiler.
if GL_GENERATE_FLOAT_H
float.h: float.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */' && \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_FLOAT_H''@|$(NEXT_FLOAT_H)|g' \
	      -e 's|@''REPLACE_ITOLD''@|$(REPLACE_ITOLD)|g' \
	      < $(srcdir)/float.in.h; \
	} > $@-t && \
	mv $@-t $@
else
float.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += float.h float.h-t

libUnixToOSX_la_SOURCES += save-cwd.c

libUnixToOSX_la_SOURCES += chdir-safer.c

DISTCLEANFILES = .DS_Store *~ autoscan.log

distclean-local:
	rm -rf autom4te.cache || rmdir autom4te.cache
	test -d sys && test -z "`ls sys`" && rmdir sys
	test -d scan_build_output && test -z "`ls scan_build_output`" && rmdir scan_build_output

libUnixToOSX_la_SOURCES += fd-hook.c

libUnixToOSX_la_SOURCES += filenamecat-lgpl.c

libUnixToOSX_la_SOURCES += filenamecat.c

libUnixToOSX_la_SOURCES += dup3.c

libUnixToOSX_la_SOURCES += binary-io.h

BUILT_SOURCES += sys/stat.h

# We need the following in order to create <sys/stat.h> when the system
# has one that is incomplete.
sys/stat.h: sys_stat.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(ARG_NONNULL_H) $(WARN_ON_USE_H)
	$(AM_V_at)$(MKDIR_P) sys
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_SYS_STAT_H''@|$(NEXT_SYS_STAT_H)|g' \
	      -e 's|@''WINDOWS_64_BIT_ST_SIZE''@|$(WINDOWS_64_BIT_ST_SIZE)|g' \
	      -e 's/@''GNULIB_FCHMODAT''@/$(GNULIB_FCHMODAT)/g' \
	      -e 's/@''GNULIB_FSTAT''@/$(GNULIB_FSTAT)/g' \
	      -e 's/@''GNULIB_FSTATAT''@/$(GNULIB_FSTATAT)/g' \
	      -e 's/@''GNULIB_FUTIMENS''@/$(GNULIB_FUTIMENS)/g' \
	      -e 's/@''GNULIB_LCHMOD''@/$(GNULIB_LCHMOD)/g' \
	      -e 's/@''GNULIB_LSTAT''@/$(GNULIB_LSTAT)/g' \
	      -e 's/@''GNULIB_MKDIRAT''@/$(GNULIB_MKDIRAT)/g' \
	      -e 's/@''GNULIB_MKFIFO''@/$(GNULIB_MKFIFO)/g' \
	      -e 's/@''GNULIB_MKFIFOAT''@/$(GNULIB_MKFIFOAT)/g' \
	      -e 's/@''GNULIB_MKNOD''@/$(GNULIB_MKNOD)/g' \
	      -e 's/@''GNULIB_MKNODAT''@/$(GNULIB_MKNODAT)/g' \
	      -e 's/@''GNULIB_STAT''@/$(GNULIB_STAT)/g' \
	      -e 's/@''GNULIB_UTIMENSAT''@/$(GNULIB_UTIMENSAT)/g' \
	      -e 's|@''HAVE_FCHMODAT''@|$(HAVE_FCHMODAT)|g' \
	      -e 's|@''HAVE_FSTATAT''@|$(HAVE_FSTATAT)|g' \
	      -e 's|@''HAVE_FUTIMENS''@|$(HAVE_FUTIMENS)|g' \
	      -e 's|@''HAVE_LCHMOD''@|$(HAVE_LCHMOD)|g' \
	      -e 's|@''HAVE_LSTAT''@|$(HAVE_LSTAT)|g' \
	      -e 's|@''HAVE_MKDIRAT''@|$(HAVE_MKDIRAT)|g' \
	      -e 's|@''HAVE_MKFIFO''@|$(HAVE_MKFIFO)|g' \
	      -e 's|@''HAVE_MKFIFOAT''@|$(HAVE_MKFIFOAT)|g' \
	      -e 's|@''HAVE_MKNOD''@|$(HAVE_MKNOD)|g' \
	      -e 's|@''HAVE_MKNODAT''@|$(HAVE_MKNODAT)|g' \
	      -e 's|@''HAVE_UTIMENSAT''@|$(HAVE_UTIMENSAT)|g' \
	      -e 's|@''REPLACE_FSTAT''@|$(REPLACE_FSTAT)|g' \
	      -e 's|@''REPLACE_FSTATAT''@|$(REPLACE_FSTATAT)|g' \
	      -e 's|@''REPLACE_FUTIMENS''@|$(REPLACE_FUTIMENS)|g' \
	      -e 's|@''REPLACE_LSTAT''@|$(REPLACE_LSTAT)|g' \
	      -e 's|@''REPLACE_MKDIR''@|$(REPLACE_MKDIR)|g' \
	      -e 's|@''REPLACE_MKFIFO''@|$(REPLACE_MKFIFO)|g' \
	      -e 's|@''REPLACE_MKNOD''@|$(REPLACE_MKNOD)|g' \
	      -e 's|@''REPLACE_STAT''@|$(REPLACE_STAT)|g' \
	      -e 's|@''REPLACE_UTIMENSAT''@|$(REPLACE_UTIMENSAT)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)' \
	      < $(srcdir)/sys_stat.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += sys/stat.h sys/stat.h-t

MOSTLYCLEANDIRS = build/Debug

MOSTLYCLEANDIRS += sys

BUILT_SOURCES += string.h

# We need the following in order to create <string.h> when the system
# does NOT have one that works with the given compiler.
string.h: string.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(ARG_NONNULL_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */' && \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_STRING_H''@|$(NEXT_STRING_H)|g' \
	      -e 's/@''GNULIB_FFSL''@/$(GNULIB_FFSL)/g' \
	      -e 's/@''GNULIB_FFSLL''@/$(GNULIB_FFSLL)/g' \
	      -e 's/@''GNULIB_MBSLEN''@/$(GNULIB_MBSLEN)/g' \
	      -e 's/@''GNULIB_MBSNLEN''@/$(GNULIB_MBSNLEN)/g' \
	      -e 's/@''GNULIB_MBSCHR''@/$(GNULIB_MBSCHR)/g' \
	      -e 's/@''GNULIB_MBSRCHR''@/$(GNULIB_MBSRCHR)/g' \
	      -e 's/@''GNULIB_MBSSTR''@/$(GNULIB_MBSSTR)/g' \
	      -e 's/@''GNULIB_MBSCASECMP''@/$(GNULIB_MBSCASECMP)/g' \
	      -e 's/@''GNULIB_MBSNCASECMP''@/$(GNULIB_MBSNCASECMP)/g' \
	      -e 's/@''GNULIB_MBSPCASECMP''@/$(GNULIB_MBSPCASECMP)/g' \
	      -e 's/@''GNULIB_MBSCASESTR''@/$(GNULIB_MBSCASESTR)/g' \
	      -e 's/@''GNULIB_MBSCSPN''@/$(GNULIB_MBSCSPN)/g' \
	      -e 's/@''GNULIB_MBSPBRK''@/$(GNULIB_MBSPBRK)/g' \
	      -e 's/@''GNULIB_MBSSPN''@/$(GNULIB_MBSSPN)/g' \
	      -e 's/@''GNULIB_MBSSEP''@/$(GNULIB_MBSSEP)/g' \
	      -e 's/@''GNULIB_MBSTOK_R''@/$(GNULIB_MBSTOK_R)/g' \
	      -e 's/@''GNULIB_MEMCHR''@/$(GNULIB_MEMCHR)/g' \
	      -e 's/@''GNULIB_MEMMEM''@/$(GNULIB_MEMMEM)/g' \
	      -e 's/@''GNULIB_MEMPCPY''@/$(GNULIB_MEMPCPY)/g' \
	      -e 's/@''GNULIB_MEMRCHR''@/$(GNULIB_MEMRCHR)/g' \
	      -e 's/@''GNULIB_RAWMEMCHR''@/$(GNULIB_RAWMEMCHR)/g' \
	      -e 's/@''GNULIB_STPCPY''@/$(GNULIB_STPCPY)/g' \
	      -e 's/@''GNULIB_STPNCPY''@/$(GNULIB_STPNCPY)/g' \
	      -e 's/@''GNULIB_STRCHRNUL''@/$(GNULIB_STRCHRNUL)/g' \
	      -e 's/@''GNULIB_STRDUP''@/$(GNULIB_STRDUP)/g' \
	      -e 's/@''GNULIB_STRNCAT''@/$(GNULIB_STRNCAT)/g' \
	      -e 's/@''GNULIB_STRNDUP''@/$(GNULIB_STRNDUP)/g' \
	      -e 's/@''GNULIB_STRNLEN''@/$(GNULIB_STRNLEN)/g' \
	      -e 's/@''GNULIB_STRPBRK''@/$(GNULIB_STRPBRK)/g' \
	      -e 's/@''GNULIB_STRSEP''@/$(GNULIB_STRSEP)/g' \
	      -e 's/@''GNULIB_STRSTR''@/$(GNULIB_STRSTR)/g' \
	      -e 's/@''GNULIB_STRCASESTR''@/$(GNULIB_STRCASESTR)/g' \
	      -e 's/@''GNULIB_STRTOK_R''@/$(GNULIB_STRTOK_R)/g' \
	      -e 's/@''GNULIB_STRERROR''@/$(GNULIB_STRERROR)/g' \
	      -e 's/@''GNULIB_STRERROR_R''@/$(GNULIB_STRERROR_R)/g' \
	      -e 's/@''GNULIB_STRSIGNAL''@/$(GNULIB_STRSIGNAL)/g' \
	      -e 's/@''GNULIB_STRVERSCMP''@/$(GNULIB_STRVERSCMP)/g' \
	      < $(srcdir)/string.in.h | \
	  sed -e 's|@''HAVE_FFSL''@|$(HAVE_FFSL)|g' \
	      -e 's|@''HAVE_FFSLL''@|$(HAVE_FFSLL)|g' \
	      -e 's|@''HAVE_MBSLEN''@|$(HAVE_MBSLEN)|g' \
	      -e 's|@''HAVE_MEMCHR''@|$(HAVE_MEMCHR)|g' \
	      -e 's|@''HAVE_DECL_MEMMEM''@|$(HAVE_DECL_MEMMEM)|g' \
	      -e 's|@''HAVE_MEMPCPY''@|$(HAVE_MEMPCPY)|g' \
	      -e 's|@''HAVE_DECL_MEMRCHR''@|$(HAVE_DECL_MEMRCHR)|g' \
	      -e 's|@''HAVE_RAWMEMCHR''@|$(HAVE_RAWMEMCHR)|g' \
	      -e 's|@''HAVE_STPCPY''@|$(HAVE_STPCPY)|g' \
	      -e 's|@''HAVE_STPNCPY''@|$(HAVE_STPNCPY)|g' \
	      -e 's|@''HAVE_STRCHRNUL''@|$(HAVE_STRCHRNUL)|g' \
	      -e 's|@''HAVE_DECL_STRDUP''@|$(HAVE_DECL_STRDUP)|g' \
	      -e 's|@''HAVE_DECL_STRNDUP''@|$(HAVE_DECL_STRNDUP)|g' \
	      -e 's|@''HAVE_DECL_STRNLEN''@|$(HAVE_DECL_STRNLEN)|g' \
	      -e 's|@''HAVE_STRPBRK''@|$(HAVE_STRPBRK)|g' \
	      -e 's|@''HAVE_STRSEP''@|$(HAVE_STRSEP)|g' \
	      -e 's|@''HAVE_STRCASESTR''@|$(HAVE_STRCASESTR)|g' \
	      -e 's|@''HAVE_DECL_STRTOK_R''@|$(HAVE_DECL_STRTOK_R)|g' \
	      -e 's|@''HAVE_DECL_STRERROR_R''@|$(HAVE_DECL_STRERROR_R)|g' \
	      -e 's|@''HAVE_DECL_STRSIGNAL''@|$(HAVE_DECL_STRSIGNAL)|g' \
	      -e 's|@''HAVE_STRVERSCMP''@|$(HAVE_STRVERSCMP)|g' \
	      -e 's|@''REPLACE_STPNCPY''@|$(REPLACE_STPNCPY)|g' \
	      -e 's|@''REPLACE_MEMCHR''@|$(REPLACE_MEMCHR)|g' \
	      -e 's|@''REPLACE_MEMMEM''@|$(REPLACE_MEMMEM)|g' \
	      -e 's|@''REPLACE_STRCASESTR''@|$(REPLACE_STRCASESTR)|g' \
	      -e 's|@''REPLACE_STRCHRNUL''@|$(REPLACE_STRCHRNUL)|g' \
	      -e 's|@''REPLACE_STRDUP''@|$(REPLACE_STRDUP)|g' \
	      -e 's|@''REPLACE_STRSTR''@|$(REPLACE_STRSTR)|g' \
	      -e 's|@''REPLACE_STRERROR''@|$(REPLACE_STRERROR)|g' \
	      -e 's|@''REPLACE_STRERROR_R''@|$(REPLACE_STRERROR_R)|g' \
	      -e 's|@''REPLACE_STRNCAT''@|$(REPLACE_STRNCAT)|g' \
	      -e 's|@''REPLACE_STRNDUP''@|$(REPLACE_STRNDUP)|g' \
	      -e 's|@''REPLACE_STRNLEN''@|$(REPLACE_STRNLEN)|g' \
	      -e 's|@''REPLACE_STRSIGNAL''@|$(REPLACE_STRSIGNAL)|g' \
	      -e 's|@''REPLACE_STRTOK_R''@|$(REPLACE_STRTOK_R)|g' \
	      -e 's|@''UNDEFINE_STRTOK_R''@|$(UNDEFINE_STRTOK_R)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)'; \
	      < $(srcdir)/string.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += string.h string.h-t

BUILT_SOURCES += strings.h

# We need the following in order to create <strings.h> when the system
# does NOT have one that works with the given compiler.
strings.h: strings.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(WARN_ON_USE_H) $(ARG_NONNULL_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */' && \
	  sed -e 's|@''GUARD_PREFIX''@|${gl_include_guard_prefix}|g' \
	      -e 's|@''HAVE_STRINGS_H''@|$(HAVE_STRINGS_H)|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_STRINGS_H''@|$(NEXT_STRINGS_H)|g' \
	      -e 's|@''GNULIB_FFS''@|$(GNULIB_FFS)|g' \
	      -e 's|@''HAVE_FFS''@|$(HAVE_FFS)|g' \
	      -e 's|@''HAVE_STRCASECMP''@|$(HAVE_STRCASECMP)|g' \
	      -e 's|@''HAVE_DECL_STRNCASECMP''@|$(HAVE_DECL_STRNCASECMP)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)' \
	      < $(srcdir)/strings.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += strings.h strings.h-t

libUnixToOSX_la_SOURCES += glthread/lock.h glthread/lock.c

libUnixToOSX_la_SOURCES += glthread/tls.h glthread/tls.c

libUnixToOSX_la_SOURCES += glthread/threadlib.c

libUnixToOSX_la_SOURCES += glthread/thread.h glthread/thread.c
