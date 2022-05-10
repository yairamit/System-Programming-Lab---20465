#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "parser.h"
#include "list_handling.h"



void open_file(const char* file_name, char* mode);


int main(int argc, char* argv[])
{
	int i = 1;
	for(i = 1; i < argc; i++){
		open_file(argv[i], "r");
		
	} if(i < 2){
		fatal_error(ErrorMissingArgument);
	}
	
	return 0;
}

/* TODO - build new file for all files function.  
*  	  preAssembler, get name with as/ps etc, 
*	  move parse process to 'parse' file, sec move of algo will be in 'command' file
*/
void open_file(const char* file_name, char* mode) {
	
	char line[81];
	int l_cnt = 0;
	label_list* symbols;

	FILE* fp = fopen(file_name, mode);
	if(!fp)
		fatal_error(ErrorCantRead);
	
	symbols = create_list();
	
	while(fgets(line, LINE_LEN, fp)){
		l_cnt++;
		parse_line(line, l_cnt, symbols);
	}
	/*until pase 11 */
	while(fgets(line, LINE_LEN, fp)){
		l_cnt++;
		call_func_to_11(line, l_cnt, symbols);/*TODO - change name */
	}
	
	print_label_table(symbols);
	deleteList(symbols);

	fclose(fp);
}