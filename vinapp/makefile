CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = vinapp.o libbin.o libarchiver.o insert.o content.o remove.o move.o
DEPS = libbin.h libarchive.h insert.h content.h remove.h move.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: vina++

vina++: $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJ) vina++
