#ifndef UTILLS_H
#define UTILLS_H

const char* mats_name[NUM_OF_MATS] = { "MAT_A","MAT_B","MAT_C","MAT_D","MAT_E","MAT_F" };

/*
* move pointer to the next word.
*/
void go_head(char* line ,int *ptr_curr);
/*
* get the next word on the line  -  from the current pointer.
*/
void get_next_word(char* line, char word[], int* ptr_curr);
/*
*
*/
void get_number(char* line,char num[], int* ptr_curr);
/*
*
*/
int get_mat(char* line , int* ptr_curr, int comma_expacted);
/*
* 
*/
void jump_comma(char* line, int *ptr_curr);
/*
*
*/
int check_comma(char* line, int *ptr_curr);

#endif

