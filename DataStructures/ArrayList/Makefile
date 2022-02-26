all:
	gcc -g -Wall -Wextra -c ArrayList.c -o ./bin/arraylist.o
	(cd ./bin && ar rcs libarraylist.a arraylist.o)

test:
	gcc ArrayListTester.c -o ./tests/tester -L./bin -larraylist

runtest: 
	./tests/tester

clean:
	(cd ./bin && rm ./arraylist.o && rm ./libarraylist.a)
	(rm ./tests/tester)

profile:
	valgrind ./tests/tester
