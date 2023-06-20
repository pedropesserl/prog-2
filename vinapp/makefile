CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = vinapp.o libbin.o libarchiver.o insert_append.o
DEPS = libbin.h libarchive.h insert_append.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: vina++

vina++: $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJ) vina++ teste_insert.o
