#include <stdio.h>
#include <stdlib.h>

#define USAGE_EXIT(err) do {                                           \
        fprintf(stderr, "Uso: ./poemabin <arquivo>\n");                \
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

typedef struct {
    int posicao;
    char letra;
} Par;

int main(int argc, char **argv) {
    if (argc != 2)
        USAGE_EXIT(1);

    const char *filename = argv[1];
    FILE *file;
    file = fopen(filename, "rb");

    Par par;

    char *poema = (char*)calloc(2048, sizeof(char));
    if (!poema)
        MEM_ERR_EXIT(1);

    fread(&par.posicao, sizeof(int), 1, file);
    fread(&par.letra, sizeof(char), 1, file);
    poema[par.posicao] = par.letra;
    while (!feof(file)) {
        fread(&par.posicao, sizeof(int), 1, file);
        fread(&par.letra, sizeof(char), 1, file);
        poema[par.posicao] = par.letra;
    }

    printf("O poema é:\n");
    printf("%s\n", poema);

    free(poema);
    fclose(file);

    return 0;
}
