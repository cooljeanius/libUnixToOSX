/* canonicalize.h: Return the canonical absolute name of a given file.
 * Copyright (C) 1996-2007, 2009-2012 Free Software Foundation, Inc.
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

#ifndef CANONICALIZE_H_
# define CANONICALIZE_H_

#include <stdlib.h> /* for canonicalize_file_name */

#define CAN_MODE_MASK (CAN_EXISTING | CAN_ALL_BUT_LAST | CAN_MISSING)

enum canonicalize_mode_t
  {
    /* All components must exist: */
    CAN_EXISTING = 0,

    /* All components excluding last one must exist: */
    CAN_ALL_BUT_LAST = 1,

    /* No requirements on components existence: */
    CAN_MISSING = 2,

    /* Corresponds to the above define: */
    CAN_MODE_MASK_ENUMERATOR_VALUE = 3,

    /* Do NOT expand symlinks: */
    CAN_NOLINKS = 4
  };
typedef enum canonicalize_mode_t canonicalize_mode_t;

/* Return the canonical absolute name of file NAME, while treating
 * missing elements according to CAN_MODE.  A canonical name
 * does not contain any `.', `..' components nor any repeated file name
 * separators ('/') or, depending on other CAN_MODE flags, symlinks.
 * Whether components must exist or not depends on canonicalize mode.
 * The result is malloc'd.  */
char *canonicalize_filename_mode(const char *, canonicalize_mode_t);

/* prototype for function from canonicalize-lgpl.c: */
#ifndef __canonicalize_file_name
/* same set of conditions that canonicalize-lgpl.c uses: */
# if (!defined(HAVE_CANONICALIZE_FILE_NAME) || (defined(HAVE_CANONICALIZE_FILE_NAME) && !HAVE_CANONICALIZE_FILE_NAME)) \
     || !FUNC_REALPATH_WORKS || defined _LIBC
#  ifdef _LIBC
#   include <shlib-compat.h>
#  else
#   define __canonicalize_file_name canonicalize_file_name
#  endif /* _LIBC */
char *__canonicalize_file_name(const char *name);
# endif /* !HAVE_CANONICALIZE_FILE_NAME || !FUNC_REALPATH_WORKS || _LIBC */
#endif /* !__canonicalize_file_name */

#endif /* !CANONICALIZE_H_ */

/* EOF */
