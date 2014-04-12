/*
 *  ftw_Apple.c
 *  libUnixToOSX
 *
 *  Created by Eric Gallager on 4/2/14.
 *  Adapted from code taken from Apple documentation.
 *
 */

#include "ftw_Apple.h"

/* In order to get a description of each file located in /usr/include using
 * fts.h, the code would be as follows: */
int ftw_simple(char *argv[]) {
	/* assume that the path "/usr/include" has been passed through argv[3]*/

	FTS *fileStruct;
	FTSENT *dirList;
	int ftsResult;

	fileStruct = fts_open(&argv[3], FTS_COMFOLLOW, 0);
	dirList = fts_children(fileStruct, FTS_NAMEONLY);

	do {
		FTSENT *fileInfo;
		void *result;

		fileInfo = fts_read(dirList->fts_pointer);

		/* dummy condition to use value stored to 'fileInfo': */
		if (fileInfo == 0) {
			;
		}

		result = malloc(sizeof(int (*)(const FTSENT **, const FTSENT **)));

		/* at this point, you should be able to extract information from the
		 * FTSENT returned by fts_read(): */

		fileStruct = fts_open((char * const *)dirList->fts_link->fts_name,
							  FTS_PHYSICAL, (void *)result);
		/* TODO: write an actual compar() function to use in the 3rd argument
		 * here (see the manpage for fts_open() for reference) */
		/* (started a stub for it below) */

	} while (dirList->fts_link != NULL);

	ftsResult = fts_close(fileStruct);

	return ftsResult;
}

/* See the manual page for fts to understand the structures and macros used in
 * the above code. The above code above shows a very simplistic file traversal.
 * For instance, it does not consider possible subdirectories existing in the
 * directory being searched. */

/* one of the arguments to fts_open() takes a function pointer to a user-defined
 * comparing function, so try to implement that here: */
int compar_for_fts_open(const FTSENT **fsthing1, const FTSENT **fsthing2) {
	/* TODO: use the parameters and actually do something here */
	return 0;
}

/* EOF */
