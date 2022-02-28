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

bool ContainsKey(HashTable* table, int key);

int Get(HashTable* table, int key);

int ht_put(HashTable* table, int key, int value);

void Remove(HashTable* table, int key);

int Size(HashTable* table);

void Clear(HashTable* table);

void ht_free(HashTable table);

#endif
