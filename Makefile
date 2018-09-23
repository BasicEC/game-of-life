CC=gcc
IDIR=./include
BDIR=./build
TARGET=main
CFLAGS=-Wall -I $(IDIR)
SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=build/%.o)

mainmake: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) -lncurses

build/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

rebuild: clean mkbuild mainmake

mkbuild:
	mkdir build 
	
clean:
	rm -rf build main
