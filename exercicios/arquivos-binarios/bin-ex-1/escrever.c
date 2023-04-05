/* a. escrever um arquivo com 10 milhões de inteiros long aleatórios, armazenados em modo binário; */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000000

#define USAGE_EXIT(err) do {                                           \
        fprintf(stderr, "Uso: ./escrever <arquivo>\n");                \
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
    srand(time(0));

    if (argc != 2)
        USAGE_EXIT(1);

        const char *filename = argv[1];

    FILE *out;

    out = fopen(filename, "wb");

    if (!out)
        FILE_ERR_EXIT(filename, 1);

    long *vetor = (long*)malloc((MAX + 100) * sizeof(long));
    if (!vetor)
        MEM_ERR_EXIT(1);

    long n;
    long i;
    for (i = 0; i < MAX; i++) {
        n = rand();
        vetor[i] = n;
    }

    int ret = fwrite(vetor, sizeof(long), MAX, out);
    if (!ret)
        FILE_ERR_EXIT(filename, 2);

    free(vetor);
    fclose(out);

    return 0;
}
