#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "mat.h"

#define MAX_LEN 512
#define NUM_OF_MATS 6
#define SIZE 4


const char* mats_name[NUM_OF_MATS] = { "MAT_A","MAT_B","MAT_C","MAT_D","MAT_E","MAT_F" };

void parse_line();
void go_head(char* line ,int *ptr_curr);
int get_mat(char* line , int* ptr_curr);
void get_next_word(char* line, char word[], int* ptr_curr);
int get_comma(char* line, int *ptr_curr);
void get_number(char* line,char num[], int* ptr_curr);


void main(){
    
    
    printf("\n----START----\n\n");
    
    
    
    
    generate_mats();
    parse_line();
    
    
}


void parse_line(){
    char line[MAX_LEN];
    char word[MAX_LEN];
    int curr;
    
    printf("\n----PARSE----\n");
    
    while(fgets(line , MAX_LEN, stdin)){
        curr = 0;
        get_next_word(line, word, &curr);
        
        if(!strcmp("read_mat", word)){
            read_mat(line, &curr);
        }
        
        else if(!strcmp("print_mat", word)){
            print_mat(line, &curr);
        }
        
        else if(!strcmp("add_mat", word)){
            add_mat(line, &curr);
        }
        
        else if(!strcmp("sub_mat", word)){
            sub_mat(line, &curr);
        }
        
        else if(!strcmp("mul_mat", word)){
            mul_mat(line, &curr);
        }
        
        else if(!strcmp("mul_scalar", word)){
            mul_scalar(line, &curr);
        }
        
        else if(!strcmp("trans_mat", word)){
            trans_mat(line, &curr);
        }
        
        else if(!strcmp("stop" , word)){
            stop();
        }
        
        else{
            printf("Command not found. try again  or stop\n");
            continue;
        }
        
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

int get_mat(char* line , int* ptr_curr){
    int curr = *ptr_curr, i;
    char word[MAX_LEN];
    
    get_next_word(line, word, &curr);
    for(i = 0; i < NUM_OF_MATS; i++){
        if(strcmp(word, mats_name[i]) == 0)
            break;
    }
    if(i == NUM_OF_MATS){
        printf("mat: %s does not exit. exit.\n", word);
        exit(0);
    }
    else{
        *ptr_curr = curr;
        return i;
    }
}

void get_next_word(char* line, char word[], int* ptr_curr){
    int curr = *ptr_curr, j; 
    
    go_head(line, &curr);

	for(j = 0; !isspace(line[curr]) && line[curr] != '\n'; curr++)
		word[j++] = line[curr];
	word[j] = '\0';

	go_head(line, &curr);

	*ptr_curr = curr; 
}




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

void get_number(char* line,char num[], int* ptr_curr){
    int curr = *ptr_curr, j;

    for(j = 0; !isspace(line[curr]) && line[curr] != '\n' && (isalnum(line[curr]) || line[curr] == '.' ); curr++)
		num[j++] = line[curr];
	num[j] = '\0';

    go_head(line, &curr);
    *ptr_curr = curr;

}



