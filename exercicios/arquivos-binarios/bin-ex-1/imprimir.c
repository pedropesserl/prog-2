/* c. escrever na tela os primeiros 10 números e os últimos 10 números contidos no arquivo. */

#include <stdio.h>
#include <stdlib.h>

#define USAGE_EXIT(err) do {                                           \
        fprintf(stderr, "Uso: ./imprimir <arquivo>\n");                \
        exit(err);                                                     \
    } while (0)

#define FOPEN_ERR_EXIT(arq, err) do {                                  \
        fprintf(stderr, "Erro ao abrir/escrever arquivo %s.\n", arq);  \
        exit(err);                                                     \
    } while (0)

int main(int argc, char **argv) {
    if (argc != 2)
        USAGE_EXIT(1);

    const char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    
    long vetor[10];

    long n, i;
    for (i = 0; i < 10; i++) {
        fread(&n, sizeof(long), 1, file);
        vetor[i] = n;
    }

    printf("Primeiros 10 números: ");
    for (i = 0; i < 10; i++) {
        printf("%ld ", vetor[i]);
    }
    printf("\n");

    fseek(file, -10 * (sizeof(long)), SEEK_END);

    for (i = 0; i < 10; i++) {
        fread(&n, sizeof(long), 1, file);
        vetor[i] = n;
    }

    printf("Últimos 10 números: ");
    for (i = 0; i < 10; i++) {
        printf("%ld ", vetor[i]);
    }
    printf("\n");

    return 0;
}
