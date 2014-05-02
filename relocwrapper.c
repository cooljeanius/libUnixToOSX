/* relocwrapper.c: Relocating wrapper program.
 * Copyright (C) 2003, 2005-2007, 2009-2012 Free Software Foundation, Inc.
 * Written by Bruno Haible <bruno@clisp.org>, 2003.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Dependencies:
 *  relocwrapper
 *   -> progname
 *   -> progreloc
 *       -> areadlink
 *          -> careadlinkat
 *            -> allocator
 *            -> readlink
 *       -> canonicalize-lgpl
 *          -> malloca
 *          -> readlink
 *   -> relocatable
 *   -> setenv
 *      -> malloca
 *   -> c-ctype
 *
 * Macros that need to be set while compiling this file:
 *   - ENABLE_RELOCATABLE 1
 *   - INSTALLPREFIX the base installation directory
 *   - INSTALLDIR the directory into which this program is installed
 *   - LIBPATHVAR the platform dependent runtime library path variable
 *   - LIBDIRS a comma-terminated list of strings representing the list of
 *     directories that contain the libraries at installation time
 *
 * We do NOT want to internationalize this wrapper because then it would
 * depend on libintl and therefore need relocation itself.  So use only
 * libc functions, no gettext(), no error(), no xmalloc(), no xsetenv().
 */

#ifndef _RELOCWRAPPER_C_
#define _RELOCWRAPPER_C_ 1

#define _GL_USE_STDLIB_ALLOC 1
#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "progname.h"
#include "relocatable.h"
#include "c-ctype.h"
#include "verify.h"

#include "configmake.h"

#ifndef EXEEXT
# define EXEEXT ""
#endif /* !EXEEXT */

/* Use the system functions, not the gnulib overrides in this file.  */
#undef fprintf

/* Return a copy of the filename, with an extra ".bin" at the end.
 * More generally, it replaces "${EXEEXT}" at the end with ".bin${EXEEXT}".  */
static char *
add_dotbin(const char *filename)
{
  size_t filename_len = strlen(filename);
  char *result = (char *)malloc(filename_len + 4 + 1); /* why not just "+ 5"? */

  if (result != NULL) {
      if (sizeof(EXEEXT) > sizeof("")) {
          /* EXEEXT handling.  */
          const size_t exeext_len = sizeof (EXEEXT) - sizeof ("");
          static const char exeext[] = EXEEXT;
          if (filename_len > exeext_len) {
              /* Compare using an inlined copy of c_strncasecmp(), because
               * the filenames may have undergone a case conversion since
               * they were packaged.  In other words, EXEEXT may be ".exe"
               * on one system and ".EXE" on another.  */
              const char *s1 = (filename + filename_len - exeext_len);
              const char *s2 = exeext;
              for (; (*s1 != '\0'); s1++, s2++) {
                  unsigned char c1;
                  unsigned char c2;
				  c1 = (unsigned char)*s1;
				  c2 = (unsigned char)*s2;
                  if (c_tolower(c1) != c_tolower(c2)) {
					  goto simple_append;
				  }
			  }
              /* Insert ".bin" before EXEEXT or its equivalent.  */
              memcpy (result, filename, filename_len - exeext_len);
              memcpy (result + filename_len - exeext_len, ".bin", 4);
              memcpy (result + filename_len - exeext_len + 4,
                      filename + filename_len - exeext_len,
                      exeext_len + 1);
              return result;
            }
        }
     simple_append:
		/* Simply append ".bin".  */
		memcpy(result, filename, filename_len);
		memcpy((result + filename_len), ".bin", (4 + 1)); /* why not just 5? */
		return result;
    }
  else
    {
      fprintf(stderr, "%s: %s\n", program_name, "memory exhausted");
      exit(1);
    }
}

#ifndef LIBDIRS
# if defined(LIBDIR) && 0
#  define LIBDIRS LIBDIR, /* pasting with '##' fails here */
# else
#  define LIBDIRS NULL, /* likewise in this condition */
# endif /* LIBDIR */
#endif /* !LIBDIRS */
/* List of directories that contain the libraries.  */
static const char *libdirs[] = { LIBDIRS NULL };
/* Verify that at least one directory is given.  */
verify((sizeof(libdirs) / sizeof(libdirs[0])) > 1);

/* Relocate the list of directories that contain the libraries.  */
static void
relocate_libdirs()
{
  size_t i;

  for ((i = 0); (i < ((sizeof(libdirs) / sizeof(libdirs[0])) - 1)); i++) {
	  libdirs[i] = relocate(libdirs[i]);
  }
}

#ifndef LIBPATHVAR
# if defined _WIN32 || defined __WIN32__ || defined __CYGWIN__
/* Native Windows, Cygwin */
#  define LIBPATHVAR "PATH"
# elif defined __APPLE__ && defined __MACH__
/* Mac OS X */
#  define LIBPATHVAR "DYLD_LIBRARY_PATH"
# else
/* "Normal" Unix */
#  define LIBPATHVAR "LD_LIBRARY_PATH"
# endif
#endif /* !LIBPATHVAR */
/* Activate the list of directories in the LIBPATHVAR.  */
static void
activate_libdirs()
{
  const char *old_value;
  size_t total;
  size_t i;
  char *value;
  char *p;

  old_value = getenv(LIBPATHVAR);
  if (old_value == NULL)
    old_value = "";

  total = 0;
  for (i = 0; i < sizeof (libdirs) / sizeof (libdirs[0]) - 1; i++)
    total += strlen (libdirs[i]) + 1;
  total += strlen (old_value) + 1;

  value = (char *) malloc (total);
  if (value == NULL)
    {
      fprintf (stderr, "%s: %s\n", program_name, "memory exhausted");
      exit (1);
    }
  p = value;
  for (i = 0; i < sizeof (libdirs) / sizeof (libdirs[0]) - 1; i++)
    {
      size_t len = strlen (libdirs[i]);
      memcpy (p, libdirs[i], len);
      p += len;
      *p++ = ':';
    }
  if (old_value[0] != '\0')
    strcpy (p, old_value);
  else
    p[-1] = '\0';

  if (setenv (LIBPATHVAR, value, 1) < 0)
    {
      fprintf (stderr, "%s: %s\n", program_name, "memory exhausted");
      exit (1);
    }
}

#ifndef INSTALLDIR
# if defined BINDIR
#  define INSTALLDIR BINDIR
# elif defined SBINDIR
#  define INSTALLDIR SBINDIR
# elif defined INSTALLPREFIX
#  define INSTALLDIR INSTALLPREFIX
# else
#  define INSTALLDIR "." /* I was tempted to use '/dev/null' in this case... */
# endif /* BINDIR || SBINDIR || INSTALLPREFIX */
#endif /* !INSTALLDIR */
int
main(int argc, char *argv[])
{
  char *full_program_name;

  /* Set the program name and perform preparations for
   * get_full_program_name() and relocate().  */
  set_program_name_and_installdir(argv[0], INSTALLPREFIX, INSTALLDIR);

  /* Get the full program path. (Important if accessed through a symlink.)  */
  full_program_name = get_full_program_name();
  if (full_program_name == NULL) {
	  full_program_name = argv[0];
  }

  /* Invoke the real program, with suffix ".bin".  */
  argv[0] = add_dotbin(full_program_name);
  relocate_libdirs();
  activate_libdirs();
  execv(argv[0], argv);
  fprintf(stderr, "%s: tried executing %s with %i argument(s), \
		  but failed with error: '%s'\n",
		  program_name, argv[0], argc, strerror(errno));
  exit(127);
}

#endif /* !_RELOCWRAPPER_C_ */

/* EOF */
