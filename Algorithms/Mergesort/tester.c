#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

void printarray(int array[], int size) {
	for(int i = 0; i < size; i++) {
		printf("%d", array[i]);
		if (i < size-1) printf(",");
	}
}

int main() {

	int array[10];
	array[0] = 1;
	array[1] = 2;
	array[2] = 3;
	array[3] = 4;
	array[4] = 5;
	array[5] = 6;
	array[6] = 7;
	array[7] = 8;
	array[8] = 9;
	array[9] = 10;

	printf("Original array: ");
	printarray(array,10);
	printf("\n");

	mergesort(array, 10);

	printf("Sorted array: ");
	printarray(array,10);
	printf("\n");

}
