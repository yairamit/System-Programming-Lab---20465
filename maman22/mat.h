
#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define SIZE 4
#define NUM_OF_MAT 6
#define MAX_LEN 1000


enum { NO, YES };


void stop();
void add_mat(char* line , int* ptr_curr);
void read_mat(char *line , int* ptr_curr);
void print_mat(char* line, int* ptr_curr);
void mul_mat(char* line , int* ptr_curr);
void mul_scalar(char* line, int *ptr_curr);
void print_mat_debbug(int mat[SIZE][SIZE]);
int get_mat(char* line, int* ptr_curr);
void get_parameters(char *line, int mat[4][4] ,int *ptr_curr);
void go_head(char* line ,int *ptr_curr);


#endif // !
