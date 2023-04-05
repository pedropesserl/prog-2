#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int i, cont = 0;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-')
            cont++;
    }

    return cont;
}
