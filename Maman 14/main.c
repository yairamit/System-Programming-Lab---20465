#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "parser.h"
#include "list_handling.h"
#include "files.h"



int main(int argc, char* argv[])
{
	int i = 1;
	for(i = 1; i < argc; i++){
		handle_file(argv[i], "r");
		
	} if(i < 2){
		fatal_error(ErrorMissingArgument);
	}
	
	return 0;
}

/* TODO - build new file for all files function.  
*  	  preAssembler, get name with as/ps etc, 
*	  move parse process to 'parse' file, sec move of algo will be in 'command' file
*/

