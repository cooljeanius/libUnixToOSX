/*
 *  rpl_misc_funcs.h
 *  libUnixToOSX
 *
 *  Created by Eric Gallager on 4/20/14.
 *  Header file for misc. "rpl_*" functions
 */

#ifndef __RPL_MISC_FUNCS_H__
#define __RPL_MISC_FUNCS_H__ 1

#include <stdio.h> /* required for file pointers */
#include <sys/stat.h> /* needed for 'struct stat' */

/* from close.c: */
#ifndef rpl_close
int rpl_close(int fd);
#endif /* !rpl_close */

/* from fchdir.c: */
#ifndef _gl_unregister_fd
void _gl_unregister_fd(int fd);
#endif /* !_gl_unregister_fd */
#ifndef _gl_register_fd
int _gl_register_fd(int fd, const char *filename);
#endif /* !_gl_register_fd */
#ifndef _gl_register_dup
int _gl_register_dup(int oldfd, int newfd);
#endif /* !_gl_register_dup */
#ifndef _gl_directory_name
const char *_gl_directory_name(int fd);
#endif /* !_gl_directory_name */

/* from fd-safer-flag.c: */
#ifndef fd_safer_flag
int fd_safer_flag(int fd, int flag);
#endif /* !fd_safer_flag */

/* from fdopen.c: */
#ifndef rpl_fdopen
FILE *rpl_fdopen(int fd, const char *mode);
#endif /* !rpl_fdopen */

/* from fflush.c: */
#ifndef rpl_fflush
int rpl_fflush(FILE *stream);
#endif /* !rpl_fflush */

/* from fstat.c: */
#ifndef rpl_fstat
int rpl_fstat(int fd, struct stat *buf);
#endif /* !rpl_fstat */

/* from itold.c: */
#ifndef _Qp_itoq
void _Qp_itoq(long double *result, int a);
#endif /* !_Qp_itoq */

#endif /* !__RPL_MISC_FUNCS_H__ */

/* EOF */
