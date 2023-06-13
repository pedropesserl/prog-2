#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define USAGE_EXIT(err) do {                                                      \
    fprintf(stderr, "Uso: %s -[iamxrch] <archive> [membro1 [membro2 [...]]]\n",   \
            argv[0]);                                                             \
    fprintf(stderr, "Use %s -h para imprimir uma mensagem de ajuda.\n", argv[0]); \
    exit(1);                                                                      \
} while (0)

int main(int argc, char **argv) {
    
    char *backup = NULL;
    char *mvtarget = NULL;

    opterr = 0;
    char c = getopt(argc, argv, "iam:xrch");
    switch (c) {
    case 'i':
        if (argc < 4) {
            fprintf(stderr, "Uso: %s -i <archive> <membro1> [membro2 [...]]\n",
                    argv[0]);
            exit(1);
        }
        break;

    case 'a':
        if (argc < 4) {
            fprintf(stderr, "Uso: %s -a <archive> <membro1> [membro2 [...]]\n",
                    argv[0]);
            exit(1);
        }
        break;

    case 'm':
        if (argc != 5) {
            fprintf(stderr, "Uso: %s -m <target> <archive> <membro>\n", argv[0]);
            exit(1);
        }
        mvtarget = optarg;
        



        break;

    case 'x':
        if (argc < 3) {
            fprintf(stderr, "Uso: %s -x <archive> [membro1 [membro2 [...]]]\n",
                    argv[0]);
            exit(1);
        }

        break;

    case 'r':
        if (argc < 4) {
            fprintf(stderr, "Uso: %s -r <archive> <membro1> [membro2 [...]]\n",
                    argv[0]);
            exit(1);
        }

        break;

    case 'c':
        if (argc != 3) {
            fprintf(stderr, "Uso: %s -c <archive>\n", argv[0]);
            exit(1);
        }
        break;

    case 'h':
        printf("Uso: %s -[iamxrch] <archive> [membro1 [membro2 [...]]]\n\n",
                argv[0]);
        printf("Opções:\n");
        printf("    -i <archive> <membro1> [membro2 [...]] Insere um ou mais");
        printf(" membros no archive, respeitando a ordem dos parâmetros");
        printf(" (membro1, depois membro2 e assim por diante). Se um membro");
        printf(" já estiver no archive, será substituído.\n");
        printf("    -a <archive> <membro1> [membro2 [...]] Mesmo comportamento");
        printf(" da opção -i, mas substitui um membro existente APENAS caso o");
        printf(" parâmetro seja mais recente que o arquivado.\n");
        printf("    -m <target> <archive> <membro>         Move o membro");
        printf(" indicado para imediatamente após o membro target, que deve");
        printf(" estar presente em archive.\n");
        printf("    -x <archive> [membro1 [membro2 [...]]] Extrai os membros");
        printf(" indicados de archive. Se não for especificado nenhum membro,");
        printf(" extrai todos os membros.\n");
        printf("    -r <archive> <membro1> [membro2 [...]] Remove os membros");
        printf(" indicados de archive.\n");
        printf("    -c <archive>                           Lista o conteúdo de");
        printf(" archive em ordem, incluindo as propriedades de cada membro");
        printf(" (nome, UID, permissões, tamanho e data de modificação) e sua");
        printf(" ordem no arquivo.\n");
        printf("    -h                                     Imprime essa");
        printf(" mensagem de ajuda.\n");
        break;

    default:
        USAGE_EXIT(1);
    }

    return 0;
}
