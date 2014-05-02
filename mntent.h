/* mntent.h
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef _MNTENT_H_
#define _MNTENT_H_ 1

#ifndef __ANDROID__
# define __ANDROID__ 1
#endif /* !__ANDROID__ */

#include <stdio.h> /* for file pointers */
#include <sys/cdefs.h> /* for __BEGIN_DECLS and __END_DECLS */

#define MNTTYPE_IGNORE "ignore"

typedef struct mntent
{
    char* mnt_fsname;
    char* mnt_dir;
    char* mnt_type;
    char* mnt_opts;
    int mnt_freq;
    int mnt_passno;
} mntent_t;


#if defined(__BEGIN_DECLS) && defined(__END_DECLS)
__BEGIN_DECLS
#endif /* __BEGIN_DECLS && __END_DECLS */

struct mntent* getmntent(FILE*);
#if defined(_GL_WARN_ON_USE) && defined(__APPLE__)
_GL_WARN_ON_USE(getmntent, "getmntent is not natively present on OS X.");
#endif /* _GL_WARN_ON_USE && __APPLE__ */

#if defined(__BEGIN_DECLS) && defined(__END_DECLS)
__END_DECLS
#endif /* __BEGIN_DECLS && __END_DECLS */

#endif /* !_MNTENT_H_ */

/* EOF */
