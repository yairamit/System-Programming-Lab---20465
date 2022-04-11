#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "mat.h"



void get_next_word(char* line, char word[], int* ptr_curr);
int get_comma(char * line, int *ptr_curr);
int get_number(char* line, int* ptr_curr);


int main() {
    
    printf("Hello World\n");
    int curr, i;
    char line[MAX_LEN];
    char word[MAX_LEN];
    
    
    while(fgets(line , MAX_LEN, stdin)){
        puts(line);
        curr = 0;
        
        /* get Command name */
        get_next_word(line, word, &curr);
        if(!strcmp("read_mat", word)){
            read_mat(line, &curr);
        }
        else if(!strcmp("add_mat", word)){
            add_mat(line, &curr);
        }
        
        else if(!strcmp("stop", word))
            stop();
        
        else if(!strcmp("print_mat", word))
            print_mat(line, &curr);
            
        else if (!strcmp("mul_mat", word))
            mul_mat(line, &curr);
        
        else if (!strcmp("mul_scalar", word))
            mul_mat(line, &curr);
        
        
        printf("enter comand: \n");
    }
    return 0;
}


 /* params in line should saparate by comma*/ 
 int get_comma(char* line, int *ptr_curr){
    int curr = *ptr_curr;
    int comma = 0;
    
    go_head(line, &curr);
	
	if(line[curr] == ','){
	    curr++;
	    comma = 1;
	}
	
	go_head(line, &curr);
	
	*ptr_curr = curr;
}


/* get_next_word for func name and mat name */
void get_next_word(char* line, char word[], int* ptr_curr){
    int curr = *ptr_curr, j; 
    
    go_head(line, &curr);
		
	for(j = 0; !isspace(line[curr]) && line[curr] != '\n'; curr++)
		word[j++] = line[curr];
	word[j] = '\0';
	
	go_head(line, &curr);

	*ptr_curr = curr; 
}





