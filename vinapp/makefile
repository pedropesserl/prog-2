CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = src/vinapp.o src/libbin.o src/libarchiver.o src/insert.o src/content.o src/remove.o src/move.o src/extract.o
DEPS = src/libbin.h src/libarchive.h src/insert.h src/content.h src/remove.h src/move.h src/extract.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: vina++

vina++: $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJ) vina++
