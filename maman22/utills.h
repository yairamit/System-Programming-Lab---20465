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
* extract the next number from the line (from curr pointer)
* as a char*, return 1 if succeeded.
*/
void get_number(char* line,char num[], int* ptr_curr);

/*
* extract the name of the matrix ffrom argument,
* return the num of mat in the mat array.
*/
int get_mat(char* line , int* ptr_curr, int comma_expacted);

/*
* move the curr pointer over comma
*/
void jump_comma(char* line, int *ptr_curr);

/*
* check if the next non white char is a comma
* without moving the pointer.
*/
int check_comma(char* line, int *ptr_curr);

#endif

