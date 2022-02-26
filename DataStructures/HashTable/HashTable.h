#ifndef HASH_TABLE 
#define HASH_TABLE 
#include <stdbool.h>

typedef struct _HashTable {

} HashTable;

void Initilize(HashTable* table);

bool ContainsKey(HashTable* table, int key);

int Get(HashTable* table, int key);

int Put(HashTable* table, int key, int value);

void Remove(HashTable* table, int key);

int Size(HashTable* table);

void Clear(HashTable* table);

void Free(HashTable* table);

#endif
