# simple makefile

all: clean main

main: field.o main.o
	gcc main.o field.o -o main -lncurses
main.o:
	gcc -c main.c -o main.o
field.o:
	gcc -c field.c -o field.o
clean:
	rm -rf *.o main
