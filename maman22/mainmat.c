#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "mymat.h"


struct {
	char* name;
	void (*func)(char* line ,int *ptr_curr);
} cmd[] = {
	{"read_mat", read_mat},
	{"print_mat", print_mat},
	{"add_mat", add_mat},
	{"sub_mat", sub_mat},
	{"mul_mat", mul_mat},
	{"mul_scalar", mul_scalar},
	{"trans_mat", trans_mat},
	{"stop", stop},
	{"not_valid", NULL}
};


void parse_line(){
   	char line[MAX_LEN];
	char command[MAX_LEN];
	int curr, i;
        
    	printf(">>> ");
    	while(fgets(line , MAX_LEN, stdin)){
		curr = 0;
        	puts(line);
        	get_next_word(line, command, &curr);
        
        	for (i = 0; cmd[i].func != NULL; i++)
			    if (strcmp(command, cmd[i].name) == 0)
					break;
					
		if (cmd[i].func == NULL){
			printf("Undefined Command.\n");		
		}
		else
			(*(cmd[i].func))(line, &curr);
			
		printf(">>> ");
    	}
	stop(line, &curr);
}



int main()
{
    printf("\n---Matrix-Culculator---\n");
    generate_mats();
    parse_line();
    
    return 0;
}





