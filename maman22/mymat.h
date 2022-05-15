#ifndef MYMAT_H
#define MYMAT_H

#define SIZE 4
#define NUM_OF_MATS 6
#define MAX_LEN 512


enum { COMMA_NOT_EXPACTED ,COMMA_EXPACTED};


typedef struct matrix {
    double** m; /* 2D array */
} matrix;

 /* ptr to struct */
typedef struct matrix * mat_ptr;

/* array of ptr of struct = array of 2d mats.*/
mat_ptr mats[NUM_OF_MATS]; 

/*
* get matrix name and variables and put them into the mat
*/
void read_mat(char *line , int* ptr_curr);
/*
* print the matrix
*/
void print_mat(char* line, int* ptr_curr);
/*
* 
*/
void add_mat(char* line , int* ptr_curr);
/*
*
*/
void sub_mat(char* line , int* ptr_curr);
/*
*
*/
void mul_mat(char* line , int* ptr_curr);
/*
*
*/
void mul_scalar(char* line, int *ptr_curr);
/*
*
*/
void trans_mat(char* line , int* ptr_curr);
/*
*
*/
void stop(char* line , int* ptr_curr);
/*
*
*/
int get_mat(char* line , int* ptr_curr, int comma_expacted);


/*
*
*/
mat_ptr create_mat();
/*
*
*/
void generate_mats();
/*
*
*/
void free_mat(mat_ptr ptr);


#endif
