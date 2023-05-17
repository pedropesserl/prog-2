#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define MAX_BUFFER 1024

#define USAGE_EXIT(err) do {                                                              \
    fprintf(stderr, "Uso: %s -[iamxrch] <archive> [membro1 [membro2 [...]]]\n", argv[0]); \
    exit(1);                                                                              \
} while (0)

int main(int argc, char **argv) {
    
    char *mvtarget = NULL;

    opterr = 0;
    char c = getopt(argc, argv, "iam:xrch");
    switch (c) {
        case 'i':
            break;

        case 'a':
            break;

        case 'm':
            mvtarget = optarg;
            break;

        case 'x':
            break;

        case 'r':
            break;

        case 'c':
            break;

        case 'h':
            printf("Uso: %s -[iamxrch] <archive> [membro1 [membro2 [...]]]\n\n", argv[0]);
            printf("Opções:\n");
            printf("    -i <archive> <membro1> [membro2 [...]]: Insere um ou mais membros");
            printf(" no archive, respeitando a ordem dos parâmetros (membro1, depois membro2");
            printf(" e assim por diante). Se um membro já estiver no archive, será substituído.\n");
            printf("    -a <archive> <membro1> [membro2 [...]]: Mesmo comportamento da");
            printf(" opção -i, mas substitui um membro existente APENAS caso o parâmetro seja");
            printf(" mais recente que o arquivado.\n");
            printf("    -m <target> <archive> <membro>: Move o membro indicado para imediatamente");
            printf(" depois do membro target, existente em archive.\n");
            printf("    -x <archive> [membro1 [membro2 [...]]]: Extrai os membros indicados de");
            printf(" archive. Se não for especificado nenhum membro, extrai todos os membros.\n");
            printf("    -r <archive> <membro1> [membro2 [...]]: Remove os membros indicados de archive.\n");
            printf("    -c <archive>: Lista o conteúdo de archive em ordem, incluindo as propriedades");
            printf(" de cada membro (nome, UID, permissões, tamanho e data de modificação) e sua ordem");
            printf(" no arquivo.\n");
            printf("    -h: Imprime essa mensagem de ajuda.\n");
            break;

        default:
            USAGE_EXIT(1);
    }

    return 0;
}
