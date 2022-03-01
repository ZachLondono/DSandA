#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int BUCKET_COUNT = 10;

static int Hash(void* key) {
	int hashcode = 1;
	printf("[INFO] hashed '%p' to '%d'\n", key, hashcode);
	return hashcode;
}

static bool CompareInts(void* a, void* b) {

	int intA = *(int*)a;
	int intB = *(int*)b;

	printf("Comparing key '%d' to key '%d'\n", intA, intB);

	return intA == intB;
	
}

static void FreeKVPair(void* value) {
	KeyValuePair* pair = value;
	if (pair != NULL) {
		printf("Try to '%p' & '%p'\n", pair->key, pair->value);
		free(pair->key);
		free(pair->value);
	}
}

int main() {

	HashTable table;
	ht_initilize(&table);
	table.are_equal = &CompareInts;

	int key = 1;
	int value = 101;
	printf("Putting value '%d' into key '%d'\n", value, key);
	ht_put(table, key, value);

	bool containsKey = ht_containskey(table, key);
	printf("Checking for key '%d': %s\n", key, containsKey ? "true" : "false");

	int* read_value = (int*) ht_get(table,key);
	printf("Value stored in key '%d' : %d\n", key, *read_value);
	
	int key2 = 2;
	int value2 = 202;
	printf("Putting value '%d' into key '%d'\n", value2, key2);
	ht_put(table, key2, value2);

	printf("Removing value with key '%d'\n", key2);
	ht_remove(table, key2);

	containsKey = ht_containskey(table, key2);
	printf("Checking for key '%d': %s\n", key2, containsKey ? "true" : "false");

	int* invalid = ht_get(table, key2);
	if (invalid != NULL)
		printf("You shouldn't see this%d\n", *invalid);
	
	int key3 = 2;
	int value3 = 202;
	printf("Putting value '%d' into key '%d'\n", value3, key3);
	ht_put(table, key3, value3);

	int key4 = 2;
	int value4 = 202;
	printf("Putting value '%d' into key '%d'\n", value4, key4);
	ht_put(table, key4, value4);

	ht_free(table);	

}

void ht_initilize(HashTable* table) {
	table->bucket_count = BUCKET_COUNT;
	table->buckets = calloc(BUCKET_COUNT,sizeof(LinkedList*));
	table->are_equal = NULL;
}

KeyValuePair* ht_get_kvpair(HashTable table, int key) {
	if(table.buckets == NULL) {
		printf("[WARNING] table not initilized");
		return NULL;
	}

	int index = Hash(&key);

	if (index >= BUCKET_COUNT) {
		printf("[ERROR] invalid hash index\n");
		return NULL;
	}

	LinkedList* bucket = table.buckets[index];

	if (bucket == NULL) return NULL;

	Node* currNode = bucket->head;
	while (1) {

		if (currNode == NULL) return NULL;
	
		KeyValuePair* pair = (KeyValuePair*) currNode->value;

		currNode = currNode->next;

		if (pair == NULL) continue;

		if (table.are_equal == NULL) {
			if (&key == pair->key) return pair;
		} else if (table.are_equal(&key,pair->key)) 
			return pair;

	}

	return NULL;

}

bool ht_containskey(HashTable table, int key) {
	return ht_get_kvpair(table, key) != NULL;
}

void* ht_get (HashTable table, int key) {
	KeyValuePair* pair = ht_get_kvpair(table, key);
	if (pair == NULL) return NULL;
	return pair->value;
}

static LinkedList* ht_get_bucket(HashTable table, int key) {
	if (table.buckets == NULL) {
		printf("[ERROR] table not initilized\n");
		return NULL;
	}

	int index = Hash(&key);

	if (index >= BUCKET_COUNT) {
		printf("[ERROR] invalid hash index\n");
		return NULL;
	}
	
	LinkedList* bucket = table.buckets[index];

	if (bucket == NULL) {
		table.buckets[index] = malloc(sizeof(LinkedList));
		bucket = table.buckets[index];
		ll_initilize(table.buckets[index]);	
		table.buckets[index]->free_contents = FreeKVPair;
	}

	return bucket;

}

static void ht_removeNode(LinkedList bucket, int index, KeyValuePair* pair) {
	free(pair->value);
	pair->value = NULL;
	free(pair->key);
	pair->key = NULL;
	ll_remove(bucket, index);
}

void ht_remove(HashTable table, int key) {

	printf("removing\n");
	LinkedList* bucket = ht_get_bucket(table, key);
	
	int index = 0;
	Node* currNode = bucket->head;
	while (1) {

		if (currNode == NULL) return;
	
		KeyValuePair* pair = (KeyValuePair*) currNode->value;

		if (pair == NULL) {
			currNode = currNode->next;
			index++;
			continue;
		}

		if (table.are_equal == NULL && &key == pair->key) {
			ht_removeNode(*bucket, index, pair);
			return;
		} else if (table.are_equal(&key,pair->key)) {
			ht_removeNode(*bucket, index, pair);
			return;
		}

		currNode = currNode->next;
		index++;
	}
}

void CreateKVPair(KeyValuePair* pair, void* key, size_t keySize, void* value, size_t valueSize) {
	pair->key = malloc(keySize);	
	memcpy(pair->key, key, keySize);
	pair->value = malloc(valueSize);
	memcpy(pair->value, value, valueSize);
}

int ht_put(HashTable table, int key, int value) {

	LinkedList* bucket = ht_get_bucket(table, key);

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
				ll_free(bucket);
				free(bucket);
				bucket = NULL;
			}

			printf("free\n");
		}

		free(table.buckets);
		table.buckets = NULL;

	}
}












