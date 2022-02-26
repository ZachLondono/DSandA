#include "ArrayList.h"
#include <stdlib.h>
#include <stdio.h>

void Initilize(ArrayList* list, int initialCapacity) {
	list->capacity = initialCapacity;
	list->size = 0;
	list->content = malloc(sizeof(int) * initialCapacity);
}

static int ResizeList(ArrayList* list, int new_capacity) {

	if (list == NULL) {
		printf("[ERROR] list is null\n");
		return -1;
	}

	if (new_capacity <= 0) {
		printf("[WANRING] invalid capacity\n");
		return -1;
	}

	printf("[INFO] resizing list content\n");
	int* new_content;
	new_content = realloc(list->content, new_capacity);
	if (new_content == NULL) {
		printf("[ERROR] could not allocate more memory for content\n");
		return -1;
	}
	list->content = new_content;
	list->capacity = new_capacity;
	return 0;
}

void Add(ArrayList* list, int value) {

	printf("Adding value '%d'\n", value);

	if (list == NULL) {
		printf("[ERROR] list is null\n");
		return;
	}

	if (list->size == list->capacity) {
		int new_capacity = sizeof(int) * list->capacity * 2;
		if (ResizeList(list, new_capacity) < 0) return;
	}

	int index = list->size;
	list->content[index] = value;
	list->size++;

	printf("value added\n");

}



void InsertAt(ArrayList* list, int value, int index) {

	// if the list is at capacity, it needs to be resized
	// then shift all values that are greater than index over to the next index
	// only need to shift values at indecies from index to size

	printf("Inserting value '%d' into position '%d'\n", value, index);

	if (list == NULL) {
		printf("[ERROR] list is null\n");
		return;
	}

	if (index < 0 || index > list->size) {
		printf("[ERROR] invalid index '%d' for array size '%d'\n", index, list->size);
		return;
	}

	if (list->size == list->capacity) {
		int new_capacity = sizeof(int) * list->capacity * 2;
		if (ResizeList(list, new_capacity) < 0) return;
	}

	int i = 0;
	for (i = list->size + 1; i > index; i--) {
		printf("moving value at '%d' to '%d'\n", i-1, i);
		list->content[i] = list->content[i - 1];
	}

	list->content[index] = value;

	list->size++;

	printf("Value inserted\n");

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

int IndexOf(ArrayList* list, int value) {

	int i = 0;
	for (i = 0; i < list->size; i++) {
		if (list->content[i] == value)
			return i;
	}

	return -1;	

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

