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
int ftw_simple(char *argv[])
{
	/* assume the path "/usr/include" has been passed through argv[3] */

	FTS *fileStruct;
	FTSENT *dirList;
	int ftsResult;

	fileStruct = fts_open(&argv[3], FTS_COMFOLLOW, 0);
	dirList = fts_children(fileStruct, FTS_NAMEONLY);

	do {
		FTSENT *fileInfo;
		void *result;

		fileInfo = (FTSENT *)fts_read((FTS *)dirList->fts_pointer);

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
		 * here (see the following quote from the  manpage for fts_open() for
		 * reference: "The argument compar() specifies a user-defined function
		 * which may be used to order the traversal of the hierarchy. It takes
		 * two pointers to pointers to FTSENT structures as arguments and should
		 * return a negative value, zero, or a positive value to indicate if the
		 * file referenced by its first argument comes before, in any order with
		 * respect to, or after, the file referenced by its second argument.") */
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
int compar_for_fts_open(const FTSENT **fsthing1, const FTSENT **fsthing2)
{
	/* really naive, not even sure if comparing them like this even works: */
	if (fsthing1 < fsthing2) {
		return -1;
	} else if (fsthing1 == fsthing2) {
		return 0;
	} else if (fsthing1 > fsthing2) {
		return 1;
	} else {
		fprintf(stderr, "compar_for_fts_open(): \
				the relation between the 2 entities compared should be '<', '==', or '>'...\
				not sure how you managed to get something different...");
		return -255;
	}
}

/* tried some functions to compare based on the members of FTSENT, but
 * that led to errors... */

/* EOF */
