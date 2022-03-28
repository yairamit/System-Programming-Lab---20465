#include <stdio.h>

int find_bits(unsigned x, unsigned y){
    	int sum = 0;
    	while(x > 0){
        	if( (x & 1) && (y & 1)){
            	sum += 1;
        	}
        	x = x>>1;
        	y = y>>1;
    	}
    	return sum;
}


int main()
{
	printf("This program check how many bits are 1 in the same location in two unsigned number.\n\n");
	unsigned x , y;
    	printf("Enter x: ");
    	scanf("%u", &x);
    	printf("Enter y: ");
    	scanf("%u", &y);
    	printf("num of bits: %d\n", find_bits(x , y));
    	return 0;
}

/*
195, 249
*/
