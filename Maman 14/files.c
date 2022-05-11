#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "error.h"
#include "parser.h"
#include "list_handling.h"


FILE* open_file(const char* file_name, char* ending, char* mode)
{
	FILE* file_p;
	char* full_file_name;
	
	full_file_name = get_full_file_name(file_name, ending);
	
	file_p = fopen(full_file_name, mode);
	free(full_file_name);
	if(!file_p) {
		fprintf(stderr, ErrorCantRead, full_file_name);
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}
	return file_p;
	
}



char* get_full_file_name(const char* file_name, char* ending)
{
	char* file_name_base;
	
	file_name_base = (char*)malloc((strlen(file_name) + AdditionalChars));
	if (!file_name_base) {
		fatal_error(ErrorMemoryAlloc);
   	     exit(0);
	}
    
	file_name_base[0] = '\0';

	strcat(file_name_base,file_name);
	strcat(file_name_base,ending);
    
    	file_name_base[strlen(file_name_base)] ='\0';
	
	return file_name_base;
}

void handle_file(const char* file_name, char* mode)
{
	char line[LINE_LEN];
	FILE* fp = open_file(file_name, MainFileEnding ,ReadFile);
	/*
	*	Here should be pre assembler
	*	and re-open the new file.
	*	after that we'll build ParserData struc
	*	to hold the file lists and data like ic,dc ect..
	
		parser_data = (ParserData*) malloc (sizeof(ParserData));
	 
	*/
	/*until pase 11 */
	while(fgets(line, LINE_LEN, fp)){
		/*parser_data.line_counter++;*/
		/*parse_line(line,0, label_list* symbols);*/
		puts(line);
	}
	
	/*
	part 2 of first move.
	while(fgets(line, LINE_LEN, fp)){
		puts(line);
	/*
		l_cnt++;
		call_func_to_11(line, 0, symbols);//TODO - change name
	}
	*/
	
	/*free(parser_data)*/
	fclose(fp);
}

