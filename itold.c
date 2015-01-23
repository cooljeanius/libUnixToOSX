/* itold.c: Replacement for 'int' to 'long double' conversion routine.
 * Copyright (C) 2011-2012 Free Software Foundation, Inc.
 * Written by Bruno Haible <bruno@clisp.org>, 2011.
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

#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 1))
#   pragma GCC diagnostic ignored "-Wredundant-decls"
# endif /* GCC 4.1+ */
#endif /* gcc */

#include <config.h>

/* Specification: */
#include <float.h>

#include "rpl_misc_funcs.h"

void
_Qp_itoq(long double *result, int a)
{
  /* Convert from 'int' to 'double', then from 'double' to 'long double': */
  *result = (double)a;
}

/* EOF */
