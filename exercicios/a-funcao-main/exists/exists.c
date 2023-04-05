#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: ./exists <arquivo>");
        exit(2);
    }

    const char *filename = argv[1];
    FILE *file;
    file = fopen(filename, "r");

    return ((int)!file);
}
