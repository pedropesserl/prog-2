CFLAGS = -Wall -Wextra

all: vinapp

vinapp: vinapp.o
	gcc $(CFLAGS) -o vina++ vinapp.o

vinapp.o: vinapp.c
	gcc -c vinapp.c

clean:
	rm -rf *.o vina++
