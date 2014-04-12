/*
 *  dysize.c
 *  libUnixToOSX
 *
 *  Created by Eric Gallager on 4/2/14.
 *  Adapted from code taken from Apple documentation.
 *
 */

#include "dysize.h"

/* should return 365 for a normal year and 366 for a leap year (I think?) */

int dysize(int year) {
	/* to consider: maybe use the "tm_year" field in struct tm? */
	int leap_year;
	leap_year = ((year % 4 == 0) && (((year % 100) != 0) || ((year % 400) == 0)));
	return leap_year;
}

/* EOF */
