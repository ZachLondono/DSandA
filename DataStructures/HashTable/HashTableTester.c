#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _Thing {
	char* value;
} Thing;

void IntegerTableTest();
void StructTableTest();
static bool CompareInts(void* a, void* b) {

	int intA = *(int*)a;
	int intB = *(int*)b;

	printf("Comparing key '%d' to key '%d'\n", intA, intB);

	return intA == intB;
	
}

int main() {
	IntegerTableTest();
	StructTableTest();
}

void StructTableTest() {

	HashTable table;
	ht_initilize(&table);
	table.are_equal = &CompareInts;

	int key_1 = 1;
	Thing thing_1;
	thing_1.value = malloc(sizeof(char) * 6);
	strcpy(thing_1.value, "Hello\0");

	int key_2 = 2;
	Thing thing_2;
	thing_2.value = malloc(sizeof(char) * 6);
	strcpy(thing_2.value, "World\0");
	
	ht_put(table, &key_1, sizeof(int), &thing_1, sizeof(Thing*));
	ht_put(table, &key_2, sizeof(int), &thing_2, sizeof(Thing*));

	Thing* value_1 = ht_get(table, &key_1);
	if (value_1 != NULL) printf("check1: '%s' == '%s' \n", thing_1.value, value_1->value);
	Thing* value_2 = ht_get(table, &key_1);
	if (value_1 != NULL) printf("check2: '%s' == '%s' \n", thing_2.value, value_2->value);
	
	ht_free(table);	

}

void IntegerTableTest() {

	HashTable table;
	ht_initilize(&table);
	table.are_equal = &CompareInts;

	int key = 1;
	int value = 101;
	printf("Putting value '%d' into key '%d'\n", value, key);
	ht_put(table, &key, sizeof(int), &value, sizeof(int));

	bool containsKey = ht_containskey(table, &key);
	printf("Checking for key '%d': %s\n", key, containsKey ? "true" : "false");

	int* read_value = (int*) ht_get(table, &key);
	printf("Value stored in key '%d' : %d\n", key, *read_value);
	
	int key2 = 2;
	int value2 = 202;
	printf("Putting value '%d' into key '%d'\n", value2, key2);
	ht_put(table, &key2, sizeof(int), &value2, sizeof(int));

	printf("Removing value with key '%d'\n", key2);
	ht_remove(table, &key2);

	containsKey = ht_containskey(table, &key2);
	printf("Checking for key '%d': %s\n", key2, containsKey ? "true" : "false");

	int* invalid = ht_get(table, &key2);
	if (invalid != NULL)
		printf("You shouldn't see this%d\n", *invalid);
	
	int key3 = 2;
	int value3 = 202;
	printf("Putting value '%d' into key '%d'\n", value3, key3);
	ht_put(table, &key3, sizeof(int), &value3, sizeof(int));

	int key4 = 2;
	int value4 = 202;
	printf("Putting value '%d' into key '%d'\n", value4, key4);
	ht_put(table, &key4, sizeof(int), &value4, sizeof(int));

	ht_free(table);	

}
