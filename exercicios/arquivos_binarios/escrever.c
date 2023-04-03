#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000000

#define USAGE_EXIT(err) do {                                   \
        fprintf(stderr, "Uso: ./escrever <arquivo>\n");        \
        exit(err);                                             \
    } while (0)                                                
                                                               
#define FOPEN_ERR_EXIT(arq, err) do {                          \
        fprintf(stderr, "erro ao abrir arquivo %s.\n", arq);   \
        exit(err);                                             \
    } while (0)

int main(int argc, char **argv) {
    srand(time(0));

    if (argc != 2)
        USAGE_EXIT(1);

        const char *filename = argv[1];

    FILE *out;

    out = fopen(filename, "ab");

    if (!out)
        FOPEN_ERR_EXIT(filename, 1);

    long *vetor;
    vetor = malloc(MAX * sizeof(long));

    long n;
    long i;
    for (i = 0; i < MAX; i++) {
        n = rand();
        vetor[i] = n;
    }

    fwrite(vetor, sizeof(long), MAX, out);

    fclose(out);

    return 0;
}
