/* cuserid.c
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.1 (the "License").  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON- INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
/*-
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _XOPEN_SOURCE
# define _XOPEN_SOURCE 500	/* to get the prototype declared */
#endif /* _XOPEN_SOURCE */

#include <pwd.h>
#include <stdio.h>
#include <string.h>

/* This is to make sure that we declare cuserid: */
#if defined(HAVE_UNISTD_H) || defined(_POSIX_C_SOURCE) || \
    (defined(__APPLE__) && !defined(_UNISTD_H_))
# include <unistd.h>
#else
# if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#  warning "cuserid expects <unistd.h> to be included."
# endif /* __GNUC__ && !__STRICT_ANSI__ */
#endif /* HAVE_UNISTD_H || _POSIX_C_SOURCE || (__APPLE__ && !_UNISTD_H_) */

#ifndef L_cuserid
# ifdef _PASSWORD_LEN
/* the two are probably the same: */
#  define L_cuserid _PASSWORD_LEN
# else
/* seems reasonable: */
#  define L_cuserid 128
# endif /* _PASSWORD_LEN */
#endif /* !L_cuserid */

#ifdef CURRENT_USER
# ifndef _UNISTD_H_
#  if defined(HAVE_UID_T) || defined(_UID_T)
extern uid_t getpwuid(void);
extern uid_t geteuid(void);
#  else
extern struct passwd *getpwuid(void);
extern unsigned short geteuid(void);
#  endif /* HAVE_UID_T || _UID_T */
# endif /* !_UNISTD_H_ */
static struct passwd *my_entry;
# ifndef cuserid
#  define cuserid(s)				\
  (my_entry = getpwuid(((int)geteuid())), \
   my_entry->pw_name)
# endif /* !cuserid */
#endif /* CURRENT_USER */

/* adapted from cuserid in the Libcompat package found on
 * <http://opensource.apple.com>: */
#if !defined(cuserid) && (!defined(_UNISTD_H_) || !defined(HAVE_CUSERID))
/* (in case we are missing the prototype) */
extern char *cuserid(char *s);
#endif /* !cuserid && (!_UNISTD_H_ || !HAVE_CUSERID) */

char *
cuserid(char *s)
{
	register struct passwd *pwd;

	if ((pwd = getpwuid(geteuid())) == NULL) {
		if (s) {
			*s = '\0';
        }
		return (s);
	}
	if (s) {
		(void)strncpy(s, pwd->pw_name, (size_t)L_cuserid);
		return (s);
	}
	return (pwd->pw_name);
}

/* EOF */
