#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int BUCKET_COUNT = 10;

static int Hash(void* key) {
//	time_t t;
//	srand((unsigned) time(&t));
//	int hashcode = rand() % BUCKET_COUNT;
	int hashcode = 1;
	printf("[INFO] hashed '%p' to '%d'\n", key, hashcode);
	return hashcode;
}

int main() {

	HashTable table;
	ht_initilize(&table);

	int key = 1;
	int value = 101;
	ht_put(&table, key, value);
	
	LinkedList* bucket = table.buckets[1];
	printf("Values in bucket index '1': %d\n", bucket->size);
	KeyValuePair* pair = (KeyValuePair*) ll_getvalue(bucket, 0);

	int* p_key = ((int*)pair->key);
	printf("key: %d\n", *p_key);

	int* p_value = ((int*)pair->value);
	printf("value: %d\n", *p_value);

	ht_free(table);	

}

void ht_initilize(HashTable* table) {
	table->bucket_count = BUCKET_COUNT;
	table->buckets = calloc(BUCKET_COUNT,sizeof(LinkedList*));
	table->are_equal = NULL;
}

void CreateKVPair(KeyValuePair* pair, void* key, size_t keySize, void* value, size_t valueSize) {
	pair->key = malloc(keySize);	
	memcpy(pair->key, key, keySize);
	pair->value = malloc(valueSize);
	memcpy(pair->value, value, valueSize);
}

int ht_put(HashTable* table, int key, int value) {

	if (table->buckets == NULL) {
		printf("[ERROR] table not initilized\n");
		return -1;
	}

	int index = Hash(&key);

	if (index >= BUCKET_COUNT) {
		printf("[ERROR] invalid hash index\n");
		return -1;
	}
	
	LinkedList* bucket = table->buckets[index];

	if (bucket == NULL) {
		table->buckets[index] = malloc(sizeof(LinkedList));
		bucket = table->buckets[index];
		bucket->head = NULL;
		bucket->size = 0;
	}

	KeyValuePair pair;
	CreateKVPair(&pair, 
			&key,
			sizeof(int),
			&value,
			sizeof(int));

	ll_add(bucket, &pair, sizeof(KeyValuePair));

	return 0;

}

void ht_free(HashTable table) {

	if (table.buckets != NULL) {

		printf("Freeing buckets\n");
		int i = 0;
		for (i = 0; i < table.bucket_count; i++) {
			printf("Bucket '%d'... ",i);
			LinkedList* bucket = table.buckets[i];
			
			if (bucket != NULL) {
				Node* currNode = bucket->head;
				while (currNode != NULL) {
					KeyValuePair* pair = currNode->value;
					if (pair != NULL) {
						if (pair->key != NULL) free(pair->key);
						if (pair->value != NULL) free(pair->value);
					}
					currNode = currNode->next;
				}

				ll_free(bucket);
				free(bucket);
			}

			printf("free\n");
		}

		free(table.buckets);

	}

	if (table.are_equal != NULL) {
		printf("Freeing equal func\n");
		free(table.are_equal);
	}

}












