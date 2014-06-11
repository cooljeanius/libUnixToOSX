/* fts-cylce.c: Detect cycles in file tree walks.
 *
 * Copyright (C) 2003-2006, 2009-2012 Free Software Foundation, Inc.
 *
 * Written by Jim Meyering.
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
#  pragma GCC diagnostic ignored "-Wunused-macros"
# endif /* GCC 4.1+ */
#endif /* gcc */

#ifndef __FTS_CYCLE_C__
#define __FTS_CYCLE_C__ 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */
#include "cycle-check.h"
#include "hash.h"
#include "fts_.h"

#if defined(HAVE_FTS_H) && (!defined(FTSENT) || !defined(FTS)) && !defined(_FTS_H)
# include <fts.h>
#endif /* HAVE_FTS_H && (!FTSENT || !FTS) && !_FTS_H */

#if !defined(malloc) || !defined(free)
# ifdef HAVE_STDLIB_H
#  include <stdlib.h>
# else
#  ifdef HAVE_MALLOC_H
#   include <malloc.h>
#  else
#   ifdef HAVE_MALLOC_MALLOC_H
#    include <malloc/malloc.h>
#   endif /* HAVE_MALLOC_MALLOC_H */
#  endif /* HAVE_MALLOC_H */
# endif /* HAVE_STDLIB_H */
#endif /* !malloc || !free */

/* Use each of these to map a device/inode pair to an FTSENT.  */
struct Active_dir
{
  dev_t dev;
  ino_t ino;
  FTSENT *fts_ent;
};

static bool AD_compare(void const *x, void const *y)
{
  struct Active_dir const *ax;
  struct Active_dir const *ay;

  ax = (const struct Active_dir *)x;
  ay = (const struct Active_dir *)y;
  return ((ax->ino == ay->ino)
		  && (ax->dev == ay->dev));
}

static size_t AD_hash(void const *x, size_t table_size)
{
  struct Active_dir const *ax;
  ax = (const struct Active_dir *)x;
  return ((uintmax_t)ax->ino % table_size);
}

/* the functions after this are only used when this file is being included from
 * fts.c, so ignore warnings about them being unused if this file is being
 * compiled all by itself: */
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6))
#  if !defined(__FTS_C__)
#   pragma GCC diagnostic ignored "-Wunused-function"
#  endif /* !__FTS_C__ */
# endif /* GCC 4.6+ */
#endif /* GCC */

/* Set up the cycle-detection machinery:  */
static bool
setup_dir(FTS *fts)
{
  if (fts->fts_options & (FTS_TIGHT_CYCLE_CHECK | FTS_LOGICAL)) {
      enum { HT_INITIAL_SIZE = 31 };
      fts->fts_cycle.ht = hash_initialize((size_t)HT_INITIAL_SIZE, NULL,
										  AD_hash, AD_compare, free);
      if (! fts->fts_cycle.ht) {
		  return false;
	  }
  } else {
      fts->fts_cycle.state = (struct cycle_check_state *)malloc(sizeof *fts->fts_cycle.state);
      if (! fts->fts_cycle.state) {
		  return false;
	  }
      cycle_check_init(fts->fts_cycle.state);
  }

  return true;
}

/* Enter a directory during a file tree walk:  */
static bool enter_dir(FTS *fts, FTSENT *ent)
{
  if (fts->fts_options & (FTS_TIGHT_CYCLE_CHECK | FTS_LOGICAL)) {
      struct stat const *st;
      struct Active_dir *ad;
      struct Active_dir *ad_from_table;

	  st = ent->fts_statp;
	  ad = (struct Active_dir *)malloc(sizeof(*ad));

      if (!ad) {
		  return false;
	  }

      ad->dev = st->st_dev;
      ad->ino = st->st_ino;
      ad->fts_ent = ent;

      /* See if we have already encountered this directory.
       * This can happen when following symlinks as well as
       * with a corrupted directory hierarchy. */
      ad_from_table = (struct Active_dir *)hash_insert(fts->fts_cycle.ht, ad);

      if (ad_from_table != ad) {
          free(ad);
          if (!ad_from_table) {
			  return false;
		  }

          /* There was an entry with matching dev/inode already in the table.
           * Record the fact that we've found a cycle.  */
          ent->fts_cycle = ad_from_table->fts_ent;
          ent->fts_info = FTS_DC;
	  }
  } else {
      if (cycle_check (fts->fts_cycle.state, ent->fts_statp)) {
          /* FIXME: setting fts_cycle like this is NOT proper.
           * To do what the documentation requires, we would have to
           * go around the cycle again and find the right entry.
           * But no callers in coreutils use the fts_cycle member. */
          ent->fts_cycle = ent;
          ent->fts_info = FTS_DC;
	  }
  }

  return true;
}

/* Leave a directory during a file tree walk:  */
static void leave_dir(FTS *fts, FTSENT *ent)
{
  struct stat const *st = ent->fts_statp;
  if (fts->fts_options & (FTS_TIGHT_CYCLE_CHECK | FTS_LOGICAL)) {
      struct Active_dir obj;
      void *found;
      obj.dev = st->st_dev;
      obj.ino = st->st_ino;
      found = hash_delete (fts->fts_cycle.ht, &obj);
      if (!found) {
		  abort();
	  }
      free(found);
  } else {
      FTSENT *parent = ent->fts_parent;
      if ((parent != NULL) && (0 <= parent->fts_level)) {
        CYCLE_CHECK_REFLECT_CHDIR_UP(fts->fts_cycle.state,
									 *(parent->fts_statp), *st);
	  }
  }
}

/* Free any memory used for cycle detection:  */
static void free_dir(FTS *sp)
{
  if (sp->fts_options & (FTS_TIGHT_CYCLE_CHECK | FTS_LOGICAL)) {
      if (sp->fts_cycle.ht) {
		  hash_free (sp->fts_cycle.ht);
	  }
  } else {
	  free(sp->fts_cycle.state);
  }
}

/* EOF */

#endif /* !__FTS_CYCLE_C__ */
