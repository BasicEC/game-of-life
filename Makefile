# simple makefile

all: clean main

main: main.o
	gcc -o main main.o
main.o:
	gcc -c main.c -o main.o
clean:
	rm -rf *.o main
