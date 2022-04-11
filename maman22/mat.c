
#include <stdio.h>
#include <stdlib.h>


#define SIZE 4
#define MAX_LEN 256
#define NUM_OF_MATS 7


typedef int matrix[SIZE][SIZE];

matrix a, b, c, d, e, f;

const char* mats_name[7] = {"MAT_A","MAT_B","MAT_C","MAT_D","MAT_E","MAT_F","#"}; 
matrix* mats = { a, b, c, d, e, f};


/* STOP Function */
void stop(){
    exit(0);
}

void mul_mat(char* line , int* ptr_curr){
    int curr = *ptr_curr, i, j, k, mat1, mat2, mat3;
    char name[MAX_LEN];
    

    mat1 = get_mat(line, &curr);
    mat2 = get_mat(line, &curr);
    mat3 = get_mat(line, &curr);
    
    for(i = 0; i < SIZE; ++i){
        for(j = 0; j < SIZE; ++j){
            for(k = 0; k < SIZE; ++k) {
                mats[mat3][i][j] += mats[mat1][i][k] * mats[mat2][k][j];
            }
        }
    }
    
    *ptr_curr = curr;
    
}


void sub_mat(char* line , int* ptr_curr){
    int curr = *ptr_curr, i, j, mat1, mat2, mat3;
    char name[MAX_LEN];
    
    mat1 = get_mat(line, name, &curr);
    mat2 = get_mat(line, name, &curr);
    mat3 = get_mat(line, name, &curr);
    
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            mats[mat3][i][j] = (mats[mat1][i][j] - mats[mat2][i][j]);
        }
    }
    
    *ptr_curr = curr;
}

void add_mat(char* line , int* ptr_curr){
    int curr = *ptr_curr, i, j, mat1, mat2, mat3;
    char name[MAX_LEN];
    
    mat1 = get_mat(line, &curr);
    
    mat2 = get_mat(line, &curr);

    mat3 = get_mat(line, &curr);
    
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            mats[mat3][i][j] = (mats[mat1][i][j] + mats[mat2][i][j]);
        }
    }
    
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
        printf("%s\n", mats_name[i]);
        *ptr_curr = curr;
        return i;
    }
}


/* print mat for Debug */
void print_mat_debbug(int mat[SIZE][SIZE]){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j <SIZE; j++){
            printf("%d   ", mat[i][j]);
        }
        printf("\n");
    }
}
/* i can fix the double code here and in read_mat func.. */
void print_mat(char* line, int* ptr_curr){
    int curr = *ptr_curr, i;
    char name[MAX_LEN];

    i = get_mat(line, &curr);
    
    print_mat_debbug(mats[i]);

    *ptr_curr = curr;
}

/* get ech parameter from line */
int get_number(char* line, int* ptr_curr){
    int curr = *ptr_curr, j;
    char * c;
    char num[MAX_LEN];
    
    for(j = 0; !isspace(line[curr]) && line[curr] != '\n' && isalnum(line[curr]) ; curr++)
		num[j++] = line[curr];
	num[j] = '\0';
    go_head(line, &curr);
    /*printf("%d", atoi(num));*/
    *ptr_curr = curr;
    return atoi(num);
}

/* not finished   -   need to add matrix chose and insert the parameters.  */
void read_mat(char *line , int* ptr_curr){
    int curr = *ptr_curr, i;
    char name[MAX_LEN];
    
    i = get_mat(line, &curr);
    
    get_parameters(line, &mats[i], &curr);
    print_mat_debbug(mats[i]);

    
    *ptr_curr = curr;
}

/* get parameters for the matrix */
void get_parameters(char* line, int mat[SIZE][SIZE] ,int *ptr_curr){
    int i = 0, j, k = 0, curr = *ptr_curr;
    int arr[SIZE*SIZE] = {0};
    
    while(i < SIZE*SIZE){
        if(get_comma(line, &curr)){
            arr[i] = get_number(line, &curr);
            i += 1;
        }
        else 
            break;
        
    }
    for(i = 0; i < SIZE; i++){
            for ( j = 0 ; j < SIZE; j++)
                mat[i][j] = arr[k++];
    }
    
}


/*  TO DO !!!  */ 
void mul_scalar(char* line, int *ptr_curr){
    int curr = *ptr_curr, i , j, mat1, mat2, scalar = 1;
    
    mat1 = get_mat(line, &curr);
    get_comma(line, &curr);
    go_head(line, &curr);
    scalar = get_number(line, &curr);
    get_comma(line, &curr);
    go_head(line, &curr);
    mat2 = get_mat(line, &curr);
    printf("%d", mat2);
    
    printf("3\n");
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            mats[mat2][i][j] = mats[mat1][i][j] * scalar;
        }
    }
    
    
    *ptr_curr = curr;
}

void go_head(char* line ,int *ptr_curr){
    int curr = *ptr_curr;
    while( isspace(line[curr]) && line[curr] != '\n')
		curr++;
	*ptr_curr = curr;
}
