#include "LinkedList.h"
#include <stdio.h>
#include <string.h>

int main() {

	LinkedList list;
	list.head = NULL;
	list.size = 0;
	
	printf("Adding number1\n");
	int number = 123;
	Add(&list, &number, sizeof(int));

	printf("Adding number2\n");
	int number2 = 456;
	Add(&list, &number2, sizeof(int));

	printf("Reading number1\n");
	int* value1 = (int*) GetValue(&list, 0);
	printf("1: %d\n", *value1);

	printf("Reading number2\n");
	int* value2 = (int*) GetValue(&list, 1);
	printf("2: %d\n", *value2);

	Free(&list);

}
