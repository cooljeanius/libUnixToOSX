# Make Autoscan library.

# Copyright (C) 2001-2002, 2009-2012 Free Software Foundation, Inc.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

autoscanlibdir = $(pkgdatadir)/autoscan

EXTRA_DIST = autoscan.pre
nodist_autoscanlib_DATA = autoscan.list
CLEANFILES = autoscan.list
DISTCLEANFILES= .DS_Store
MY_AUTOM4TE = autom4te

AM_V_AUTOM4TE_FLAGS = $(am__v_AUTOM4TE_FLAGS_@AM_V@)
am__v_AUTOM4TE_FLAGS_ = $(am__v_AUTOM4TE_FLAGS_@AM_DEFAULT_V@)
am__v_AUTOM4TE_FLAGS_0 =
am__v_AUTOM4TE_FLAGS_1 = --verbose

## ------------------------ ##
## Building autoscan.list.  ##
## ------------------------ ##

#FIXME: this fails to add our new autoscan checks from
# $(top_srcdir)/m4/autoscan-warnings-for-OSX.m4:
autoscan.list: $(srcdir)/autoscan.pre Makefile.am $(top_srcdir)/autom4te.cache $(top_srcdir)/aclocal.m4
	$(AM_V_GEN)echo '# Automatically Generated: do not edit this file' >autoscan.list; \
	$(SED) '/^[#]/!q' $(srcdir)/autoscan.pre >>autoscan.list; \
	( \
	  $(SED) -n '/^[^#]/p' $(srcdir)/autoscan.pre; \
	  $(MY_AUTOM4TE) $(AM_V_AUTOM4TE_FLAGS) --cache '$(top_srcdir)/autom4te.cache' -I$(top_srcdir) -I$(top_srcdir)/m4 -M -l autoconf -t'AN_OUTPUT:$$1: $$2		$$3' \
	) | LC_ALL=C sort >>autoscan.list

$(top_srcdir)/autom4te.cache:
	$(MAKE) -C $(top_srcdir) configure.scan
