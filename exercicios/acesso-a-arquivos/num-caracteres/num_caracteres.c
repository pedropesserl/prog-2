/* Escreva um programa em C para informar o número de caracteres presentes em um arquivo de texto. */

#include <stdio.h>
#include <stdlib.h>

#define USAGE_EXIT(err) do {                                    \
        fprintf(stderr, "Uso: ./num_caracteres <arquivo>\n");   \
        exit(err);                                              \
    } while (0)

#define FILE_ERR_EXIT(arq, err) do {                            \
        fprintf(stderr, "Erro ao abrir arquivo %s\n", arq);     \
        exit(err);                                              \
    } while (0)


int main(int argc, char **argv) {
    if (argc != 2)
        USAGE_EXIT(1);

    FILE *arq;
    const char *filename = argv[1];
    arq = fopen(filename, "r");

    if (!arq)
        FILE_ERR_EXIT(filename, 1);

    long n = 0;
    char c;

    c = fgetc(arq);
    while (c != EOF) {
        n++;
        c = fgetc(arq);
    }

    printf("O arquivo %s tem %ld caracteres.\n", filename, n);
    
    fclose(arq);
    return 0;
}
