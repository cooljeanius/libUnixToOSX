## ------------------------- ##
## Checks for declarations.  ##
## ------------------------- ##

# AC_DECL_SYS_SIGLIST
# -------------------
AN_IDENTIFIER([sys_siglist],[AC_DECL_SYS_SIGLIST])
# Just replace the "AU" with an "AC":
AC_DEFUN([AC_DECL_SYS_SIGLIST],
[AC_REQUIRE([AC_HEADER_STDC])
 AC_CHECK_HEADERS_ONCE([signal.h])
 AC_CHECK_DECLS([sys_siglist],[],[],
[#include <signal.h>
/* NetBSD declares sys_siglist in unistd.h.  */
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#else
/* TODO: check to confirm that I used the right preprocessor macro for
 * detecting NetBSD here: */
# if defined(__GNUC__) && !defined(__STRICT_ANSI__) && defined(__NetBSD__)
#  warning "this conftest expects <unistd.h> to be included on NetBSD."
# endif /* __GNUC__ && !__STRICT_ANSI__ && __NetBSD__ */
#endif /* HAVE_UNISTD_H */
])
])# AC_DECL_SYS_SIGLIST
