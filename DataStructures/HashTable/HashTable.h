#ifndef HASH_TABLE 
#define HASH_TABLE 
#include "LinkedList.h"
#include <stdbool.h>

typedef struct _KeyValuePair {
	void* key;
	void* value;
	void (*free_keycontent)(void*);
	void (*free_valuecontent)(void*);
} KeyValuePair;

typedef struct _HashTable {
	int bucket_count;
	LinkedList** buckets;
	bool (*are_equal)(void*, void*);
} HashTable;

void ht_initilize(HashTable* table);

bool ht_containskey(HashTable table, void* key);

void* ht_get(HashTable table, void* key);

int ht_put(HashTable table, void* key, size_t keySize, void* value, size_t valueSize);

void ht_remove(HashTable table, void* key);

int ht_size(HashTable table);

void ht_clear(HashTable* table);

void ht_free(HashTable table);

#endif
