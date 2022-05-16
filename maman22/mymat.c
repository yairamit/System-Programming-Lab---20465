
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "mymat.h"






void read_mat(char *line , int* ptr_curr){
    
    int curr = *ptr_curr, i = 0, j, k = 0, mat_index;
    char num[MAX_LEN];
    double* arr = (double*)calloc(SIZE*SIZE, sizeof(double));
    if(arr){
	    mat_index = get_mat(line, &curr, COMMA_NOT_EXPACTED);
	    /* if get mat return -1 so there is an erro. */
	    if(mat_index >= 0){
		/* collect variables to temporary array. */
		while(i < SIZE*SIZE)
		{
		    if(check_comma(line, &curr)){
		        jump_comma(line, &curr);
		        
		        if(!check_comma(line, &curr)){
		            	get_number(line, &num ,&curr);
		            	arr[i] = atof(num);
		            	i += 1;
		        }
		        else{
		        	free(arr);
		            	printf("Too Many Commas.\n");
		            	return;
		        }
		    }
		    else 
		        break;
		}
		/* insert the temporary array into the chosen mat. */
		for(i = 0; i < SIZE; i++)
		    for ( j = 0 ; j < SIZE; j++) {
		        mats[mat_index]->m[i][j] = *(arr+k);
		        k++;
		    }
		/* set pointer. */
		*ptr_curr = curr;
	    }
	}
	free(arr);
}


void print_mat(char* line, int* ptr_curr){
    	int curr = *ptr_curr, mat_index, i, j;
    	char name[MAX_LEN];
    
    	mat_index = get_mat(line, &curr, COMMA_NOT_EXPACTED);
    	if(mat_index >= 0){
		for(i=0; i < SIZE; i=i+1){
			for(j=0; j < SIZE; j= j+1){
				    printf(" %6.2f ", *(*((mats[mat_index]->m)+i)+j));
			}
			printf("\n");
		}
	printf("\n");
    	}
    	*ptr_curr = curr;
}


void add_mat(char* line , int* ptr_curr){
    int curr = *ptr_curr, i, j, mat1, mat2, mat3;
    char name[MAX_LEN];
    
    mat1 = get_mat(line, &curr, COMMA_EXPACTED);
    mat2 = get_mat(line, &curr, COMMA_EXPACTED);
    mat3 = get_mat(line, &curr, COMMA_NOT_EXPACTED);
    
    
    if(mat1 >= 0 && mat2 >=0 && mat3 >= 0){
        for(i = 0; i < SIZE; i++) {
            for(j = 0; j < SIZE; j++) {
                mats[mat3]->m[i][j] = (mats[mat1]->m[i][j] + mats[mat2]->m[i][j]);
            }
        }
        *ptr_curr = curr;
    }
}

void sub_mat(char* line , int* ptr_curr){
    int curr = *ptr_curr, i, j, mat1, mat2, mat3;
    char name[MAX_LEN];
    
    mat1 = get_mat(line, &curr, COMMA_EXPACTED);
    mat2 = get_mat(line, &curr, COMMA_EXPACTED);
    mat3 = get_mat(line, &curr, COMMA_NOT_EXPACTED);
    
    if(mat1 >= 0 && mat2 >=0 && mat3 >= 0){
        
        for(i = 0; i < SIZE; i++) {
            for(j = 0; j < SIZE; j++) {
                mats[mat3]->m[i][j] = (mats[mat1]->m[i][j] - mats[mat2]->m[i][j]);
            }
        }
    
        *ptr_curr = curr;
    }
}

void mul_mat(char* line , int* ptr_curr){
    	int curr = *ptr_curr, i, j, k = 0, mat1, mat2, mat3;
    	char name[MAX_LEN];
	mat_ptr temp = create_mat();
	
    	mat1 = get_mat(line, &curr, COMMA_EXPACTED);
    	mat2 = get_mat(line, &curr, COMMA_EXPACTED);
    	mat3 = get_mat(line, &curr, COMMA_NOT_EXPACTED);
    
    	if(mat1 >= 0 && mat2 >=0 && mat3 >= 0){
        	for(i = 0; i < SIZE; ++i){
            		for(j = 0; j < SIZE; ++j){
            			
                		for(k = 0; k < SIZE; k++) {
                    			temp->m[i][j] += mats[mat1]->m[i][k] * mats[mat2]->m[k][j];
                		}
            		}
        	}
        	for(i = 0; i < SIZE; ++i){
            		for(j = 0; j < SIZE; ++j){
            			mats[mat3]->m[i][j] = temp->m[i][j];
            		}
            	}
            	
       		*ptr_curr = curr;
    	}
    	free_mat(temp);
}


void mul_scalar(char* line, int *ptr_curr){
    	int curr = *ptr_curr, i , j, mat1, mat2;
    	char num[MAX_LEN];
    	double scalar = 0.0;
    	
        mat1 = get_mat(line, &curr, COMMA_EXPACTED);
        jump_comma(line, &curr);
        
        get_number(line, &num,&curr);
        scalar = atof(num);
        
        if(!check_comma(line, &curr)){
            printf("Missing Comma.\n");
            return;
        }
        jump_comma(line, &curr);
        
        mat2 = get_mat(line, &curr, COMMA_NOT_EXPACTED);
        /* for every variable in the mat - mult with the scalar. */
        if(mat1 >= 0 && mat2 >=0){
            for(i = 0; i < SIZE; i++){
                for(j = 0; j < SIZE; j++){
                    mats[mat2]->m[i][j] = scalar*mats[mat1]->m[i][j];
                }
            }
            *ptr_curr = curr;
        }
}

void trans_mat(char* line , int* ptr_curr){
    int curr = *ptr_curr, i, j, mat1, mat2;
    double temp; /* for swaping */
    /* get the index of the matrix */
    mat1 = get_mat(line, &curr, COMMA_EXPACTED);
    mat2 = get_mat(line, &curr, COMMA_NOT_EXPACTED);
    
    if(mat1 >= 0 && mat2 >=0){
        for(i = 0; i <SIZE; i++) {
            for (j = i; j < SIZE; j++)
            {
                temp = mats[mat1]->m[j][i];
                mats[mat1]->m[j][i] = mats[mat2]->m[i][j];
                mats[mat2]->m[i][j] = temp;
            }
        } 
    }
    *ptr_curr = curr;
}

void stop(char* line , int* ptr_curr){
    	int i;
	for(i = 0; i < NUM_OF_MATS; i++){
		free_mat(mats[i]);
	}
	printf("\n---End-Of-Culc---\n");
	exit(0);
}



/********** start-func *************/


mat_ptr create_mat(){
    int i , j;
    mat_ptr new_mat;
    new_mat = (matrix*)malloc(sizeof(matrix));
    
    if(new_mat){
        new_mat->m = (double**) calloc (SIZE, sizeof(double*));
        
        if(new_mat->m){
            for(i = 0; i < SIZE ; i++) {
                *((new_mat->m)+i) = (double*) calloc (SIZE, sizeof(double));
                
                if(!(*((new_mat->m)+i))){
                    for (j = 0; j < i; j++){
                        free(*((new_mat->m)+j));
                    }
                    return NULL;
                }
            }
        } else {
            free(new_mat);
            return NULL;
        }
    }
    return new_mat;
}

void generate_mats(){
    int i, j;
    /* for each mats in the array - create mat and allocate space */
    for(i = 0; i < NUM_OF_MATS; i++){
            mats[i] = create_mat();
            if(!mats[i]){
                printf("memory allocation failed. exit program.\n");
                for(j = 0; j < i; j++){
                    free_mat(mats[j]);
                }
                exit(0);
            }
    }
}

void free_mat(mat_ptr ptr){
	int i;
	for(i = 0; i < SIZE; i++){
		free(*((ptr->m)+i));
	}
	free(ptr);
}
