#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define SIZE 4
#define NUM_OF_MAT 6
#define MAX_LEN 512

void read_mat(char*, int*);
void print_mat(char*, int*);
void add_mat(char*, int*);
void sub_mat(char*, int*);
void mul_mat(char*, int*);
void mul_scalar(char*, int*);
void trans_mat(char*, int*);
void stop();

int get_mat(char*, int*);
void get_parameters(char*, int mat[SIZE][SIZE] ,int*);
void go_head(char* ,int*);


#endif // !