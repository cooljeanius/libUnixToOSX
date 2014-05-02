/* mountlist.c -- return a list of mounted file systems
 *
 * Copyright (C) 1991-1992, 1997-2012 Free Software Foundation, Inc.
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

#include "mntent.h"
#include "mountlist.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "xalloc.h"

#include <errno.h>

#include <fcntl.h>

#include <unistd.h>

#if HAVE_SYS_PARAM_H
# include <sys/param.h>
#endif /* HAVE_SYS_PARAM_H */

#if defined MOUNTED_GETFSSTAT   /* OSF_1 and Darwin1.3.x */
# if HAVE_SYS_UCRED_H
#  include <grp.h> /* needed on OSF V4.0 for definition of NGROUPS,
                    * NGROUPS is used as an array dimension in ucred.h */
#  include <sys/ucred.h> /* needed by powerpc-apple-darwin1.3.7 */
# endif /* HAVE_SYS_UCRED_H */
# if HAVE_SYS_MOUNT_H
#  include <sys/mount.h>
# endif /* HAVE_SYS_MOUNT_H */
# if HAVE_SYS_FS_TYPES_H
#  include <sys/fs_types.h> /* needed by powerpc-apple-darwin1.3.7 */
# endif /* HAVE_SYS_FS_TYPES_H */
# if HAVE_STRUCT_FSSTAT_F_FSTYPENAME
#  define FS_TYPE(Ent) ((Ent).f_fstypename)
# else
#  define FS_TYPE(Ent) mnt_names[(Ent).f_type]
# endif /* HAVE_STRUCT_FSSTAT_F_FSTYPENAME */
#endif /* MOUNTED_GETFSSTAT */

/* TODO: while the default for darwin may be the above, I am trying to implement
 * getmntent() and friends here, so see if we can use the versions of those
 * functions that get built here in this library, as opposed to the pre-existing
 * ones that get picked up at configure time
 * (which is where most of the defines come from) */

#ifndef MOUNTED_GETMNTENT1
# if ((defined(HAVE_MNTENT_H) || defined(_MNTENT_H_)) && defined(MOUNTED) \
      && defined(HAVE_SETMNTENT) && defined(HAVE_GETMNTENT) && defined(HAVE_ENDMNTENT)) || 0
#  define MOUNTED_GETMNTENT1 1
# endif /* ((HAVE_MNTENT_H || _MNTENT_H_) && MOUNTED && HAVE_SETMNTENT && HAVE_GETMNTENT && HAVE_ENDMNTENT) || 0 */
#endif /* !MOUNTED_GETMNTENT1 */
#ifdef MOUNTED_GETMNTENT1       /* 4.3BSD, SunOS, HP-UX, Dynix, Irix.  */
# if defined(HAVE_MNTENT_H)
#  include <mntent.h>
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__) && !defined(_MNTENT_H_)
#   warning "mountlist.c expects <mntent.h> to be included when MOUNTED_GETMNTENT1 is defined"
#  endif /* __GNUC__ && !__STRICT_ANSI__ && !_MNTENT_H_ */
# endif /* HAVE_MNTENT_H */
# if !defined MOUNTED
#  if defined _PATH_MOUNTED     /* GNU libc */
#   define MOUNTED _PATH_MOUNTED
#  endif /* _PATH_MOUNTED */
#  if defined MNT_MNTTAB        /* HP-UX. */
#   define MOUNTED MNT_MNTTAB
#  endif /* MNT_MNTTAB */
#  if defined MNTTABNAME        /* Dynix. */
#   define MOUNTED MNTTABNAME
#  endif /* MNTTABNAME */
# endif /* !MOUNTED */
#endif /* MOUNTED_GETMNTENT1 */

#ifndef MOUNTED_GETMNTINFO
# if (defined(__APPLE__) && defined(__MACH__)) || (defined(HAVE_SYS_MOUNT_H) && defined(HAVE_GETMNTINFO))
#  define MOUNTED_GETMNTINFO 1
# endif /* (__APPLE__ && __MACH__) || (HAVE_SYS_MOUNT_H && HAVE_GETMNTINFO) */
#endif /* !MOUNTED_GETMNTINFO */
#ifdef MOUNTED_GETMNTINFO       /* 4.4BSD (and darwin).  */
# include <sys/mount.h>
#endif /* MOUNTED_GETMNTINFO */

#ifndef MOUNTED_GETMNTINFO2
# if (defined(HAVE_SYS_STATVFS_H) && defined(MNT_NOWAIT) && defined(HAVE_GETMNTINFO) \
      && (defined(_DEV_T) || defined(HAVE_DEV_T))) || 0
#  define MOUNTED_GETMNTINFO2 2
# endif /* (HAVE_SYS_STATVFS_H && MNT_NOWAIT && HAVE_GETMNTINFO && (_DEV_T || HAVE_DEV_T)) || 0 */
#endif /* !MOUNTED_GETMNTINFO2 */
#ifdef MOUNTED_GETMNTINFO2      /* NetBSD 3.0 (and darwin). */
# include <sys/statvfs.h>
#endif /* MOUNTED_GETMNTINFO2 */

#ifndef MOUNTED_GETMNT
# if (defined(HAVE_SYS_FS_TYPES_H) && defined(HAVE_GETMNT) && defined(NOSTAT_MANY)) || 0
#  define MOUNTED_GETMNT 1
# endif /* (HAVE_SYS_FS_TYPES_H && HAVE_GETMNT && NOSTAT_MANY) || 0 */
#endif /* !MOUNTED_GETMNT */
#ifdef MOUNTED_GETMNT           /* Ultrix. */
# include <sys/mount.h>
# if defined(HAVE_SYS_FS_TYPES_H)
#  include <sys/fs_types.h>
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   warning "mountlist.c expects <sys/fs_types.h> to be included when MOUNTED_GETMNT is defined"
#  endif /* __GNUC__ && !__STRICT_ANSI__ */
# endif /* HAVE_SYS_FS_TYPES_H */
#endif /* MOUNTED_GETMNT */

/* TODO: thouroughly test all possibilities/conditions/ifdefs */
#ifdef MOUNTED_FS_STAT_DEV      /* BeOS.  */
# include <fs_info.h>
# include <dirent.h>
#endif /* MOUNTED_FS_STAT_DEV */

#ifdef MOUNTED_FREAD            /* SVR2.  */
# include <mnttab.h>
#endif /* MOUNTED_FREAD */

#ifdef MOUNTED_FREAD_FSTYP      /* SVR3.  */
# include <mnttab.h>
# include <sys/fstyp.h>
# include <sys/statfs.h>
#endif /* MOUNTED_FREAD_FSTYP */

#ifndef MOUNTED_LISTMNTENT
# if ((defined(HAVE_MNTENT_H) || defined(_MNTENT_H_)) && defined(HAVE_LISTMNTENT) \
      && defined(KMTAB) && defined(HAVE_FREEMNTLIST)) || 0
#  define MOUNTED_LISTMNTENT 1
# endif /* ((HAVE_MNTENT_H || _MNTENT_H_) && HAVE_LISTMNTENT && KMTAB && HAVE_FREEMNTLIST) || 0 */
#endif /* !MOUNTED_LISTMNTENT */
#ifdef MOUNTED_LISTMNTENT
# if defined(HAVE_MNTENT_H)
#  include <mntent.h>
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__) && !defined(_MNTENT_H_)
#   warning "mountlist.c expects <mntent.h> to be included when MOUNTED_LISTMNTENT is defined"
#  endif /* __GNUC__ && !__STRICT_ANSI__ && !_MNTENT_H_ */
# endif /* HAVE_MNTENT_H */
#endif /* MOUNTED_LISTMNTENT */

#ifndef MOUNTED_GETMNTENT2
# if (defined(HAVE_SYS_MNTTAB_H) && defined(MNTTAB) && defined(HAVE_GETMNTENT)) || 0
#  define MOUNTED_GETMNTENT2 2
# endif /* (HAVE_SYS_MNTTAB_H && MNTTAB && HAVE_GETMNTENT) || 0 */
#endif /* !MOUNTED_GETMNTENT2 */
#ifdef MOUNTED_GETMNTENT2       /* SVR4.  */
# if defined(HAVE_SYS_MNTTAB_H)
#  include <sys/mnttab.h>
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   warning "mountlist.c expects <sys/mnttab.h> to be included when MOUNTED_GETMNTENT2 is defined"
#  endif /* __GNUC__ && !__STRICT_ANSI__ */
# endif /* HAVE_SYS_MNTTAB_H */
#endif /* MOUNTED_GETMNTENT2 */

#ifndef MOUNTED_VMOUNT
# if (defined(HAVE_FSHELP_H) && defined(HAVE_SYS_VFS_H) && defined(HAVE_GETVFSBYTYPE) \
      && defined(HAVE_MNTCTL) && defined(MCTL_QUERY) && defined(MNT_REMOTE) \
	  && defined(VMT_HOSTNAME) && defined(VMT_OBJECT) && defined(VMT_STUB) && defined(VMT_ARGS)) || 0
#  define MOUNTED_VMOUNT 1
# endif /* (HAVE_FSHELP_H && HAVE_SYS_VFS_H && HAVE_GETVFSBYTYPE && HAVE_MNTCTL \
         *  && MCTL_QUERY && MNT_REMOTE && VMT_HOSTNAME && VMT_OBJECT && VMT_STUB && VMT_ARGS) || 0 */
#endif /* !MOUNTED_VMOUNT */
#ifdef MOUNTED_VMOUNT           /* AIX.  */
# if defined(HAVE_FSHELP_H)
#  include <fshelp.h>
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   warning "mountlist.c expects <fshelp.h> to be included when MOUNTED_VMOUNT is defined"
#  endif /* __GNUC__ && !__STRICT_ANSI__ */
# endif /* HAVE_FSHELP_H */
# if defined(HAVE_SYS_VFS_H)
#  include <sys/vfs.h>
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   warning "mountlist.c expects <sys/vfs.h> to be included when MOUNTED_VMOUNT is defined"
#  endif /* __GNUC__ && !__STRICT_ANSI__ */
# endif /* HAVE_SYS_VFS_H */
#endif /* MOUNTED_VMOUNT */

#ifdef MOUNTED_INTERIX_STATVFS  /* Interix. */
# include <sys/statvfs.h>
# include <dirent.h>
#endif /* MOUNTED_INTERIX_STATVFS */

#ifdef DOLPHIN
/* So special that it is not worth putting this in autoconf. */
# undef MOUNTED_FREAD_FSTYP
# define MOUNTED_GETMNTTBL 1
#endif /* DOLPHIN */

#if HAVE_SYS_MNTENT_H
/* This is to get MNTOPT_IGNORE on e.g. SVR4. */
# include <sys/mntent.h>
#endif /* HAVE_SYS_MNTENT_H */

#undef MNT_IGNORE
#if defined MNTOPT_IGNORE && defined HAVE_HASMNTOPT
# define MNT_IGNORE(M) hasmntopt(M, MNTOPT_IGNORE)
#else
# define MNT_IGNORE(M) 0
#endif /* MNTOPT_IGNORE && HAVE_HASMNTOPT */

#if USE_UNLOCKED_IO
# include "unlocked-io.h"
#endif /* USE_UNLOCKED_IO */

/* The results of open() in this file are not used with fchdir,
 * therefore save some unnecessary work in fchdir.c. */
#undef open
#undef close

/* The results of opendir() in this file are not used with dirfd and fchdir,
 * therefore save some unnecessary work in fchdir.c. */
#undef opendir
#undef closedir

#ifndef ME_DUMMY
# define ME_DUMMY(Fs_name, Fs_type)             \
    (strcmp (Fs_type, "autofs") == 0            \
     || strcmp (Fs_type, "none") == 0           \
     || strcmp (Fs_type, "proc") == 0           \
     || strcmp (Fs_type, "subfs") == 0          \
     /* for NetBSD 3.0 */                       \
     || strcmp (Fs_type, "kernfs") == 0         \
     /* for Irix 6.5 */                         \
     || strcmp (Fs_type, "ignore") == 0)
#endif /* !ME_DUMMY */

#if defined(__CYGWIN__) || defined(HAVE_WINDOWS_H)
# include <windows.h>
#endif /* __CYGWIN__ || HAVE_WINDOWS_H */
#ifdef __CYGWIN__
# if !(defined(DRIVE_REMOVABLE) || defined(DRIVE_FIXED) || defined(DRIVE_CDROM) || defined(DRIVE_RAMDISK))
#  if defined(HAVE_WINBASE_H)
#   include <winbase.h>
#  else
/* next 4 values taken from the Wine <winbase.h> header: */
#   ifndef DRIVE_REMOVABLE
#    define DRIVE_REMOVABLE 2
#   endif /* !DRIVE_REMOVABLE */
#   ifndef DRIVE_FIXED
#    define DRIVE_FIXED 3
#   endif /* !DRIVE_FIXED */
/* Win32 additions: */
#   ifndef DRIVE_CDROM
#    define DRIVE_CDROM 5
#   endif /* !DRIVE_CDROM */
#   ifndef DRIVE_RAMDISK
#    define DRIVE_RAMDISK 6
#   endif /* !DRIVE_RAMDISK */
#  endif /* HAVE_WINBASE_H */
# endif /* !(DRIVE_REMOVABLE || DRIVE_FIXED || DRIVE_CDROM || DRIVE_RAMDISK) */
# define ME_REMOTE me_remote
/* All cygwin mount points include ':' or start with '//'; so it
 * requires a native Windows call to determine remote disks.  */
static bool
me_remote(char const *fs_name, char const *fs_type _GL_UNUSED)
{
  if (fs_name[0] && (fs_name[1] == ':')) {
      char drive[4];
      sprintf(drive, "%c:\\", fs_name[0]);
# if !defined(GetDriveType) && defined(WINELIB_NAME_AW)
#  define GetDriveType WINELIB_NAME_AW(GetDriveType)
# endif /* !GetDriveType && WINELIB_NAME_AW */
      switch (GetDriveType(drive)) {
# ifdef DRIVE_REMOVABLE
		  case DRIVE_REMOVABLE:
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   if defined(__WINE_WINBASE_H)
#    warning "DRIVE_REMOVABLE should have been defined in <winbase.h>"
#   else
#    warning "<winbase.h> should have been included for DRIVE_REMOVABLE."
#   endif /* __WINE_WINBASE_H */
#  endif /* __GNUC__ && !__STRICT_ANSI__ */
# endif /* DRIVE_REMOVABLE */
# ifdef DRIVE_FIXED
		  case DRIVE_FIXED:
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   if defined(__WINE_WINBASE_H)
#    warning "DRIVE_FIXED should have been defined in <winbase.h>"
#   else
#    warning "<winbase.h> should have been included for DRIVE_FIXED."
#   endif /* __WINE_WINBASE_H */
#  endif /* __GNUC__ && !__STRICT_ANSI__ */
# endif /* DRIVE_FIXED */
# ifdef DRIVE_CDROM
		  case DRIVE_CDROM:
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   if defined(__WINE_WINBASE_H)
#    warning "DRIVE_CDROM should have been defined in <winbase.h>"
#   else
#    warning "<winbase.h> should have been included for DRIVE_CDROM."
#   endif /* __WINE_WINBASE_H */
#  endif /* __GNUC__ && !__STRICT_ANSI__ */
# endif /* DRIVE_CDROM */
# ifdef DRIVE_RAMDISK
		  case DRIVE_RAMDISK:
			  return false;
# else
#  if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#   if defined(__WINE_WINBASE_H)
#    warning "DRIVE_RAMDISK should have been defined in <winbase.h>"
#   else
#    warning "<winbase.h> should have been included for DRIVE_RAMDISK."
#   endif /* __WINE_WINBASE_H */
#  endif /* __GNUC__ && !__STRICT_ANSI__ */
# endif /* DRIVE_RAMDISK */
		  default:
			  /* do nothing */ ;
	  }
  }
  return true;
}
#endif /* __CYGWIN__ */

#ifndef ME_REMOTE
/* A file system is "remote" if its Fs_name contains a ':'
 * or if (it is of type (smbfs or cifs) and its Fs_name starts with '//'). */
# define ME_REMOTE(Fs_name, Fs_type)            \
    ((strchr(Fs_name, ':') != NULL)             \
     || (((Fs_name)[0] == '/')                  \
         && ((Fs_name)[1] == '/')               \
         && ((strcmp(Fs_type, "smbfs") == 0)    \
             || (strcmp(Fs_type, "cifs") == 0))))
#endif /* !ME_REMOTE */

#if MOUNTED_GETMNTINFO

# if ! HAVE_STRUCT_STATFS_F_FSTYPENAME
static char *
fstype_to_string(short int t)
{
  switch (t) {
#  ifdef MOUNT_PC
    case MOUNT_PC:
      return "pc";
#  endif /* MOUNT_PC */
#  ifdef MOUNT_MFS
    case MOUNT_MFS:
      return "mfs";
#  endif /* MOUNT_MFS */
#  ifdef MOUNT_LO
    case MOUNT_LO:
      return "lo";
#  endif /* MOUNT_LO */
#  ifdef MOUNT_TFS
    case MOUNT_TFS:
      return "tfs";
#  endif /* MOUNT_TFS */
#  ifdef MOUNT_TMP
    case MOUNT_TMP:
      return "tmp";
#  endif /* MOUNT_TMP */
#  ifdef MOUNT_UFS
   case MOUNT_UFS:
     return "ufs";
#  endif /* MOUNT_UFS */
#  ifdef MOUNT_NFS
   case MOUNT_NFS:
     return "nfs";
#  endif /* MOUNT_NFS */
#  ifdef MOUNT_MSDOS
   case MOUNT_MSDOS:
     return "msdos";
#  endif /* MOUNT_MSDOS */
#  ifdef MOUNT_LFS
   case MOUNT_LFS:
     return "lfs" ;
#  endif /* MOUNT_LFS */
#  ifdef MOUNT_LOFS
   case MOUNT_LOFS:
     return "lofs";
#  endif /* MOUNT_LOFS */
#  ifdef MOUNT_FDESC
   case MOUNT_FDESC:
     return "fdesc";
#  endif /* MOUNT_FDESC */
#  ifdef MOUNT_PORTAL
   case MOUNT_PORTAL:
     return "portal";
#  endif /* MOUNT_PORTAL */
#  ifdef MOUNT_NULL
   case MOUNT_NULL:
     return "null";
#  endif /* MOUNT_NULL */
#  ifdef MOUNT_UMAP
   case MOUNT_UMAP:
     return "umap";
#  endif /* MOUNT_UMAP */
#  ifdef MOUNT_KERNFS
   case MOUNT_KERNFS:
     return "kernfs";
#  endif /* MOUNT_KERNFS */
#  ifdef MOUNT_PROCFS
   case MOUNT_PROCFS:
     return "procfs";
#  endif /* MOUNT_PROCFS */
#  ifdef MOUNT_AFS
   case MOUNT_AFS:
     return "afs";
#  endif /* MOUNT_AFS */
#  ifdef MOUNT_CD9660
   case MOUNT_CD9660:
     return "cd9660";
#  endif /* MOUNT_CD9660 */
#  ifdef MOUNT_UNION
   case MOUNT_UNION:
     return "union";
#  endif /* MOUNT_UNION */
#  ifdef MOUNT_DEVFS
   case MOUNT_DEVFS:
     return "devfs";
#  endif /* MOUNT_DEVFS */
#  ifdef MOUNT_EXT2FS
   case MOUNT_EXT2FS:
     return "ext2fs";
#  endif /* MOUNT_EXT2FS */
    default:
      return "?";
  }
}
# endif /* !HAVE_STRUCT_STATFS_F_FSTYPENAME */

static char *
fsp_to_string(const struct statfs *fsp)
{
# if HAVE_STRUCT_STATFS_F_FSTYPENAME
  return (char *)(fsp->f_fstypename);
# else
  return fstype_to_string(fsp->f_type);
# endif /* HAVE_STRUCT_STATFS_F_FSTYPENAME */
}

#endif /* MOUNTED_GETMNTINFO */

#ifdef MOUNTED_VMOUNT           /* AIX.  */
static char *
fstype_to_string(int t)
{
  struct vfs_ent *e;

  e = (struct vfs_ent *)getvfsbytype(t);
  if (!e || !e->vfsent_name) {
	  return (char *)"none";
  } else {
	  return e->vfsent_name;
  }
}
#endif /* MOUNTED_VMOUNT */


#if defined MOUNTED_GETMNTENT1 || defined MOUNTED_GETMNTENT2
/* Return the device number from MOUNT_OPTIONS, if possible.
 * Otherwise return (dev_t) -1.  */
static dev_t
dev_from_mount_options(char const *mount_options)
{
  /* GNU/Linux allows file system implementations to define their own
   * meaning for "dev=" mount options, so do NOT trust the meaning
   * here.  */
# ifndef __linux__
  static char const dev_pattern[] = ",dev=";
  char const *devopt = strstr(mount_options, dev_pattern);

  if (devopt) {
      char const *optval = (devopt + sizeof(dev_pattern) - 1);
      char *optvalend;
      unsigned long int dev;
      errno = 0;
      dev = strtoul(optval, &optvalend, 16);
	  /* the comparison between different signs here is intentional: */
#  if defined(__GNUC__) && defined(__GNUC_MINOR__)
#   if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 2))
#    pragma GCC diagnostic ignored "-Wsign-compare"
#   endif /* GCC 4.2+ */
#  endif /* any gcc */
      if ((optval != optvalend)
          && ((*optvalend == '\0') || (*optvalend == ','))
          && !((dev == ULONG_MAX) && (errno == ERANGE))
          && ((unsigned long int)dev == (dev_t)dev)) {
		  return (dev_t)dev;
	  }
  }

# endif /* !__linux__ */
  (void)mount_options;
  return -1;
}
#endif /* MOUNTED_GETMNTENT[1|2] */


/* Return a list of the currently mounted file systems, or NULL on error.
 * Add each entry to the tail of the list so that they stay in order.
 * If NEED_FS_TYPE is true, ensure that the file system type fields in
 * the returned list are valid.  Otherwise, they might not be.  */
struct mount_entry *
read_file_system_list(bool need_fs_type)
{
  struct mount_entry *mount_list;
  struct mount_entry *me;
  struct mount_entry **mtail = &mount_list;
  (void)need_fs_type;

#ifdef MOUNTED_LISTMNTENT
  {
    struct tabmntent *mntlist, *p;
    struct mntent *mnt;
    struct mount_entry *me; /* what about the previous 'me' variable? */

    /* the third and fourth arguments could be used to filter mounts,
     * but Crays does NOT seem to have any mounts that we want to
     * remove. Specifically, automount create normal NFS mounts.
     * */

	if (listmntent(&mntlist, KMTAB, NULL, NULL) < 0) {
		return NULL;
	}
    for ((p = mntlist); p; (p = p->next)) {
        mnt = p->ment;
        me = xmalloc(sizeof(*me));
        me->me_devname = xstrdup(mnt->mnt_fsname);
        me->me_mountdir = xstrdup(mnt->mnt_dir);
        me->me_type = xstrdup(mnt->mnt_type);
        me->me_type_malloced = 1;
        me->me_dummy = ME_DUMMY(me->me_devname, me->me_type);
        me->me_remote = ME_REMOTE(me->me_devname, me->me_type);
        me->me_dev = -1;
        *mtail = me;
        mtail = &me->me_next;
	}
    freemntlist(mntlist);
  }
#endif /* MOUNTED_LISTMNTENT */

#ifdef MOUNTED_GETMNTENT1 /* GNU/Linux, 4.3BSD, SunOS, HP-UX, Dynix, Irix.  */
  {
    struct mntent *mnt;
	char const *table;
    FILE *fp;

	table = (char const *)MOUNTED;
    fp = (FILE *)setmntent(table, "r");
	if (fp == NULL) {
		return NULL;
	}

    while ((mnt = (struct mntent *)getmntent(fp))) {
        me = xmalloc(sizeof(*me));
        me->me_devname = xstrdup(mnt->mnt_fsname);
        me->me_mountdir = xstrdup(mnt->mnt_dir);
        me->me_type = xstrdup(mnt->mnt_type);
        me->me_type_malloced = 1;
        me->me_dummy = ME_DUMMY(me->me_devname, me->me_type);
        me->me_remote = ME_REMOTE(me->me_devname, me->me_type);
        me->me_dev = dev_from_mount_options(mnt->mnt_opts);

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
	}

	if (endmntent(fp) == 0) {
		goto free_then_fail;
	}
  }
#endif /* MOUNTED_GETMNTENT1. */

#ifdef MOUNTED_GETMNTINFO       /* 4.4BSD (and darwin).  */
  {
    struct statfs *fsp;
    int entries;

    entries = getmntinfo(&fsp, MNT_NOWAIT);
	if (entries < 0) {
		return NULL;
	}
    for (; (entries-- > 0); fsp++) {
        char *fs_type = fsp_to_string(fsp);

        me = xmalloc(sizeof(*me));
        me->me_devname = xstrdup(fsp->f_mntfromname);
        me->me_mountdir = xstrdup(fsp->f_mntonname);
        me->me_type = fs_type;
        me->me_type_malloced = 0;
        me->me_dummy = ME_DUMMY(me->me_devname, me->me_type);
        me->me_remote = ME_REMOTE(me->me_devname, me->me_type);
        me->me_dev = (dev_t)-1;        /* Magic; means not known yet. */

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
      }
  }
#endif /* MOUNTED_GETMNTINFO */

#ifdef MOUNTED_GETMNTINFO2      /* NetBSD 3.0.  */
  {
# if defined(__DARWIN_STRUCT_STATFS64)
	/* the darwin version of 'struct statvfs' is missing some fields, so just
	 * use 'struct statfs' as a replacement: */
	struct statfs *fsp;
# else
    struct statvfs *fsp;
# endif /* __DARWIN_STRUCT_STATFS64 */
    int entries;

    entries = getmntinfo(&fsp, MNT_NOWAIT);
	if (entries < 0) {
		return NULL;
	}
    for (; (entries-- > 0); fsp++) {
        me = xmalloc(sizeof(*me));
        me->me_devname = xstrdup(fsp->f_mntfromname);
        me->me_mountdir = xstrdup(fsp->f_mntonname);
        me->me_type = xstrdup(fsp->f_fstypename);
        me->me_type_malloced = 1;
        me->me_dummy = ME_DUMMY(me->me_devname, me->me_type);
        me->me_remote = ME_REMOTE(me->me_devname, me->me_type);
        me->me_dev = (dev_t)-1;        /* Magic; means not known yet. */

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
	}
  }
#endif /* MOUNTED_GETMNTINFO2 */

#ifdef MOUNTED_GETMNT           /* Ultrix.  */
  {
    int offset = 0;
    int val;
    struct fs_data fsd;

    while ((errno = 0),
           (0 < (val = getmnt(&offset, &fsd, sizeof(fsd), NOSTAT_MANY,
							  (char *)0)))) {
        me = xmalloc(sizeof(*me));
        me->me_devname = xstrdup(fsd.fd_req.devname);
        me->me_mountdir = xstrdup(fsd.fd_req.path);
        me->me_type = gt_names[fsd.fd_req.fstype];
        me->me_type_malloced = 0;
        me->me_dummy = ME_DUMMY(me->me_devname, me->me_type);
        me->me_remote = ME_REMOTE(me->me_devname, me->me_type);
        me->me_dev = fsd.fd_req.dev;

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
	}
	if (val < 0) {
		goto free_then_fail;
	}
  }
#endif /* MOUNTED_GETMNT. */

#if defined MOUNTED_FS_STAT_DEV /* BeOS */
  {
    /* The next_dev() and fs_stat_dev() system calls give the list of
     * all file systems, including the information returned by statvfs()
     * (fs type, total blocks, free blocks etc.), but without the mount
     * point. But on BeOS all file systems except / are mounted in the
     * rootfs, directly under /.
     * The directory name of the mount point is often, but not always,
     * identical to the volume name of the device.
     * We therefore get the list of subdirectories of /, and the list
     * of all file systems, and match the two lists.  */

    DIR *dirp;
    struct rootdir_entry
      {
        char *name;
        dev_t dev;
        ino_t ino;
        struct rootdir_entry *next;
      };
    struct rootdir_entry *rootdir_list;
    struct rootdir_entry **rootdir_tail;
    int32 pos;
    dev_t dev;
    fs_info fi;

    /* All volumes are mounted in the rootfs, directly under /. */
    rootdir_list = NULL;
    rootdir_tail = &rootdir_list;
    dirp = opendir ("/");
    if (dirp)
      {
        struct dirent *d;

        while ((d = readdir (dirp)) != NULL)
          {
            char *name;
            struct stat statbuf;

            if (strcmp (d->d_name, "..") == 0)
              continue;

            if (strcmp (d->d_name, ".") == 0)
              name = xstrdup ("/");
            else
              {
                name = xmalloc (1 + strlen (d->d_name) + 1);
                name[0] = '/';
                strcpy (name + 1, d->d_name);
              }

            if (lstat (name, &statbuf) >= 0 && S_ISDIR (statbuf.st_mode))
              {
                struct rootdir_entry *re = xmalloc (sizeof(*re));
                re->name = name;
                re->dev = statbuf.st_dev;
                re->ino = statbuf.st_ino;

                /* Add to the linked list.  */
                *rootdir_tail = re;
                rootdir_tail = &re->next;
              }
            else
              free (name);
          }
        closedir (dirp);
      }
    *rootdir_tail = NULL;

    for (pos = 0; (dev = next_dev (&pos)) >= 0; )
      if (fs_stat_dev (dev, &fi) >= 0)
        {
          /* Note: fi.dev == dev. */
          struct rootdir_entry *re;

          for (re = rootdir_list; re; re = re->next)
            if (re->dev == fi.dev && re->ino == fi.root)
              break;

          me = xmalloc (sizeof(*me));
          me->me_devname = xstrdup (fi.device_name[0] != '\0'
                                    ? fi.device_name : fi.fsh_name);
          me->me_mountdir = xstrdup (re != NULL ? re->name : fi.fsh_name);
          me->me_type = xstrdup (fi.fsh_name);
          me->me_type_malloced = 1;
          me->me_dev = fi.dev;
          me->me_dummy = 0;
          me->me_remote = (fi.flags & B_FS_IS_SHARED) != 0;

          /* Add to the linked list. */
          *mtail = me;
          mtail = &me->me_next;
        }
    *mtail = NULL;

    while (rootdir_list != NULL)
      {
        struct rootdir_entry *re = rootdir_list;
        rootdir_list = re->next;
        free (re->name);
        free (re);
      }
  }
#endif /* MOUNTED_FS_STAT_DEV */

#if defined MOUNTED_GETFSSTAT   /* __alpha running OSF_1 */
  {
    int numsys, counter;
    size_t bufsize;
    struct statfs *stats;

    numsys = getfsstat (NULL, 0L, MNT_NOWAIT);
    if (numsys < 0)
      return NULL;
    if (SIZE_MAX / sizeof(*stats) <= numsys)
      xalloc_die ();

    bufsize = (1 + numsys) * sizeof(*stats);
    stats = xmalloc (bufsize);
    numsys = getfsstat (stats, bufsize, MNT_NOWAIT);

    if (numsys < 0)
      {
        free (stats);
        return NULL;
      }

    for (counter = 0; counter < numsys; counter++)
      {
        me = xmalloc (sizeof(*me));
        me->me_devname = xstrdup (stats[counter].f_mntfromname);
        me->me_mountdir = xstrdup (stats[counter].f_mntonname);
        me->me_type = xstrdup (FS_TYPE (stats[counter]));
        me->me_type_malloced = 1;
        me->me_dummy = ME_DUMMY (me->me_devname, me->me_type);
        me->me_remote = ME_REMOTE (me->me_devname, me->me_type);
        me->me_dev = (dev_t) -1;        /* Magic; means not known yet. */

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
      }

    free (stats);
  }
#endif /* MOUNTED_GETFSSTAT */

#if defined MOUNTED_FREAD || defined MOUNTED_FREAD_FSTYP /* SVR[23].  */
  {
    struct mnttab mnt;
    char *table = "/etc/mnttab";
    FILE *fp;

    fp = fopen (table, "r");
    if (fp == NULL)
      return NULL;

    while (fread (&mnt, sizeof(mnt), 1, fp) > 0)
      {
        me = xmalloc (sizeof(*me));
# ifdef GETFSTYP                        /* SVR3.  */
        me->me_devname = xstrdup (mnt.mt_dev);
# else
        me->me_devname = xmalloc (strlen (mnt.mt_dev) + 6);
        strcpy (me->me_devname, "/dev/");
        strcpy (me->me_devname + 5, mnt.mt_dev);
# endif
        me->me_mountdir = xstrdup (mnt.mt_filsys);
        me->me_dev = (dev_t) -1;        /* Magic; means not known yet. */
        me->me_type = "";
        me->me_type_malloced = 0;
# ifdef GETFSTYP                        /* SVR3.  */
        if (need_fs_type)
          {
            struct statfs fsd;
            char typebuf[FSTYPSZ];

            if (statfs (me->me_mountdir, &fsd, sizeof(fsd), 0) != -1
                && sysfs (GETFSTYP, fsd.f_fstyp, typebuf) != -1)
              {
                me->me_type = xstrdup (typebuf);
                me->me_type_malloced = 1;
              }
          }
# endif
        me->me_dummy = ME_DUMMY (me->me_devname, me->me_type);
        me->me_remote = ME_REMOTE (me->me_devname, me->me_type);

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
      }

    if (ferror (fp))
      {
        /* The last fread() call must have failed.  */
        int saved_errno = errno;
        fclose (fp);
        errno = saved_errno;
        goto free_then_fail;
      }

    if (fclose (fp) == EOF)
      goto free_then_fail;
  }
#endif /* MOUNTED_FREAD || MOUNTED_FREAD_FSTYP.  */

#ifdef MOUNTED_GETMNTTBL        /* DolphinOS goes its own way.  */
  {
    struct mntent **mnttbl = getmnttbl (), **ent;
    for (ent = mnttbl; *ent; ent++)
      {
        me = xmalloc (sizeof(*me));
        me->me_devname = xstrdup ((*ent)->mt_resource);
        me->me_mountdir = xstrdup ((*ent)->mt_directory);
        me->me_type = xstrdup ((*ent)->mt_fstype);
        me->me_type_malloced = 1;
        me->me_dummy = ME_DUMMY (me->me_devname, me->me_type);
        me->me_remote = ME_REMOTE (me->me_devname, me->me_type);
        me->me_dev = (dev_t) -1;        /* Magic; means not known yet. */

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
      }
    endmnttbl();
  }
#endif /* MOUNTED_GETMNTTBL */

#ifdef MOUNTED_GETMNTENT2       /* SVR4.  */
  {
    struct mnttab mnt;
    char *table = MNTTAB;
    FILE *fp;
    int ret;
    int lockfd = -1;

# ifndef F_RDLCK
#  define F_RDLCK 1 /* value taken from the darwin <sys/fcntl.h> header */
# endif /* !F_RDLCK */
# ifndef F_SETLKW
#  define F_SETLKW 9 /* value taken from the darwin <sys/fcntl.h> header */
# endif /* !F_SETLKW */
# if defined F_RDLCK && defined F_SETLKW
    /* MNTTAB_LOCK is a macro name of our own invention; it is not present in
     * e.g. Solaris 2.6.  If the SVR4 folks ever define a macro
     * for this file name, we should use their macro name instead.
     * (Why not just lock MNTTAB directly? We do NOT know.)  */
#  ifndef MNTTAB_LOCK
#   define MNTTAB_LOCK "/etc/.mnttab.lock"
#  endif /* !MNTTAB_LOCK */
    lockfd = open(MNTTAB_LOCK, O_RDONLY);
    if (0 <= lockfd) {
        struct flock flock;
        flock.l_type = F_RDLCK;
        flock.l_whence = SEEK_SET;
        flock.l_start = 0;
        flock.l_len = 0;
        while (fcntl(lockfd, F_SETLKW, &flock) == -1) {
          if (errno != EINTR) {
              int saved_errno = errno;
              close(lockfd);
              errno = saved_errno;
              return NULL;
		  }
		}
	} else if (errno != ENOENT) {
		return NULL;
	}
# endif /* F_RDLCK && F_SETLKW */

    errno = 0;
    fp = fopen(table, "r");
	if (fp == NULL) {
		ret = errno;
    } else {
        while ((ret = getmntent(fp, &mnt)) == 0) {
            me = xmalloc(sizeof(*me));
            me->me_devname = xstrdup(mnt.mnt_special);
            me->me_mountdir = xstrdup(mnt.mnt_mountp);
            me->me_type = xstrdup(mnt.mnt_fstype);
            me->me_type_malloced = 1;
            me->me_dummy = MNT_IGNORE(&mnt) != 0;
            me->me_remote = ME_REMOTE(me->me_devname, me->me_type);
            me->me_dev = dev_from_mount_options(mnt.mnt_mntopts);

            /* Add to the linked list. */
            *mtail = me;
            mtail = &me->me_next;
		}

        ret = ((fclose(fp) == EOF) ? errno : ((0 < ret) ? 0 : -1));
	}

	if ((0 <= lockfd) && (close(lockfd) != 0)) {
		ret = errno;
	}

    if (0 <= ret) {
        errno = ret;
        goto free_then_fail;
	}
  }
#else
/* MNT_IGNORE is only used in the other half of this condition, so check it and
 * then undefine it in this half to try to silence a warning from the
 * '-Wunused-macros' flag: */
# ifdef MNT_IGNORE
#  undef MNT_IGNORE
# endif /* MNT_IGNORE */
#endif /* MOUNTED_GETMNTENT2.  */

#ifdef MOUNTED_VMOUNT           /* AIX.  */
  {
    int bufsize;
    char *entries, *thisent;
    struct vmount *vmp;
    int n_entries;
    int i;

    /* Ask how many bytes to allocate for the mounted file system info.  */
	if (mntctl(MCTL_QUERY, sizeof(bufsize), (struct vmount *)&bufsize) != 0) {
		return NULL;
	}
    entries = xmalloc((size_t)bufsize);

    /* Get the list of mounted file systems.  */
    n_entries = mntctl(MCTL_QUERY, bufsize, (struct vmount *)entries);
    if (n_entries < 0) {
        int saved_errno = errno;
        free (entries);
        errno = saved_errno;
        return NULL;
	}

    for ((i = 0), (thisent = entries);
         (i < n_entries);
         i++, (thisent += vmp->vmt_length)) {
        char *options, *ignore;

        vmp = (struct vmount *)thisent;
        me = xmalloc(sizeof(*me));
        if (vmp->vmt_flags & MNT_REMOTE) {
            char *host, *dir;

            me->me_remote = 1;
            /* Prepend the remote dirname.  */
            host = (thisent + vmp->vmt_data[VMT_HOSTNAME].vmt_off);
            dir = (thisent + vmp->vmt_data[VMT_OBJECT].vmt_of)f;
            me->me_devname = xmalloc(strlen(host) + strlen(dir) + 2);
            strcpy(me->me_devname, host);
            strcat(me->me_devname, ":");
            strcat(me->me_devname, dir);
		} else {
            me->me_remote = 0;
            me->me_devname = xstrdup(thisent +
									 vmp->vmt_data[VMT_OBJECT].vmt_off);
		}
        me->me_mountdir = xstrdup(thisent + vmp->vmt_data[VMT_STUB].vmt_off);
        me->me_type = xstrdup(fstype_to_string(vmp->vmt_gfstype));
        me->me_type_malloced = 1;
        options = (thisent + vmp->vmt_data[VMT_ARGS].vmt_off);
        ignore = strstr(options, "ignore");
        me->me_dummy =(ignore
					   && ((ignore == options) || (ignore[-1] == ','))
                        && ((ignore[(sizeof("ignore") - 1)] == ',')
                            || (ignore[(sizeof("ignore") - 1)] == '\0')));
        me->me_dev = (dev_t)-1; /* vmt_fsid might be the info we want.  */

        /* Add to the linked list. */
        *mtail = me;
        mtail = &me->me_next;
	}
    free(entries);
  }
#endif /* MOUNTED_VMOUNT. */

#ifdef MOUNTED_INTERIX_STATVFS
  {
    DIR *dirp = opendir ("/dev/fs");
    char node[9 + NAME_MAX];

    if (!dirp)
      goto free_then_fail;

    while (1)
      {
        struct statvfs dev;
        struct dirent entry;
        struct dirent *result;

        if (readdir_r (dirp, &entry, &result) || result == NULL)
          break;

        strcpy (node, "/dev/fs/");
        strcat (node, entry.d_name);

        if (statvfs (node, &dev) == 0)
          {
            me = xmalloc (sizeof(*me));
            me->me_devname = xstrdup (dev.f_mntfromname);
            me->me_mountdir = xstrdup (dev.f_mntonname);
            me->me_type = xstrdup (dev.f_fstypename);
            me->me_type_malloced = 1;
            me->me_dummy = ME_DUMMY (me->me_devname, me->me_type);
            me->me_remote = ME_REMOTE (me->me_devname, me->me_type);
            me->me_dev = (dev_t) -1;        /* Magic; means not known yet. */

            /* Add to the linked list. */
            *mtail = me;
            mtail = &me->me_next;
          }
      }
  }
#endif /* MOUNTED_INTERIX_STATVFS */

  *mtail = NULL;
  return mount_list;

/* conditions that use this label: */
#if defined(MOUNTED_GETMNT) || defined(MOUNTED_GETMNTENT1) || (defined(MOUNTED_FREAD) \
    || defined(MOUNTED_FREAD_FSTYP)) || defined(MOUNTED_GETMNTENT2) || defined(MOUNTED_INTERIX_STATVFS)
 free_then_fail:
  {
    int saved_errno = errno;
    *mtail = NULL;

    while (mount_list) {
        me = mount_list->me_next;
        free(mount_list->me_devname);
        free(mount_list->me_mountdir);
        if (mount_list->me_type_malloced) {
			free(mount_list->me_type);
		}
        free(mount_list);
        mount_list = me;
	}

    errno = saved_errno;
    return NULL;
  }
#endif /* MOUNTED_GETMNT || MOUNTED_GETMNT1 || (MOUNTED_FREAD || MOUNTED_FREAD_FSTYP) \
        * || MOUNTED_GETMNT2 || MOUNTED_INTERIX_STATVFS */
}

/* EOF */
