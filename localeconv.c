/* localeconv.c: Query locale dependent information for formatting numbers.
 * Copyright (C) 2012 Free Software Foundation, Inc.
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

#include <config.h>

/* Specification.  */
#include <locale.h>

#if HAVE_STRUCT_LCONV_DECIMAL_POINT

/* Override for platforms where 'struct lconv' lacks the int_p_*, int_n_*
 * members.  */

struct lconv *
localeconv(void)
{
  static struct lconv result;
# undef lconv
# undef localeconv
  struct lconv *sys_result = localeconv();

  result.decimal_point = sys_result->decimal_point;
  result.thousands_sep = sys_result->thousands_sep;
  result.grouping = sys_result->grouping;
  result.mon_decimal_point = sys_result->mon_decimal_point;
  result.mon_thousands_sep = sys_result->mon_thousands_sep;
  result.mon_grouping = sys_result->mon_grouping;
  result.positive_sign = sys_result->positive_sign;
  result.negative_sign = sys_result->negative_sign;
  result.currency_symbol = sys_result->currency_symbol;
  result.frac_digits = sys_result->frac_digits;
  result.p_cs_precedes = sys_result->p_cs_precedes;
  result.p_sign_posn = sys_result->p_sign_posn;
  result.p_sep_by_space = sys_result->p_sep_by_space;
  result.n_cs_precedes = sys_result->n_cs_precedes;
  result.n_sign_posn = sys_result->n_sign_posn;
  result.n_sep_by_space = sys_result->n_sep_by_space;
  result.int_curr_symbol = sys_result->int_curr_symbol;
  result.int_frac_digits = sys_result->int_frac_digits;
  result.int_p_cs_precedes = sys_result->p_cs_precedes;
  result.int_p_sign_posn = sys_result->p_sign_posn;
  result.int_p_sep_by_space = sys_result->p_sep_by_space;
  result.int_n_cs_precedes = sys_result->n_cs_precedes;
  result.int_n_sign_posn = sys_result->n_sign_posn;
  result.int_n_sep_by_space = sys_result->n_sep_by_space;

  return &result;
}

#else /* !HAVE_STRUCT_LCONV_DECIMAL_POINT: */

/* Override for platforms where 'struct lconv' is a dummy.  */

# include <limits.h>

# if defined(__clang__)
#  define COMPILE_TIME_CONSTANT const
#  define STATIC_SPECIFIER /* nothing */
# else /* not clang: */
#  define COMPILE_TIME_CONSTANT /* nothing */
#  define STATIC_SPECIFIER static
# endif /* __clang__ */

# ifndef CHAR_MAX
#  define CHAR_MAX 127 /* what it is on darwin by default */
# endif /* !CHAR_MAX */

struct lconv *
localeconv(void)
{
  STATIC_SPECIFIER COMPILE_TIME_CONSTANT char null_str[1] = "";
  STATIC_SPECIFIER COMPILE_TIME_CONSTANT char *null_string_char = &null_str[0];
  STATIC_SPECIFIER COMPILE_TIME_CONSTANT char decptstr[2] = ".";
  STATIC_SPECIFIER COMPILE_TIME_CONSTANT struct lconv result =
    {
      /* decimal_point */ (char *)decptstr,
      /* thousands_sep */ (char *)null_str,
      /* grouping */ (char *)null_str,
      /* mon_decimal_point */ (char *)null_str,
      /* mon_thousands_sep */ (char *)null_str,
      /* mon_grouping */ (char *)null_str,
      /* positive_sign */ (char *)null_str,
      /* negative_sign */ (char *)null_str,
      /* currency_symbol */ (char *)null_str,
      /* frac_digits */ (char *)CHAR_MAX,
      /* p_cs_precedes */ CHAR_MAX,
      /* p_sign_posn */ CHAR_MAX,
      /* p_sep_by_space */ CHAR_MAX,
      /* n_cs_precedes */ CHAR_MAX,
      /* n_sign_posn */ CHAR_MAX,
      /* n_sep_by_space */ CHAR_MAX,
      /* int_curr_symbol */ '\0',
      /* int_frac_digits */ CHAR_MAX,
      /* int_p_cs_precedes */ CHAR_MAX,
      /* int_p_sign_posn */ CHAR_MAX,
      /* int_p_sep_by_space */ CHAR_MAX,
      /* int_n_cs_precedes */ CHAR_MAX,
      /* int_n_sign_posn */ CHAR_MAX,
      /* int_n_sep_by_space */ CHAR_MAX
    };
  STATIC_SPECIFIER struct lconv *retv = (struct lconv *)&result;

  /* dummy condition to use value stored to 'null_string_char': */
  if (null_string_char == '\0') {
	  ;
  }

#ifdef __clang_analyzer__
  /* dummy condition to use value stored to 'retv': */
  if (retv == NULL) {
	  ;
  }
  /* clang's static analyzer complains about addresses of stack memory being
   * returned, so tell it that we are returning something else: */
  return (struct lconv *)NULL;
#else /* normal compiling: */
  return retv;
#endif /* __clang_analyzer__ */
}

#endif /* HAVE_STRUCT_LCONV_DECIMAL_POINT */

/* EOF */
