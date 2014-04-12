/* isnand.c: Test for NaN that does not need libm.
 * Copyright (C) 2008-2012 Free Software Foundation, Inc.
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

/* Written by Bruno Haible <bruno@clisp.org>, 2008.  */

#ifndef __ISNAND_C__
#define __ISNAND_C__ 1

/* isnan.c assumes it is being included from this file if USE_FLOAT is
 * undefined: */
#ifdef USE_FLOAT
# undef USE_FLOAT
#endif /* USE_FLOAT */

#include "isnan.c"

#endif /* __ISNAND_C__ */

/* EOF */
