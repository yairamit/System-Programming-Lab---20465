#include <stdio.h>
#include <stdlib.h>

int main() {
    char *str = NULL, *tmp = NULL;
    int c;
    int size = 0, len = 0, sumOfalpanumeric = 0;
    
    printf("This program counts alpha-numeric characters.\nplease type your string:\n");
	/* Get characters from user */
    while ((c=getchar()) != EOF && c != '\n') 
    {
        if (len + 1 >= size) {
            size = size * 2 + 1;/**/
            tmp = realloc(str, sizeof(char)*size);
            if(tmp){
            	str = tmp;
            }
            else{
            	free(tmp);
            	free(str);
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
        printf("\nYour String is:\n%s\n", str);
        printf("sum of alpha = %d, total sum = %d\n", sumOfalpanumeric, len);
        free(str);
    }

    return 0;
}
