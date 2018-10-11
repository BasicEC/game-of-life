CC=gcc
IDIR=./include
BDIR=./build
TARGET=main
CFLAGS=-Wall -I $(IDIR)
SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=build/%.o)

mainmake: mkbuild $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) -lncurses -pthread

build/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

rebuild: clean mkbuild mainmake

mkbuild:
	mkdir -p build

clean:
	rm -rf build main
