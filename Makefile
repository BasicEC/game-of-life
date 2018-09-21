CC=gcc
IDIR=./include
BDIR=./build
CFLAGS=-Wall -I$(IDIR)
TARGET=main
SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=build/%.o)

mainmake: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

build/%.o: src/%.c
	$(CC) -c -g -o $@ $< $(CFLAGS)

clean:
	rm $(BDIR)/*