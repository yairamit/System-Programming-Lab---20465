#include "error.h"

#include <stdio.h>
#include <stdlib.h>


/* Fatal error - report and exit.*/
void fatal_error(const char* message) {
	printf(stderr, "Fatal error: %s\n", message);
	exit(EXIT_FAILURE);
}
/* Error log - report, rise counter and continue.*/
void error_log(char* message) {
	printf(stderr, "%s\n", message);
}
