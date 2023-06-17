CFLAGS = -Wall -Wextra
OBJ = vinapp.o libbin.o libarchive.o insert_append.o
DEPS = libbin.h libarchive.h insert_append.h

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

all: vina++

vina++: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ) vina++
