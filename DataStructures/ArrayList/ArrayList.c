#include "ArrayList.h"
#include <stdlib.h>
#include <stdio.h>

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

	printf("size:%d, cap:%d\n", list->size, list->capacity);
	if (list->size == list->capacity) {
		printf("[INFO] resizing list content\n");
		int new_capacity = sizeof(int) * list->capacity * 2;
		int* new_content;
		new_content = realloc(list->content, new_capacity);
		if (new_content == NULL) {
			printf("[ERROR] could not allocate more memory for content\n");
			return;
		}
		list->content = new_content;
		list->capacity = new_capacity;
	}

	int index = list->size;
	list->content[index] = value;
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

bool IsEmpty(ArrayList* list) {
	return list->size == 0;
}

int Size(ArrayList* list) {
	return list->size;
}

void Free(ArrayList* list) {

	free(list->content);

}

