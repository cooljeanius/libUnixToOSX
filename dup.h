/* dup.h */

/* misc. prototypes for dup-related functions */

#ifndef __DUP_H__
#define __DUP_H__ 1

/* from dup.c: */
#ifndef rpl_dup
int rpl_dup(int fd);
#endif /* !rpl_dup */

/* from dup2.c: */
#ifndef rpl_dup2
int rpl_dup2(int fd, int desired_fd);
#endif /* !rpl_dup2 */

/* from dup-safer-flag.c: */
#ifndef dup_safer_flag
int dup_safer_flag(int fd, int flag);
#endif /* !dup_safer_flag */

#endif /* !__DUP_H__ */

/* EOF */
