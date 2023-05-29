CFLAGS = -Wall -Wextra -g
	OBJ = ler_bytes.o

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

all: ler_bytes

ler_bytes: ler_bytes.o
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ)

purge:
	rm -rf $(OBJ) ler_bytes out.bin
