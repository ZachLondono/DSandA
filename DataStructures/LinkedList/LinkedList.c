#include "LinkedList.h"
#include <stdio.h>
#include <string.h>

void ll_initilize(LinkedList* list) {
	list->head = NULL;
	list->size = 0;
	list->free_contents = NULL;
}

static Node* ll_createnode() {
	Node* node = malloc(sizeof(Node));
	node->value = NULL;
	node->next = NULL;
	return node;
}

static void ll_setnodevalue(Node* node, void* value, size_t size) {
	if (node->value != NULL) free(node->value);
	node->value = malloc(size);
	memcpy(node->value, value, size);
	node->size = size;
}

void ll_add(LinkedList* list, void* value, size_t size) {

	if (list == NULL) {
		printf("[WARNING] list is null\n");
		return;
	}
	
	if (list->head == NULL) {
		list->head =  ll_createnode();
		ll_setnodevalue(list->head, value, size);
		list->size++;
		return;
	}

	Node* currNode = list->head;
	while (1) {
		if (currNode->next != NULL) {
			currNode = currNode->next;
			continue;
		}

		currNode->next = ll_createnode();
		currNode = currNode->next;
		ll_setnodevalue(currNode, value, size);
		list->size++;
		break;
	}

}

void* ll_getvalue(LinkedList list, int index) {

	if (list.head == NULL) {
		printf("[WARNING] list is null or has not been initilized\n");
		return NULL;
	}

	int i = 0;
	Node* currNode = list.head;
	while (currNode != NULL) {

		if (i == index) 
			return currNode->value;

		currNode = currNode->next;
		i++;

	}

	return NULL;

}

void ll_setvalue(LinkedList list, void* value, size_t size, int index) {

	if (list.size <= index) {
		printf("[ERROR] invalid index\n");
		return;
	}
	
	if (list.head == NULL) {
		printf("[WARNING] list contains no values\n");
		return;
	}

	int i = 0;
	Node* currNode = list.head;
	while (1) {

		if (i == index) {
			ll_setnodevalue(currNode, value, size);
			return;
		}

		if (currNode->next == NULL) break;

		currNode = currNode->next;
		i++;
	}

	printf("[ERROR] invalid index\n");
}

static void ll_freenode(Node* node, void (*free_contents)(void*)) {
	printf("Freeing node\n");
	void* value = node->value;
	if (free_contents != NULL) {
		printf("Freeing content\n");
		free_contents(value);
	}
	free(value);
	free(node);
	printf("Node freed\n");
}

void ll_remove(LinkedList list, int index) {

	int currIndex = 0;
	Node* currNode = list.head;
	Node* prevNode = NULL;
	while (currNode != NULL) {
		
		if (currIndex != index)  {
			prevNode = currNode;
			currNode = currNode->next;
			currIndex++;
			continue;
		}

		if (prevNode == NULL) list.head = currNode->next;
		else  prevNode->next = currNode->next;
		ll_freenode(currNode, list.free_contents);
		list.size--;
		return;
				
	}

}

void ll_free(LinkedList* list) {
	if (list->head == NULL) return;
	Node* currNode = list->head;
	while (currNode != NULL) {
		Node* nextNode = currNode->next;
		ll_freenode(currNode, list->free_contents);
		currNode = nextNode;
	}
}







