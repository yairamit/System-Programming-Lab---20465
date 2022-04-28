#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define SIZE 4
#define NUM_OF_MATS 6
#define MAX_LEN 512




void read_mat(char *line , int* ptr_curr);
void print_mat(char* line, int* ptr_curr);
void add_mat(char* line , int* ptr_curr);
void sub_mat(char* line , int* ptr_curr);
void mul_mat(char* line , int* ptr_curr);
void scalar_mat(char* line, int *ptr_curr);
void trans_mat(char* line , int* ptr_curr);
void stop(char* line , int* ptr_curr);

/*
mat_ptr create_mat();
void generate_mats();
void free_mat(mat_ptr ptr);
*/





#endif // !
