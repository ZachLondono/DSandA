#include "LinkedList.h"
#include <stdio.h>
#include <string.h>

int main() {

	LinkedList list;
	list.head = NULL;
	list.size = 0;
	
	printf("Adding number1\n");
	int number = 123;
	ll_add(&list, &number, sizeof(int));

	printf("Adding number2\n");
	int number2 = 456;
	ll_add(&list, &number2, sizeof(int));

	printf("Reading number1\n");
	int* value1 = (int*) ll_getvalue(&list, 0);
	printf("1: %d\n", *value1);

	printf("Reading number2\n");
	int* value2 = (int*) ll_getvalue(&list, 1);
	printf("2: %d\n", *value2);


	printf("Rewriting index: 0\n");
	int newNumber1 = 999;
	ll_setvalue(&list, &newNumber1, sizeof(int), 0);
	printf("Reading number1\n");
	value1 = (int*) ll_getvalue(&list, 0);
	printf("1: %d\n", *value1);


	printf("Rewriting index: 1\n");
	ll_setvalue(&list, &newNumber1, sizeof(int), 1);
	printf("Reading number2\n");
	value2 = (int*) ll_getvalue(&list, 1);
	printf("2: %d\n", *value2);

	
	printf("Removing index: 1\n");
	void* node = ll_getvalue(&list, 1);
	ll_remove(list, node);


	printf("Rewriting index: 10 (invliad)\n");
	ll_setvalue(&list, &newNumber1, sizeof(int), 10);	

	ll_free(&list);

}
