#include <stdio.h>
#include <stdlib.h>
#include "error.h"

int threre_is_errors = 0;

/*
* Fatal error - report and exit.
*/
void fatal_error(const char* message) {
	fprintf(stderr, "Fatal error: %s\n", message);
	exit(EXIT_FAILURE);
}

/*
* Error log - report, rise counter and continue.
*/
void error_log(char* msg, int line) {
	fprintf(stderr, "%s; The error is on line %d\n", msg, line);
}
