#include <stdio.h>


int my_scalar(int x[], int y[], int size){
	int i, sum = 0;
	for(i = 0; i < size; i++){
			sum += x[i] * y[i];
		}
	return sum;
}


int main(){

	int size = 1, i, z;

	printf("Enter vector size: ");
	scanf("%d", &size);
	if(size == 0){
		printf("Invalid size of vectors.");
		return 0;
	}

	int x[size];
	int y[size];

	printf("Enter item to x: \n");
	for(i=0; i<size; i++){
		scanf("%d", &z);
		x[i] = z;
	}

	printf("Enter item to y: \n");
		for(i=0; i<size; i++){
			scanf("%d", &z);
			y[i] = z;
		}
	/*
	for(i=0; i< size; i++){
		printf("%d", y[i]);
	}
	*/
	printf("The scalar product: %d\n", my_scalar(x, y, size));

	return 0;
}

