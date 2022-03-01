all:
	gcc -g -Wall -Wextra -c LinkedList.c -o ./bin/linkedlist.o
	(cd ./bin && ar rcs liblinkedlist.a linkedlist.o)

test:
	gcc LinkedListTester.c -o ./tests/tester -L./bin -llinkedlist

runtest: 
	./tests/tester

clean:
	(cd ./bin && rm ./linkedlist.o && rm ./liblinkedlist.a)
	(rm ./tests/tester)

profile:
	valgrind --leak-check=full -s ./tests/tester
