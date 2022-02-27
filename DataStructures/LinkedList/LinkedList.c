#include "LinkedList.h"
#include <stdio.h>
#include <string.h>

static Node* CreateNode() {
	Node* node = malloc(sizeof(Node));
	node->value = NULL;
	node->next = NULL;
	return node;
}

static void SetValue(Node* node, void* value, size_t size) {
	node->value = malloc(size);
	memcpy(node->value, value, size);
	node->size = size;
}

void Add(LinkedList* list, void* value, size_t size) {

	if (list == NULL) {
		printf("[WARNING] list is null");
		return;
	}
	
	if (list->head == NULL) {
		list->head =  CreateNode();
		SetValue(list->head, value, size);
		list->size++;
		return;
	}

	Node* currNode = list->head;
	while (1) {
		if (currNode->next != NULL) {
			currNode = currNode->next;
			continue;
		}

		currNode->next = CreateNode();
		currNode = currNode->next;
		SetValue(currNode, value, size);
		list->size++;
		break;
	}

}

void* GetValue(LinkedList* list, int index) {

	if (list == NULL || list->head == NULL) {
		printf("[WARNING] list is null or has not been initilized");
		return NULL;
	}

	int i = 0;
	Node* currNode = list->head;
	while (currNode != NULL) {

		if (i == index) 
			return currNode->value;

		currNode = currNode->next;
		i++;

	}

	return NULL;

}

static void FreeNode(Node* node) {

	if (node->next != NULL)
		FreeNode(node->next);

	void* value = node->value;
	free(value);
	free(node);

}

void Free(LinkedList* list) {
	if (list->head == NULL) return;
	FreeNode(list->head);
}







