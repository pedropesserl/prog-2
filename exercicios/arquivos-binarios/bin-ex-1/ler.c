/* b. ler o arquivo de inteiros em um vetor, ordenar o vetor e reescrever o arquivo; */

#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"

#define MAX 10000000

#define USAGE_EXIT(err) do {                                           \
        fprintf(stderr, "Uso: ./ler <arquivo>\n");                     \
        exit(err);                                                     \
    } while (0)

#define FILE_ERR_EXIT(arq, err) do {                                   \
        fprintf(stderr, "Erro ao abrir/escrever arquivo %s.\n", arq);  \
        exit(err);                                                     \
    } while (0)

#define MEM_ERR_EXIT(err) do {                                         \
        fprintf(stderr, "Erro COMPRA MAIS RAM\n");                     \
        exit(err);                                                     \
    } while (0)

int main(int argc, char **argv) {
    if (argc != 2)
        USAGE_EXIT(1);

    const char *filename = argv[1];
    FILE *file;
    file = fopen(filename, "rb+");
    if (!file)
        FILE_ERR_EXIT(filename, 1);

    long *vetor = (long*)malloc((MAX + 100) * sizeof(long));
    if (!vetor)
        MEM_ERR_EXIT(1);

    long n, i = 1;
    fread(&n, sizeof(long), 1, file);
    vetor[0] = n;

    while (!feof(file)) {
        fread(&n, sizeof(long), 1, file);
        vetor[i++] = n;
    }

    quicksort(vetor, MAX);

    rewind(file);

    int ret = fwrite(vetor, sizeof(long), MAX, file);
    if (!ret)
        FILE_ERR_EXIT(filename, 2);

    free(vetor);
    fclose(file);

    return 0;
}
