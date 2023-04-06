#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2 || strcmp(argv[1], "minusc.txt") != 0) {
        fprintf(stderr, "Uso: ./capitalizar minusc.txt\n");
        exit(1);
    }

    FILE *input;
    input = fopen("minusc.txt", "r");
    if (!input) {
        fprintf(stderr, "Erro ao abrir arquivo minusc.txt.\n");
        exit(1);
    }

    FILE *output = fopen("maiusc.txt", "w");
    if (!output) {
        fprintf(stderr, "Erro ao criar arquivo maiusc.txt.\n");
        exit(1);
    }

    char c;
    c = fgetc(input);
    while (c != EOF) {
        if ('a' <= c && c <= 'z')
            c -= 32;
        fputc(c, output);
        c = fgetc(input);
    }
    
    fclose(input);
    fclose(output);
    
    return 0;
}
