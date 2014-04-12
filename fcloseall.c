/*
 *  fcloseall.c
 *  libUnixToOSX
 *
 *  Created by Eric Gallager on 4/3/14.
 *  Adapted from code taken from Apple documentation.
 *
 */

#include "fclose.h"

/* Notes from Linux manpage: */
/* The fcloseall() function closes all of the calling process's open streams.
 * Buffered output for each stream is written before it is closed
 * (as for fflush()); buffered input is discarded.
 * The standard streams, stdin, stdout, and stderr are also closed. */
/* This function returns 0 if all files were successfully closed;
 * on error, EOF is returned. */
/* This function is a GNU extension. */

/* Notes from Apple documentation: */
/* Although OS X supports fclose, fcloseall is not supported.
 * You can use fclose to implement fcloseall by storing the file pointers in
 * an array and iterating through the array. */

int fcloseall(void) {
	int succeeded;
	succeeded = 0;
	succeeded += fclose(stdin);
	succeeded += fclose(stdout);
	succeeded += fclose(stderr);
	return succeeded;
}

/* EOF */
