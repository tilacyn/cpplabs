all: Lab4

Lab4: bin/ms_cli.o bin/mergesort.o
	gcc bin/ms_cli.o bin/mergesort.o -o Lab4

bin/ms_cli.o: ms_cli.c mergesort.h
	gcc -c ms_cli.c -o bin/ms_cli.o

bin/mergesort.o: mergesort.c mergesort.h
	gcc -c mergesort.c -o bin/mergesort.o

clean:
	rm -rf bin/*.o Lab4

