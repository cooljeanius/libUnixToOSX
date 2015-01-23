/* posix_fallocate64.c
   Copyright (C) 2000-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/stat.h>
#ifdef HAVE_SYS_STATFS_H
# include <sys/statfs.h>
#else
# ifdef HAVE_SYS_MOUNT_H
#  include <sys/mount.h>
# else
#  ifdef HAVE_SYS_STATVFS_H
#   include <sys/statvfs.h>
#  else
#   if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#    warning "posix_fallocate64.c expects <sys/statfs.h> to be included."
#   endif /* __GNUC__ && !__STRICT_ANSI__ */
#  endif /* HAVE_SYS_STATVFS_H */
# endif /* HAVE_SYS_MOUNT_H */
#endif /* HAVE_SYS_STATFS_H */

#ifndef _LIBC
/* strip off leading underscores when NOT building inside glibc: */
# if defined(HAVE_OFF64_T) || defined(off64_t) || defined(_OFF64_T)
#  define __off64_t off64_t
# else
#  if defined(HAVE_OFF_T) || defined(off_t) || defined(_OFF_T)
#   define __off64_t off_t
#  else
#   if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#    warning "missing a proper type for posix_fallocate64.c"
#   endif /* __GNUC__ && !__STRICT_ANSI__ */
#  endif /* HAVE_OFF_T || off_t || _OFF_T */
# endif /* HAVE_OFF64_T || off64_t || _OFF64_T */
# if defined(HAVE_FXSTAT64)
#  define __fxstat64 fxstat64
# else
#  if defined(HAVE_FSTAT64)
#   define __fxstat64(unused, fd, st64) fstat64(fd, st64)
#  endif /* HAVE_FSTAT64 */
# endif /* HAVE_FXSTAT64 */
# if defined(HAVE_FSTATFS64)
#  define __fstatfs64 fstatfs64
# else
#  if defined(HAVE_FSTATFS)
#   define __fstatfs64 fstatfs
#  endif /* HAVE_FSTATFS */
# endif /* HAVE_FSTATFS64 */
# if defined(HAVE_FTRUNCATE64)
#  define __ftruncate64 ftruncate64
# else
#  if defined(HAVE_FTRUNCATE)
#   define __ftruncate64 ftruncate
#  endif /* HAVE_FTRUNCATE */
# endif /* HAVE_FTRUNCATE64 */
# if defined(HAVE_PREAD64)
#  define __libc_pread64 pread64
# else
#  if defined(HAVE_PREAD)
#   define __libc_pread64 pread
#  endif /* HAVE_PREAD */
# endif /* HAVE_PREAD64 */
# if defined(HAVE_PWRITE64)
#  define __libc_pwrite64 pwrite64
# else
#  if defined(HAVE_PWRITE)
#   define __libc_pwrite64 pwrite
#  endif /* HAVE_PWRITE */
# endif /* HAVE_PWRITE64 */
#endif /* !_LIBC */

/* Reserve storage for the data of the file associated with FD.  */
int __posix_fallocate64_l64(int fd, __off64_t offset, __off64_t len)
{
  struct stat64 st;
  struct statfs64 f;

  /* `off64_t' is a signed type. Therefore we can determine whether
   * OFFSET + LEN is too large if it is a negative value. */
  if ((offset < 0L) || (len < 0L)) {
    return EINVAL;
  }
#if (defined(WRAPV) && WRAPV) && defined(EFBIG)
  if ((offset + len) < 0L) {
    return EFBIG;
  }
#endif /* WRAPV && EFBIG */

  /* First, we have to make sure this is really a regular file: */
  if (__fxstat64(_STAT_VER, fd, &st) != 0) {
    return EBADF;
  }
  if (S_ISFIFO(st.st_mode)) {
    return ESPIPE;
  }
  if (! S_ISREG(st.st_mode)) {
    return ENODEV;
  }

  if (len == 0) {
      if (st.st_size < offset) {
          int ret = __ftruncate64(fd, offset);

          if (ret != 0) {
              ret = errno;
          }
          return ret;
      }
      return 0;
  }

  /* We have to know the block size of the filesystem to get at least some
   * sort of performance: */
  if (__fstatfs64(fd, &f) != 0) {
    return errno;
  }

  /* Try to play safe: */
  if (f.f_bsize == 0) {
    f.f_bsize = 512;
  }

  /* Write something to every block.  */
  for ((offset += ((len - 1) % f.f_bsize)); (len > 0); (offset += f.f_bsize)) {
      len -= f.f_bsize;

      if (offset < st.st_size) {
          unsigned char c;
          ssize_t rsize = __libc_pread64(fd, &c, (size_t)1UL, offset);

          if (rsize < 0) {
              return errno;
          } else if ((rsize == 1) && (c != 0)) {
              /* If there is a non-zero byte, the block must have been
               * allocated already.  */
              continue;
          }
      }

      if (__libc_pwrite64(fd, "", (size_t)1UL, offset) != 1) {
          return errno;
      }
  }

  return 0;
}

#ifdef _LIBC
# undef __posix_fallocate64_l64
# include <shlib-compat.h>
# include <bits/wordsize.h>

# if (__WORDSIZE == 32) && SHLIB_COMPAT(libc, GLIBC_2_2, GLIBC_2_3_3)

int
attribute_compat_text_section
__posix_fallocate64_l32(int fd, off64_t offset, size_t len)
{
  return __posix_fallocate64_l64(fd, offset, len);
}

versioned_symbol(libc, __posix_fallocate64_l64, posix_fallocate64,
                 GLIBC_2_3_3);
compat_symbol(libc, __posix_fallocate64_l32, posix_fallocate64, GLIBC_2_2);
# else
strong_alias(__posix_fallocate64_l64, posix_fallocate64);
# endif /* other _LIBC junk */
/* (moved "else" case to our fcntl.h header) */
#endif /* _LIBC */

/* EOF */
