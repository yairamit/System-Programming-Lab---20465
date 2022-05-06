#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "error.h"
#include "parser.h"
#include "list_handling.h"

int ic = 100;

void forward(char* line ,int *ptr_curr)
{
	int curr = *ptr_curr;
    	while( isspace(line[curr]) && line[curr] != '\n')
		curr++;
	*ptr_curr = curr;
}



int check_comma(char* line, int *ptr_curr)
{
    int curr = *ptr_curr, comma = 0;;
    forward(line, &curr);
    
    if(line[curr] == ',')
	    comma = 1;
    return comma;
}



void jump_comma(char* line, int *ptr_curr)
{
    	int curr = *ptr_curr;
    	forward(line, &curr);
	if(line[curr] == ',')
		curr++;
	
	forward(line, &curr);
	*ptr_curr = curr;
}

void get_next_word(char* line, char* word, int* ptr_curr)
{
	
	int curr = *ptr_curr, j; 
    
    	forward(line, &curr);

	for(j = 0; !isspace(line[curr]) && line[curr] != '\n' && line[curr] != ','; curr++)
		word[j++] = line[curr];
	word[j] = '\0';
	
	forward(line, &curr);

	*ptr_curr = curr; 
}



void parse_line(char* line, int l_cnt, label_list* symbols)
{
	int curr = 0, i;
	char* word = (char*)malloc(sizeof(char)* LINE_LEN);
	if(!word)
		fatal_error(ErrorMemoryAlloc);
	
	
	if(line[curr] != ";") /* comment line */
	{
		get_next_word(line, word, &curr);
		/*printf("%c\n",word[strlen(word)-1]);*/
		
		if(word[strlen(word)-1] == ':'){
			/* there is a label */
			puts(word);
			word[strlen(word)-1] = '\0';
			add_label_to_list(symbols, word, ic++);
		}
		
		free(word);
	}
}	

