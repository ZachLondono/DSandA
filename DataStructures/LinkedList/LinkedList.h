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

void Add(LinkedList* list, void* value, size_t size);

void* GetValue(LinkedList* list, int index);

void SetValue(LinkedList* list, void* value, size_t size, int index);

void Free(LinkedList* list);

#endif
