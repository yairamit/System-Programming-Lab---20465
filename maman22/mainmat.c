#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "mat.h"

#define MAX_LEN 512
#define NUM_OF_MATS 6
#define SIZE 4


const char* mats_name[NUM_OF_MATS] = { "MAT_A","MAT_B","MAT_C","MAT_D","MAT_E","MAT_F" };


struct {
	char* name;
	void (*func)(char* line ,int *ptr_curr);
} cmd[] = {
	{"read_mat", read_mat},
	{"print_mat", print_mat},
	{"add_mat", add_mat},
	{"sub_mat", sub_mat},
	{"mul_mat", mul_mat},
	{"scalar_mat", scalar_mat},
	{"trans_mat", trans_mat},
	{"stop", stop},
	{"not_valid", NULL}
};


void parse_line();
void go_head(char* line ,int *ptr_curr);
int get_mat(char* line , int* ptr_curr, int comma_expacted);
void get_next_word(char* line, char word[], int* ptr_curr);
void jump_comma(char* line, int *ptr_curr);
int check_comma(char* line, int *ptr_curr);
void get_number(char* line,char num[], int* ptr_curr);


int main(){
    
    
    printf("\n----START----\n");
    
    generate_mats();
    parse_line();
    
    return 0;
}

void parse_line(){
    char line[MAX_LEN];
    char command[MAX_LEN];
    int curr, i;
    
    
    printf("$: ");
    while(fgets(line , MAX_LEN, stdin)){
        curr = 0;
        
        get_next_word(line, command, &curr);
        
        for (i = 0; cmd[i].func != NULL; i++)
			    if (strcmp(command, cmd[i].name) == 0)
					break;
					
		if (cmd[i].func == NULL)
			printf(stderr, "Command does not exit:%s\n", command);
			
		else
			(*(cmd[i].func))(line, &curr);
			
		printf("$: ");
    }
}



/*****************************************************
        *     parsers -  methods      *
*****************************************************/



void go_head(char* line ,int *ptr_curr){
    int curr = *ptr_curr;
    while( isspace(line[curr]) && line[curr] != '\n')
		curr++;
	*ptr_curr = curr;
}

int get_mat(char* line , int* ptr_curr, int comma_expacted){
    int curr = *ptr_curr, i;
    char word[MAX_LEN];
    
    /* extract mat name from line*/
    get_next_word(line, word, &curr);
    
    for(i = 0; i < NUM_OF_MATS; i++){
        if(strcmp(word, mats_name[i]) == 0)
            break;
    }
    /*  comma handle. */
    if(comma_expacted){
        if(check_comma(line, &curr))
            jump_comma(line, &curr); 
        else{
            printf("Missing Comma.");
            return -1;
        }
    }
    
    /* mat num handle. */
    if(i == NUM_OF_MATS){
        printf("Undefined matrix name");
        return -1;
        /* TODO exit func*/
    }
    else{
        *ptr_curr = curr;
        return i;
    }
}

void get_next_word(char* line, char word[], int* ptr_curr){
    int curr = *ptr_curr, j; 
    
    go_head(line, &curr);

	for(j = 0; !isspace(line[curr]) && line[curr] != '\n' && line[curr] != ','; curr++){
	        word[j++] = line[curr];
	}
		
	word[j] = '\0';

	go_head(line, &curr);

	*ptr_curr = curr; 
}

int check_comma(char* line, int *ptr_curr){
    int curr = *ptr_curr, comma = 0;;
    go_head(line, &curr);
    
    if(line[curr] == ',')
	    comma = 1;
    return comma;
}


void jump_comma(char* line, int *ptr_curr){
    int curr = *ptr_curr;
    go_head(line, &curr);
	if(line[curr] == ',')
	    curr++;
	
	go_head(line, &curr);
	*ptr_curr = curr;
}

void get_number(char* line,char num[], int* ptr_curr){
    int curr = *ptr_curr, j;

    for(j = 0; !isspace(line[curr]) && line[curr] != '\n' && ( isalnum(line[curr]) || line[curr] == '.' || line[curr] == '-' ); curr++)
		num[j++] = line[curr];
	num[j] = '\0';

    go_head(line, &curr);
    *ptr_curr = curr;

}
