#include "ArrayList.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

	ArrayList list;

	Initilize(&list, 5);

	Add(&list, 1);
	Add(&list, 2);
	Add(&list, 3);

	int i = 0;
	for (i = 0; i < 3; i++) {
		int value = -1;
		int ret = Get(&list, i, &value);

		if (ret >= 0)
			printf("%d -> %d\n", i, value);
		else printf("Error reading from arraylist\n");
	}

}

void Initilize(ArrayList* list, int initialCapacity) {
	list->capacity = initialCapacity;
	list->size = 0;
	list->content = malloc(sizeof(int) * initialCapacity);
}

void Add(ArrayList* list, int value) {

	if (list == NULL) {
		printf("[ERROR] list is null\n");
		return;
	}

	// TODO: resize content
	if (list->size == list->capacity) {
		printf("[ERROR] resizable array not implemented\n");
		return;
	}

	list->content[list->size] = value;
	list->size++;

}

int Get(ArrayList* list, int index, int* value) {

	if (list == NULL) {
		printf("[ERROR] list is null\n");
		return -1;
	}

	if (index >= list->size) {
		printf("[ERROR] index is out of bounds [%d] >= [%d]\n", index, list->size);
		return -1;
	}

	*value = list->content[index];

	return 0;

}















