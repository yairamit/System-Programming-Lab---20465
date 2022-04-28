#ifndef ERROR_H_
#define ERROR_H_

/* List of common errors:  */
#define ErrorMissingArgument "Missing argument."
#define ErrorMemoryAlloc "Memory allocation failed."
#define UndefinedCommand "Undefined command name."
#define TooManyCommas "There is too many cammas."
#define InvalidCharacter "Invalid Character."


#define UndifneMatName "Undifne Matrix Name."

/**
* Prints an error message and the program exits
*/
void fatal_error(const char *);
/**
* Prints an error message and adds 1 to the error counter
*/
void error_log(char* );

#endif
