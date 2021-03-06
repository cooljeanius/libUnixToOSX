/* isnanl-nolibm.h: Test for NaN that does not need libm.
 * Copyright (C) 2007-2012 Free Software Foundation, Inc.
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

#ifndef __ISNANL_NOLIBM_H__
#define __ISNANL_NOLIBM_H__ 1

#if defined(HAVE_ISNANL_IN_LIBC) && HAVE_ISNANL_IN_LIBC
/* Get declaration of isnan macro or (older) isnanl function.  */
# include <math.h>
# if defined(__GNUC__) && (__GNUC__ >= 4)
   /* GCC 4.0 and newer provides three built-ins for isnan.  */
#  undef isnanl
#  define isnanl(x) __builtin_isnanl ((long double)(x))
# elif defined isnan
#  undef isnanl
#  define isnanl(x) isnan ((long double)(x))
# endif /* GCC 4+ || isnan */
#else /* do not already HAVE_ISNANL_IN_LIBC: */
/* Test whether X is a NaN.  */
# undef isnanl
# define isnanl rpl_isnanl
extern int isnanl(long double x);
#endif /* HAVE_ISNANL_IN_LIBC */

#endif /* !__ISNANL_NOLIBM_H__ */

/* EOF */
