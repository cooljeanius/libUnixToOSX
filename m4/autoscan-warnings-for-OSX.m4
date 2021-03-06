# Define a dummy macro to ensure that this file gets included:
AC_DEFUN([AN_OSX_WARNINGS_DUMMY_MACRO],[
  test -x "`which autoscan`"
dnl# Programs:
AN_MAKEVAR([LDD],
           [warn: The LDD Makefile variable will most likely end up being empty on OS X. However, you can use the command otool -L to get the same functionality that ldd provides.])dnl
AN_PROGRAM([ldd],
           [warn: The ldd program is not available in OS X. However, you can use the command otool -L to get the same functionality that ldd provides.])dnl
AN_MAKEVAR([LSMOD],
           [warn: The LSMOD Makefile variable will most likely end up being empty on OS X.])dnl
AN_PROGRAM([lsmod],
           [warn: The lsmod program is not available on OS X, but other commands exist that offer similar functionality.])dnl

dnl# Headers:
AN_HEADER([alloc.h],
          [warn: alloc.h does not exist in OS X, but the functionality does exist. You should include stdlib.h instead. Alternatively, you can define the prototypes yourself.])dnl
AN_HEADER([ftw.h],
          [warn: ftw.h should not exist in OS X, and there is NOT a function similar to ftw in fts.h.])dnl
AN_HEADER([getopt.h],
          [warn: getopt.h is unsupported, use unistd.h instead])dnl
AN_HEADER([lcrypt.h],
          [warn: lcrypt.h is unsupported, use unistd.h instead])dnl
AN_HEADER([malloc.h],
          [warn: malloc.h is unsupported, use stdlib.h for just malloc instead, or malloc/malloc.h for other malloc-related functions])dnl
AN_HEADER([mm.h],
          [warn: mm.h is not supported in Max OS X. In OS X, you can use mmap to map files into memory. If you wish to map devices, use the I/O Kit framework instead.])dnl
AN_HEADER([module.h],
          [warn: Instead of using module.h, kernel modules should instead be loaded using the KextManager API in the I/O Kit framework. The modules themselves must be compiled against the Kernel framework.])dnl
AN_HEADER([nl_types.h],
          [warn: instead of using nl_types.h, use the APIs in CoreFoundation for similar localization functionality.])dnl
AN_HEADER([ptms.h],
          [warn: Although pseudo-TTYs are supported in OS X, the ptms.h header is not. The implementation of pseudo-TTYs is very different on OS X from their implementation on Linux. For more information, see the pty manual page.])dnl
AN_HEADER([stream.h],
          [warn: the stream.h header file is not present in OS X. For file streaming, use iostream.h.])dnl
AN_HEADER([stropts.h],[warn: stropts.h is not supported in OS X.])dnl
AN_HEADER([swapctl.h],
          [warn: OS X does not support the swapctl.h header file. You can use the header file swap.h to implement swap functionality. The swap.h header file contains many functions that can be used for swap tuning.])dnl
AN_HEADER([termio.h],
          [warn: The termio.h header file is obsolete, and has been replaced by termios.h, which is part of the POSIX standard. These two header files are very similar. However, the termios.h does not include the same header files as termio.h. Thus, you should be sure to look directly at the termios.h header to make sure it includes everything your application needs.])dnl
AN_HEADER([utmp.h],
          [warn: utmp.h is deprecated in OS X, use utmpx.h instead.])dnl
AN_HEADER([values.h],[warn: values.h is not supported in OS X, use limits.h instead.])dnl
AN_HEADER([wchar.h],
          [warn: although the functionality from wchar.h is available in OS X, you should generally use the APIs in Core Foundation instead.])dnl

dnl# Functions:
AN_FUNCTION([btowc],
            [warn: Although OS X supports the wchar API for btowc, the preferred way to work with international strings is through CoreFoundation])dnl
AN_FUNCTION([wctob],
            [warn: Although OS X supports the wchar API for wctob, the preferred way to work with international strings is through CoreFoundation])dnl
gl_WARN_ON_USE_PREPARE([[
#include <stdio.h>
#include <wchar.h>
  ]],[btowc wctob])dnl
gl_WARN_ON_USE_PREPARE([[
#include <wchar.h>
#include <xlocale.h>
  ]],[btowc_l wctob_l])dnl
AN_FUNCTION([catopen],
            [warn: nl_types.h is not supported on OS X, thus, catopen is not supported on OS X. Use CoreFoundation instead.])dnl
AN_FUNCTION([catgets],
            [warn: nl_types.h is not supported on OS X, thus, catgets is not supported on OS X. Use CoreFoundation instead.])dnl
AN_FUNCTION([catclose],
            [warn: nl_types.h is not supported on OS X, thus, catclose is not supported on OS X. Use CoreFoundation instead.])dnl
gl_WARN_ON_USE_PREPARE([[
#include <nl_types.h>
  ]],[catopen catgets catclose])dnl
AN_FUNCTION([dysize],[warn: dysize is not supported in OS X.])dnl
AN_FUNCTION([ecvt],
            [warn: use of ecvt is discouraged in OS X. Use sprintf, snprintf, and similar functions instead.])dnl
AN_FUNCTION([fcvt],
            [warn: use of fcvt is discouraged in OS X. Use sprintf, snprintf, and similar functions instead.])dnl
AN_FUNCTION([gcvt],
            [warn: use of gcvt is discouraged in OS X. Use sprintf, snprintf, and similar functions instead.])dnl
gl_WARN_ON_USE_PREPARE([[
#include <stdlib.h>
  ]],[ecvt fcvt gcvt])dnl
AN_FUNCTION([fcloseall],[warn: Although OS X supports fclose, fcloseall is not supported.])dnl
AN_FUNCTION([getmntent],
            [warn: In general, volumes in OS X are not in /etc/fstab. However, to the extent that they are, you can get functionality similar to getmntent by using getfsent instead])dnl
AN_FUNCTION([setmntent],
            [warn: In general, volumes in OS X are not in /etc/fstab. However, to the extent that they are, you can get functionality similar to setmntent by using setfsent instead])dnl
AN_FUNCTION([addmntent],
            [warn: In general, volumes in OS X are not in /etc/fstab. However, to the extent that they are, you can probably find functionality similar to addmntent by looking through the functions in fstab.h])dnl
AN_FUNCTION([endmntent],
            [warn: In general, volumes in OS X are not in /etc/fstab. However, to the extent that they are, you can get functionality similar to endmntent by using endfsent instead])dnl
AN_FUNCTION([hasmntopt],
            [warn: In general, volumes in OS X are not in /etc/fstab. However, to the extent that they are, you can probably find functionality similar to hasmntopt by looking through the functions in fstab.h])dnl
AN_FUNCTION([poll],
            [warn: The poll API is partially supported in OS X. It does not support polling devices though.])dnl
gl_WARN_ON_USE_PREPARE([[
#include <poll.h>
  ]],[poll])dnl
AN_FUNCTION([sbrk],
            [warn: The sbrk function is a historical curiosity left over from earlier days before the advent of virtual memory management. Although sbrk is present on the system, it is not recommended.])dnl
AN_FUNCTION([brk],
            [warn: The brk function is a historical curiosity left over from earlier days before the advent of virtual memory management. Although brk is present on the system, it is not recommended.])dnl
gl_WARN_ON_USE_PREPARE([[
#include <unistd.h>
  ]],[brk sbrk])dnl
AN_FUNCTION([shmget],
            [warn: The shmget API is supported but is not recommended. shmget has a limited memory blocks allocation. When several applications use shmget, this limit may change and cause problems for the other applications. In general, you should either use mmap for mapping files into memory or use the POSIX shm_open function and related functions for creating non-file-backed shared memory.])dnl
gl_WARN_ON_USE_PREPARE([[
#include <sys/shm.h>
  ]],[shmget])dnl
AN_FUNCTION([swapon],
            [warn: The swapon function is not supported in OS X.])dnl
AN_FUNCTION([swapoff],
            [warn: The swapoff function is not supported in OS X.])dnl
])dnl

