all: OS.c list.h list.o
	gcc -pthread -o os OS.c list.h list.o -I .

clean:
	rm -rf ./a.out os list.h.gch
