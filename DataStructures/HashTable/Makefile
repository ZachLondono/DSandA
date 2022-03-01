all:
	gcc -g -Wall -Werror -Wextra -c HashTable.c -o ./bin/hashtable.o -L./bin -llinkedlist
	(cd ./bin && ar rcs libhashtable.a hashtable.o)

test:
	gcc -g HashTableTester.c -o ./tests/tester -L./bin -lhashtable -llinkedlist

runtest:
	./tests/tester

debug:
	gdb ./tests/tester

clean:
	(cd ./bin && rm ./hashtable.o && rm ./libhashtable.a)
	(rm ./tests/tester)

profile:
	valgrind --leak-check=full -s ./tests/tester
