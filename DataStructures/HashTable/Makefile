all:
	gcc -g -Wall -Werror -Wextra HashTable.c -o hashtable.o -L./bin -llinkedlist

run:
	./hashtable.o

profile:
	valgrind --leak-check=full -s ./hashtable.o
