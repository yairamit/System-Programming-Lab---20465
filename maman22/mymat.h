#ifndef MYMAT_H
#define MYMAT_H

#define SIZE 4 /* for column size and row size */
#define NUM_OF_MATS 6 /* num of mats in the array */
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
* add two matrix and store the sum in the third mat
*/
void add_mat(char* line , int* ptr_curr);

/*
* sub two matrix and store the sum in the third mat
*/
void sub_mat(char* line , int* ptr_curr);

/*
* multiply two matrix and store the sum in the third mat
*/
void mul_mat(char* line , int* ptr_curr);

/*
* multiply matrix with scalar and store the result in another matrix
*/
void mul_scalar(char* line, int *ptr_curr);

/*
* transpose matrix and store the result in another matrix
*/
void trans_mat(char* line , int* ptr_curr);

/*
* stop the program and free allocated space.
*/
void stop(char* line , int* ptr_curr);


/*
* Allocate space for 2D array of double.
* return pointer the the mat.
*/
mat_ptr create_mat();

/*
* build arry of all the matrix,
* using create_mat() for each matrix in the array.
*/
void generate_mats();

/*
* free allocated memory of 2D array of double (matrix).
*/
void free_mat(mat_ptr ptr);


#endif
