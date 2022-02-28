#ifndef HASH_TABLE 
#define HASH_TABLE 
#include "LinkedList.h"
#include <stdbool.h>

typedef struct _KeyValuePair {
	void* key;
	void* value;
} KeyValuePair;

typedef struct _HashTable {
	int bucket_count;
	LinkedList** buckets;
	bool (*are_equal)(void*, void*);
} HashTable;

void ht_initilize(HashTable* table);

bool ht_containskey(HashTable table, int key);

void* ht_get(HashTable table, int key);

int ht_put(HashTable table, int key, int value);

void ht_remove(HashTable table, int key);

int ht_size(HashTable table);

void ht_clear(HashTable* table);

void ht_free(HashTable table);

#endif
