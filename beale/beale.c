#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define USAGE_EXIT(err) do {                                                    \
        fprintf(stderr, "Usos:\n");                                             \
        fprintf(stderr, "./beale -e -b <livro_cifra> -m <mensagem_original> "); \
        fprintf(stderr, "-o <mensagem_codificada> [-c <arquivo_de_chaves>]\n"); \
        fprintf(stderr, "./beale -d -i <mensagem-codificada> ");                \
        fprintf(stderr, "-c <arquivo-de-chaves> -o <mensagem-decodificada>\n"); \
        fprintf(stderr, "./beale -d -i <mensagem-codificada> ");                \
        fprintf(stderr, "-b <livro-cifra> -o <mensagem-decodificada>\n");       \
        exit(err);                                                              \
    } while (0)

#include "codificacao.h"
#include "decodificacao.h"
#include "chaves.h"

int main(int argc, char **argv) {
    if (argc < 8)
        USAGE_EXIT(1);

    char *livro_cifra = NULL;
    char *msg_input = NULL;
    char *msg_output = NULL;
    char *arq_chaves = NULL;
    int exportar_chaves = 0;
    int decodificar_com_chaves = 0;

    opterr = 0;
    char c = getopt(argc, argv, "ed");
    
    if (c == 'e') {
        while ((c = getopt(argc, argv, "b:m:o:c:")) != -1)
            switch (c) {
                case 'b':
                    livro_cifra = optarg;
                    arq_chaves = optarg;
                    break;
                case 'm':
                    msg_input = optarg;
                    break;
                case 'o':
                    msg_output = optarg;
                    break;
                case 'c':
                    exportar_chaves = 1;
                    arq_chaves = optarg;
                    break;
                default:
                    USAGE_EXIT(1);
            }

        printf("A mensagem que voce quer codificar está no arquivo %s.\n", msg_input);
        printf("A mensagem codificada sairá no arquivo %s.\n", msg_output);
        printf("O livro que usaremos para codificar a mensagem é %s.\n", livro_cifra);
        if (exportar_chaves)    
            printf("Você escolheu exportar as chaves de cifra utilizadas. Elas sairão no arquivo %s.\n", arq_chaves);
        else
            printf("Você escolheu não exportar as chaves de cifra utilizadas.\n");

    } else if (c == 'd') {
        while ((c = getopt(argc, argv, "i:c:b:o:")) != -1)
            switch (c) {
                case 'i':
                    msg_input = optarg;
                    break;
                case 'c':
                    decodificar_com_chaves = 1;
                    arq_chaves = optarg;
                    break;
                case 'b':
                    livro_cifra = optarg;
                    break;
                case 'o':
                    msg_output = optarg;
                    break;
                default:
                    USAGE_EXIT(1);
            }

        printf("A mensagem que você quer decodificar está no arquivo %s.\n", msg_input);
        printf("A mensagem decodificada sairá no arquivo %s.\n", msg_output);
        if (decodificar_com_chaves)
            printf("Você escolheu decodificar com um arquivo de chaves. Usaremos o arquivo %s.\n", arq_chaves);
        else
            printf("Você escolheu decodificar com um livro-cifra. Usaremos o livro %s.\n", livro_cifra);

    } else
        USAGE_EXIT(1);

    return 0;
}
