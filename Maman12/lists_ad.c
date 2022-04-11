#include <stdio.h>
#include <stdlib.h>

int main() {
    char *str = NULL;
    int c;
    int size = 0, len = 0, sumOfalpanumeric = 0;

    while ((c=getchar()) != EOF && c != '\n') {
        if (len + 1 >= size)
        {
            size = size * 2 + 1;
            str = realloc(str, sizeof(char)*size);
            
        }
        if(isalnum(c))
        	sumOfalpanumeric++;
        str[len++] = c;
    }
    if (str != NULL) {
        str[len] = '\0';
        printf("%s\n", str);
        printf("sum of alpha = %d, total sum = %d\n", sumOfalpanumeric, len);
        free(str);
    }

    return 0;
}
