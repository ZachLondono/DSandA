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

static void FreeKVPair(void* value) {
	KeyValuePair* pair = value;
	if (pair != NULL) {
		if (pair->free_keycontent != NULL) 
			pair->free_keycontent(pair->key);
		free(pair->key);

		if (pair->free_valuecontent != NULL) 
			pair->free_valuecontent(pair->value);
		free(pair->value);
	}
}

void ht_initilize(HashTable* table) {
	table->bucket_count = BUCKET_COUNT;
	table->buckets = calloc(BUCKET_COUNT,sizeof(LinkedList*));
	table->are_equal = NULL;
}

static KeyValuePair* ht_get_kvpair(HashTable table, void* key) {
	if(table.buckets == NULL) {
		printf("[WARNING] table not initilized");
		return NULL;
	}

	int index = Hash(key);
	printf("Hashed key to index '%d'\n", index);

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
			if (key == pair->key) return pair;
		} else if (table.are_equal(key,pair->key)) 
			return pair;

	}

	return NULL;
}


bool ht_containskey(HashTable table, void* key) {
	return ht_get_kvpair(table, key) != NULL;
}

void* ht_get(HashTable table, void* key) {
	KeyValuePair* pair = ht_get_kvpair(table, key);
	if (pair == NULL) return NULL;
	return pair->value;
}

LinkedList* ht_get_bucket(HashTable table, void* key) {
	if (table.buckets == NULL) {
		printf("[ERROR] table not initilized\n");
		return NULL;
	}

	int index = Hash(key);

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

void ht_removeNode(LinkedList bucket, int index, KeyValuePair* pair) {
	free(pair->value);
	pair->value = NULL;
	free(pair->key);
	pair->key = NULL;
	ll_remove(bucket, index);
}

void ht_remove(HashTable table, void* key) {

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

		if (table.are_equal == NULL && key == pair->key) {
			ht_removeNode(*bucket, index, pair);
			return;
		} else if (table.are_equal(key,pair->key)) {
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
	pair->free_keycontent = NULL;
	pair->free_valuecontent = NULL;
}

int ht_put(HashTable table, void* key, size_t keySize, void* value, size_t valueSize) {

	LinkedList* bucket = ht_get_bucket(table, key);

	KeyValuePair pair;
	CreateKVPair(&pair, 
			key,
			keySize,
			value,
			valueSize);

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

