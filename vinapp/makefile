CFLAGS = -Wall -Wextra
OBJ = vinapp.o
DEPS =

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

all: vina++

vina++: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ) vina++
