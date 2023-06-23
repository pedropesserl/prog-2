CFLAGS = -g -Wall -Wextra

all: backup

backup: backup.o
	gcc -o backup backup.o

backup.o:
	gcc -c backup.c $(CFLAGS)

clean:
	rm *.o

purge:
	rm *.o backup
