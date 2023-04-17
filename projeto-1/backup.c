#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE_EXIT(err) do {                                        \
        fprintf(stderr, "Uso: ./backup [-t]\n");                    \
        exit(err);                                                  \
    } while (0)                                             

#define FOPEN_ERR_EXIT(err, filename) do {                          \
        fprintf(stderr, "Erro ao abrir arquivo %s.\n", filename);   \
        exit(err);                                                  \
    } while (0)                                                     

#define OVERWRITE_EXIT(err, filename) do {                          \
        fprintf(stderr, "Erro: arquivo %s já existe.", filename);   \
        exit(err);                                                  \
    } while (0)

#define MEM_ERR_EXIT(err) do {                                      \
        fprintf(stderr, "Erro na alocação de memória.\n");          \
        exit(err);                                                  \
    } while (0)

#define MAX_NOME 100

struct reg {
    unsigned int tam;
    char nome[MAX_NOME];
    void *conteudo;
    size_t tam_conteudo;
};

struct reg *le_vetor_registros(FILE *bin, unsigned int n_registros) {
    struct reg *registros = (struct reg*)calloc(n_registros, sizeof(struct reg));
    if (!registros)
        return NULL;

    char c = '\0';
    size_t j = 0;
    size_t tam_nome = 0;
    for (size_t i = 0; i < n_registros; i++) {
        
        // ler tamanho do registro
        fread(&registros[i].tam, 1, sizeof(unsigned int), bin);

        // ler nome do arquivo
        /* registros[i].nome = (char*)calloc(MAX_NOME, sizeof(char)); */
        /* if (!registros[i].nome) */
        /*     return NULL; */
        fread(&c, 1, sizeof(char), bin);
        while (c != '\n') {
            registros[i].nome[j++] = c;
            fread(&c, 1, sizeof(char), bin);
        }
        tam_nome = j + 1; // tamanho do nome inclui \n
        c = '\0';
        j = 0;

        // ler conteudo do arquivo
        registros[i].tam_conteudo = registros[i].tam - tam_nome;
        registros[i].conteudo = calloc(registros[i].tam_conteudo, 1); // aloca um espaço de tam_conteudo bytes
        if (!registros[i].conteudo)
            return NULL;
        fread(registros[i].conteudo, registros[i].tam_conteudo, 1, bin); // registros[i].conteudo aponta para
                                                                         // o conteudo do arquivo
        tam_nome = 0;
    }
    
    return registros;
}

int main(int argc, char **argv) {
    int flag_t = 0;

    if (argc > 2)
        USAGE_EXIT(1);

    if (argc == 2) {
        if (strcmp(argv[1], "-t") == 0)
            flag_t = 1;
        else
            USAGE_EXIT(1);
    }

    const char *backup = "bkp.bin";
    FILE *bin = fopen(backup, "rb");
    if (!bin)
        FOPEN_ERR_EXIT(1, backup);

    unsigned int n_registros = 0;
    fread(&n_registros, 1, sizeof(unsigned int), bin);

    struct reg *registros = le_vetor_registros(bin, n_registros);
    if (!registros)
        MEM_ERR_EXIT(1);

    FILE *out;

    if (flag_t) {
        for (unsigned int i = 0; i < n_registros; i++) {
            printf("Arquivos armazenados em %s:\n", backup);
            printf("%s\n", registros[i].nome);
        }

        return 0;
    } else {
        for (unsigned int i = 0; i < n_registros; i++) {
            out = fopen(registros[i].nome, "r");
            if (out)
                OVERWRITE_EXIT(1, registros[i].nome);
            out = fopen(registros[i].nome, "w");
            fwrite(registros[i].conteudo, registros[i].tam_conteudo, 1, out);
            fclose(out);
        }
    }

    free(registros);
    fclose(bin);

    return 0;
}
