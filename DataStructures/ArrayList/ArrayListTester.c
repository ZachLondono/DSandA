#include "ArrayList.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

	ArrayList list;

	Initilize(&list, 2);

	printf("Is list empty: %s\n", IsEmpty(&list) ? "true": "false");

	Add(&list, 1);
	Add(&list, 2);
	Add(&list, 3);

	printf("Is list empty: %s\n", IsEmpty(&list) ? "true": "false");

	int i = 0;
	for (i = 0; i < 3; i++) {
		int value = -1;
		int ret = Get(&list, i, &value);

		if (ret >= 0)
			printf("%d -> %d\n", i, value);
		else printf("Error reading from arraylist\n");
	}

	Free(&list);

}
