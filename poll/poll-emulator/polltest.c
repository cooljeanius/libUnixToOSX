/* $Id$ */
/* polltest.c: simple test-case for the poll-emulator package */
/* License: not sure? The rest of the poll-emulator package has a BSD-style
 * license, but I am also using this file with a bunch of gnulib sources, which
 * are all GPL... */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "pollemu.h"

#ifdef HAVE_CONFIG_H
# include "../../config.h"
#else
# define POLLTEST_C_NON_AUTOTOOLS_BUILD 1
# if defined(__GNUC__) && !defined(__STRICT_ANSI__) && !defined(__STDC__)
#  warning "building polltest.c without autoheader is unsupported."
# endif /* __GNUC__ && !__STRICT_ANSI__ */
#endif /* HAVE_CONFIG_H */

#if ((defined(HAVE_STDLIB_H) && defined(HAVE_EXIT)) || defined(POLLTEST_C_NON_AUTOTOOLS_BUILD)) && !defined(exit)
# include <stdlib.h>
#else
# if defined(__GNUC__) && !defined(__STRICT_ANSI__) && !defined(exit) && !defined(_STDLIB_H_)
#  warning "polltest.c needs to include <stdlib.h> for exit()."
# endif /* __GNUC__ && !__STRICT_ANSI__ && !exit && !_STDLIB_H_ */
#endif /* ((HAVE_STDLIB_H && HAVE_EXIT) || POLLTEST_C_NON_AUTOTOOLS_BUILD) && !exit */

#define MAX	10

int main(int argc, char **argv)
{
    int	    arg;
    int	    i;
    struct  pollfd array[MAX];
    int     ready;

    if ((argc == 1) || ((argc % 2) != 1) || (argc > ((MAX * 2) + 1))) {
		fprintf(stderr, "Usage: %s r|w file [r|w file] ...\n", argv[0]);
		exit(1);
    }

    for ((arg = 1), (i = 0); (arg < argc); (arg += 2), i++) {
		int open_mode;
		short poll_mask;
		const char *strMode;

		if (argv[arg][0] == 'r') {
			open_mode = O_RDONLY;
			poll_mask = POLLIN;
			strMode   = "reading";
		} else {
			open_mode = O_WRONLY;
			poll_mask = POLLOUT;
			strMode   = "writing";
		}

		printf("%2d: Opening \"%s\" for %s ...\n", i, argv[(arg + 1)], strMode);
		array[i].revents = 0;
		array[i].events  = 0; /* initialize properly first */
		array[i].events |= poll_mask;
		array[i].fd      = open(argv[(arg + 1)], open_mode);
		if (array[i].fd == -1) {
			fprintf(stderr, "Cannot open \"%s\": errno %d\n",
					argv[(arg + 1)], errno);
			exit(1);
		}
    }

    printf("Polling on %d file descriptors.  Timeout is indefinite ...\n", i);
    ready = poll(array, (unsigned long) i, -1);
    printf("poll() returned %d.\n", ready);
    if (ready < 0) {
		printf("Errno = %d\n", errno);
	}

    for ((arg = 1), (i = 0); (arg < argc); (arg += 2), i++) {
		if (array[i].revents != 0) {
			printf("%2d (\"%s\"):", i, argv[(arg + 1)]);

			if (array[i].revents & POLLPRI) {
				printf(" EXCEPTION");
			}
			if (array[i].revents &  POLLIN) {
				printf(" INPUT");
			}
			if (array[i].revents & POLLOUT) {
				printf(" OUTPUT");
			}
			putchar('\n');
		}
    }

    exit(0);
}

/* EOF */
