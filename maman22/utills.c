#include "mymat.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "utills.h"



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
            printf("Missing Comma.\n");
            return -1;
        }
    }
    
    /* mat num handle. */
    if(i == NUM_OF_MATS){
        printf("Undifine Matrix Name.\n");
        return -1;
    }
    else{
        *ptr_curr = curr;
        return i;
    }
}


void go_head(char* line ,int *ptr_curr){
    	int curr = *ptr_curr;
    	while( isspace(line[curr]) && line[curr] != '\n')
		curr++;
	/* set the pointer to the start of the next word */
	*ptr_curr = curr;
}


void get_next_word(char* line, char word[], int* ptr_curr){
    	int curr = *ptr_curr, j; 
    	go_head(line, &curr);/* move pointer to next non-white char */

	for(j = 0; !isspace(line[curr]) && line[curr] != '\n' && line[curr] != ','; curr++){
	        word[j++] = line[curr];
	}
		
	word[j] = '\0';
	/*move pointer to the next non-white char */
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
    	go_head(line, &curr); /* search for non wihite character. */
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

