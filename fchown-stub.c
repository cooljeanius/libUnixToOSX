/* fchown-stub.c */

#include <config.h>

#include <sys/types.h>
#include <errno.h>

#if defined(HAVE_UNISTD_H)
# include <unistd.h> /* specification. */
#endif /* HAVE_UNISTD_H */

/* A trivial substitute for 'fchown'.
 *
 * DJGPP 2.03 and earlier (and perhaps later) do NOT have 'fchown',
 * so we pretend that no-one has permission for this operation: */
int fchown(int fd _GL_UNUSED, uid_t uid _GL_UNUSED, gid_t gid _GL_UNUSED)
{
  errno = EPERM;
  return -1;
}

/* EOF */
