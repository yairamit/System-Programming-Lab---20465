
#include <stdio.h>
#include <stdlib.h>


#define SIZE 4
#define MAX_LEN 512
#define NUM_OF_MATS 7


typedef int matrix[SIZE][SIZE];

matrix a, b, c, d, e, f;

const char* mats_name[NUM_OF_MATS] = { "MAT_A","MAT_B","MAT_C","MAT_D","MAT_E","MAT_F","#" }; 
matrix* mats = { a, b, c, d, e, f };



/* READ_MAT Method:
* get line of char aand extract the name of the the matrix and the parameters
* and set the params in the mat.
*/
void read_mat(char *line , int* ptr_curr){
    int curr = *ptr_curr, i;
    char name[MAX_LEN];
    
    printf("1\n");
    i = get_mat(line, &curr);/*  return the num of the matrix in the mats array (char*) */
    printf("2\n");
    get_parameters(line, &mats[i], &curr);
    printf("3\n");
    *ptr_curr = curr;
}

/* i can fix the double code here and in read_mat func.. */
void print_mat(char* line, int* ptr_curr){
    int curr = *ptr_curr, mat_index, i, j;
    char name[MAX_LEN];

    mat_index = get_mat(line, &curr);
    
    for(i = 0; i < SIZE; i++){
        for(j = 0; j <SIZE; j++){
            printf("%d   ", mats[mat_index][i][j]);
        }
        printf("\n");
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

/*  TO DO !!!  */ 
void mul_scalar(char* line, int *ptr_curr){
    int curr = *ptr_curr, i , j, mat1, mat2, scalar = 1;
    
    *ptr_curr = curr;
}
/* To - DO  */
void trans_mat(char* line , int* ptr_curr){
    int curr = *ptr_curr, i
}

/* STOP  Method - close the program*/
void stop(){
    exit(0);
}

/***********************************************/
/***********************************************/

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




void go_head(char* line ,int *ptr_curr){
    int curr = *ptr_curr;
    while( isspace(line[curr]) && line[curr] != '\n')
		curr++;
	*ptr_curr = curr;
}
