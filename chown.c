/* chown.c: provide consistent interface to chown for systems that do NOT
 * interpret an ID of -1 as meaning "do NOT change the corresponding ID".
 *
 * Copyright (C) 1997, 2004-2007, 2009-2012 Free Software Foundation, Inc.
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

/* written by Jim Meyering */

#include <config.h>

/* Specification: */
#include <unistd.h>

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

#include "rpl_misc_funcs.h"

#if !HAVE_CHOWN
/* Simple stub that always fails with ENOSYS, for mingw: */
int chown(const char *file _GL_UNUSED, uid_t uid _GL_UNUSED,
		  gid_t gid _GL_UNUSED)
{
  errno = ENOSYS;
  return -1;
}
#else /* do HAVE_CHOWN: */

/* Below we refer to the system's chown(). */
# undef chown

/* The results of open() in this file are not used with fchdir, therefore save
 * some unnecessary work in fchdir.c. */
# undef open
# undef close

/* Provide a more-closely POSIX-conforming version of chown on
 * systems with one or both of the following problems:
 * - chown does NOT treat an ID of -1 as meaning
 *   "don NOT change the corresponding ID".
 * - chown does NOT dereference symlinks. */
int rpl_chown(const char *file, uid_t uid, gid_t gid)
{
  struct stat st;
  bool stat_valid = false;
  int result;

# if defined(CHOWN_CHANGE_TIME_BUG) && CHOWN_CHANGE_TIME_BUG
  if ((gid != (gid_t)-1) || (uid != (uid_t)-1)) {
      if (stat(file, &st)) {
		  return -1;
	  }
      stat_valid = true;
  }
# endif /* CHOWN_CHANGE_TIME_BUG */

# if defined(CHOWN_FAILS_TO_HONOR_ID_OF_NEGATIVE_ONE) && CHOWN_FAILS_TO_HONOR_ID_OF_NEGATIVE_ONE
  if ((gid == (gid_t)-1) || (uid == (uid_t)-1)) {
      /* Stat file to get id(s) that should remain unchanged.  */
      if (!stat_valid && stat(file, &st)) {
		  return -1;
	  }
      if (gid == (gid_t)-1) {
		  gid = st.st_gid;
	  }
      if (uid == (uid_t)-1) {
		  uid = st.st_uid;
	  }
  }
# endif /* CHOWN_FAILS_TO_HONOR_ID_OF_NEGATIVE_ONE */

# if defined(CHOWN_MODIFIES_SYMLINK) && CHOWN_MODIFIES_SYMLINK
  {
    /* Handle the case in which the system-supplied chown function does *not*
	 * follow symlinks. Instead, it changes permissions on the symlink itself.
	 * To work around that, we open the file (but this can fail due to lack
	 * of read or write permission) & use fchown on the resulting descriptor. */
    int open_flags = (O_NONBLOCK | O_NOCTTY);
    int fd = open(file, (O_RDONLY | open_flags));
    if ((0 <= fd)
        || ((errno == EACCES)
            && (0 <= (fd = open(file, (O_WRONLY | open_flags)))))) {
        int saved_errno;
        bool fchown_socket_failure;

        result = fchown(fd, uid, gid);
        saved_errno = errno;

        /* POSIX says fchown can fail with errno == EINVAL on sockets and pipes,
		 * so fall back on chown in that case: */
        fchown_socket_failure =
          ((result != 0) && (saved_errno == EINVAL)
           && (fstat(fd, &st) == 0)
           && (S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode)));

        close(fd);

        if (! fchown_socket_failure) {
            errno = saved_errno;
            return result;
		}
	} else if (errno != EACCES) {
		return -1;
	}
  }
# endif /* CHOWN_MODIFIES_SYMLINK */

# if defined(CHOWN_TRAILING_SLASH_BUG) && CHOWN_TRAILING_SLASH_BUG
  if (!stat_valid) {
      size_t len = strlen(file);
      if (len && (file[(len - 1)] == '/') && stat(file, &st)) {
		  return -1;
	  }
  }
# endif /* CHOWN_TRAILING_SLASH_BUG */

  result = chown(file, uid, gid);

# if defined(CHOWN_CHANGE_TIME_BUG) && CHOWN_CHANGE_TIME_BUG
  if ((result == 0) && stat_valid
      && ((uid == st.st_uid) || (uid == (uid_t)-1))
      && ((gid == st.st_gid) || (gid == (gid_t)-1))) {
      /* No change in ownership, but at least one argument was not -1, so we
	   * are required to update ctime. Since chown succeeded, we assume that
	   * chmod will do likewise.  Fortunately, on all known systems where
	   * a 'no-op' chown skips the ctime update, a 'no-op' chmod still does
	   * the trick: */
      result = chmod(file, (st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO
										  | S_ISUID | S_ISGID | S_ISVTX)));
  }
# endif /* CHOWN_CHANGE_TIME_BUG */

  return result;
}

#endif /* HAVE_CHOWN */

/* EOF */
