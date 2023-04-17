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

#define MEM_ERR_EXIT(err) do {                                                  \
        fprintf(stderr, "Erro na alocação de memória.\n");                      \
        exit(err);                                                              \
    } while (0)

#define FOPEN_ERR_EXIT(err, filename) do {                                      \
        fprintf(stderr, "Erro ao abrir/escrever arquivo %s.\n", filename);      \
        exit(err);                                                              \
    } while (0)

#define FEXISTS_EXIT(err, filename) do {                                        \
        fprintf(stderr, "Erro: o arquivo %s já existe.\n", filename);           \
        exit(err);                                                              \
    } while (0);

#include "lista.h"
#include "codificacao.h"
#include "decodificacao.h"
#include "chaves.h"

int main(int argc, char **argv) {
    int erro = 0;

    if (argc < 8)
        USAGE_EXIT(1);

    char *livro_cifra = NULL;
    char *msg_input = NULL;
    char *msg_output = NULL;
    char *arq_chaves = NULL;
    int exportar_chaves = 0;
    int decodificar_com_chaves = 0;
    
    L_lista *lista_de_chaves = cria_l_lista();
    if (!lista_de_chaves)
        MEM_ERR_EXIT(1);

    opterr = 0;
    char c = getopt(argc, argv, "ed");
    if (c == 'e') {
        while ((c = getopt(argc, argv, "b:m:o:c:")) != -1)
            switch (c) {
                case 'b':
                    livro_cifra = optarg;
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

        erro = codifica_msg(livro_cifra, msg_input, msg_output, lista_de_chaves);
        if (erro)
            switch (erro) {
                case 1:
                    MEM_ERR_EXIT(erro);
                    break;
                case 2:
                    FOPEN_ERR_EXIT(erro, livro_cifra);
                    break;
                case 3: 
                    FOPEN_ERR_EXIT(erro, msg_input);
                    break;
                case 4:
                    FEXISTS_EXIT(erro, msg_output);
                    break;
                case 5:
                    FOPEN_ERR_EXIT(erro, msg_output);
            }

        if (exportar_chaves) {
            erro = exporta_chaves(arq_chaves, lista_de_chaves);
            if (erro)
                switch (erro) {
                    case 2:
                        FOPEN_ERR_EXIT(erro, arq_chaves);
                        break;
                    case 4:
                        FEXISTS_EXIT(erro, arq_chaves);
                        break;
                }
        }

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

        if (decodificar_com_chaves) {
            erro = decodifica_com_chaves(arq_chaves, msg_input, msg_output, lista_de_chaves);
            if (erro)
                switch (erro) {
                    case 1:
                        MEM_ERR_EXIT(erro);
                        break;
                    case 2:
                        FOPEN_ERR_EXIT(erro, arq_chaves);
                        break;
                    case 3: 
                        FOPEN_ERR_EXIT(erro, msg_input);
                        break;
                    case 4:
                        FEXISTS_EXIT(erro, msg_output);
                        break;
                    case 5:
                        FOPEN_ERR_EXIT(erro, msg_output);
                        break;
                }
        } else {
            erro = decodifica_com_livro(livro_cifra, msg_input, msg_output, lista_de_chaves);
            if (erro)
                switch (erro) {
                    case 1:
                        MEM_ERR_EXIT(erro);
                        break;
                    case 2:
                        FOPEN_ERR_EXIT(erro, livro_cifra);
                        break;
                    case 3: 
                        FOPEN_ERR_EXIT(erro, msg_input);
                        break;
                    case 4:
                        FEXISTS_EXIT(erro, msg_output);
                        break;
                    case 5:
                        FOPEN_ERR_EXIT(erro, msg_output);
                        break;
                }

        }

    } else
        USAGE_EXIT(1);

    lista_de_chaves = destroi_l_lista(lista_de_chaves);

    return 0;
}
