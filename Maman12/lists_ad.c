#include <stdio.h>
#include <stdlib.h>


void lists_ad();

int main() {
    lists_ad(); 
    return 0;
}

/*
* lists_ad func - Get a string from the user,
* calculates the amount of alphanumeric characters and prints it on the screen.
* 
*/
void lists_ad(){
	char *str = NULL, *tmp = NULL;
    int c;
    int size = 0, len = 0, sumOfalpanumeric = 0;
    
    printf("This program counts alpha-numeric characters.\nplease type your string:\n");
	/* Get characters from user */
    while ((c=getchar()) != EOF) 
    {
        if (len + 1 >= size) {
            size = size * 2 + 1;
            tmp = realloc(str, sizeof(char)*size);
            /* check the if realloc succeeded */
            if(tmp){
            	str = tmp;
            }
            /* if realloc did not succeed we will free the memory we have already used and exit.*/
            else{
            	free(tmp);
            	free(str);
            	exit(0);
	    }
        }
        /* Checking the input */
        if(isalnum(c))
        	sumOfalpanumeric++;
        str[len++] = c;
    }
    
    /* Set the string and return the values */
    if (str != NULL) {
        str[len] = '\0';
        printf("\nYour String is:\n\n%s\n\n", str);
        printf("- - - - - - - - - - - - -\nsum of alphanumeric characters = %d, total sum of characters = %d\n", sumOfalpanumeric, len);
        free(str);
    }
	
}
