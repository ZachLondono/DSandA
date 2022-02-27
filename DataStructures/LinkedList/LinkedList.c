#include "LinkedList.h"
#include <stdio.h>
#include <string.h>

static Node* CreateNode() {
	Node* node = malloc(sizeof(Node));
	node->value = NULL;
	node->next = NULL;
	return node;
}

static void SetNodeValue(Node* node, void* value, size_t size) {
	if (node->value != NULL) free(node->value);
	node->value = malloc(size);
	memcpy(node->value, value, size);
	node->size = size;
}

void Add(LinkedList* list, void* value, size_t size) {

	if (list == NULL) {
		printf("[WARNING] list is null\n");
		return;
	}
	
	if (list->head == NULL) {
		list->head =  CreateNode();
		SetNodeValue(list->head, value, size);
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
		SetNodeValue(currNode, value, size);
		list->size++;
		break;
	}

}

void* GetValue(LinkedList* list, int index) {

	if (list == NULL || list->head == NULL) {
		printf("[WARNING] list is null or has not been initilized\n");
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

void SetValue(LinkedList* list, void* value, size_t size, int index) {

	if (list->size <= index) {
		printf("[ERROR] invalid index\n");
		return;
	}

	if (list == NULL) {
		printf("[WARNING] list is null\n");
		return;
	}
	
	if (list->head == NULL) {
		printf("[WARNING] list contains no values\n");
		return;
	}

	int i = 0;
	Node* currNode = list->head;
	while (1) {

		if (i == index) {
			SetNodeValue(currNode, value, size);
			return;
		}

		if (currNode->next == NULL) break;

		currNode = currNode->next;
		i++;
	}

	printf("[ERROR] invalid index\n");
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







