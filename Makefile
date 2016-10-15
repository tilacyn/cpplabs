all: Lab5

Lab5: bin/main.o bin/clist.o bin/position.o
	gcc -g bin/main.o bin/clist.o bin/position.o -o Lab5

bin/main.o: main.c clist.h position.h
	gcc -g -c main.c -o bin/main.o

bin/position.o: position.c position.h clist.h
	gcc -g -c position.c -o bin/position.o

bin/clist.o: clist.c clist.h
	gcc -g -c clist.c -o bin/clist.o

clean:
	rm -rf bin/*.o Lab5

