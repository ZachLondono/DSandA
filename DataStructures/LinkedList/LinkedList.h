#ifndef LINKED_LIST
#define LINKED_LIST
#include <stdlib.h>

typedef struct _Node {
	void* value;
	size_t size;
	struct _Node* next;
} Node;

typedef struct _LinkedList {
	Node* head;
	int size;
} LinkedList;

void ll_add(LinkedList* list, void* value, size_t size);

void* ll_getvalue(LinkedList* list, int index);

void ll_setvalue(LinkedList* list, void* value, size_t size, int index);

void ll_free(LinkedList* list);

#endif
