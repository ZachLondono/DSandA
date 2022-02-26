#ifndef ARRAY_LIST
#define ARRAY_LIST
#include <stdbool.h>

typedef struct _ArrayList {
	int capacity;	// The current maximum capacity
	int size;	// The number of elements currently stored
	int* content;	// The elements of the list
} ArrayList;

void Initilize(ArrayList* list, int initialCapacity);

// Adds a value to the end of the list
void Add(ArrayList* list, int value);

// Inserts the value at the specified index
void InsertAt(ArrayList* list, int value, int index);

// Writes the value to the pointer 'value', returns a value less than 0 if the index is invalid
int Get(ArrayList* list, int index, int* value);

// Returns the index of the value in the array, -1 if the value does not exist
int IndexOf(ArrayList* list, int value);

// Returns true if there are no values stored in the array list
bool IsEmpty(ArrayList* list);

// Returns the number of entities currently stored in the array list
int Size(ArrayList* list);

void Free(ArrayList* list);

#endif	
