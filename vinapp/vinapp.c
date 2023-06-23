#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libbin.h"
#include "insert.h"
#include "content.h"
#include "remove.h"
#include "move.h"

#define USAGE_EXIT(err) do {                                                    \
    fprintf(stderr, "Uso: %s -[iamxrch] <archive> [membro1 [membro2 [...]]]\n", \
            argv[0]);                                                           \
    fprintf(stderr,                                                             \
            "Use %s -h para imprimir uma mensagem de ajuda.\n", argv[0]);       \
    exit(1);                                                                    \
} while (0)

char parse_options(int argc, char **argv) {
    if (argc > 1 && argv[1][0] != '-') // o primeiro argumento precisa ser uma opção
        USAGE_EXIT(1);
    int optn = 0;
    char option, c;
    while ((c = getopt(argc, argv, "iam:xrch")) != -1) {
      option = c;
      optn++;
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
          break;
        default:
          USAGE_EXIT(1);
      }
    }
    if (optn != 1)
        USAGE_EXIT(1);
    return option;
}

int main(int argc, char **argv) {
    char *archive_path = NULL;
    opterr = 0;

    char option = parse_options(argc, argv);

    if (option == 'm')
        archive_path = argv[3];
    else
        archive_path = argv[2];
    
    switch (option) {
    case 'i':
        insert_in_archive(archive_path, argc - 3, argv + 3);
        break;
    case 'a':
        update_archive(archive_path, argc - 3, argv + 3);
        break;
    case 'm':
        move_member(archive_path, argv[2], argv[4]);
        break;
    case 'x':
        break;
    case 'r':
        remove_from_archive(archive_path, argc - 3, argv + 3);
        break;
    case 'c':
        list_archive(archive_path);
        break;
    case 'h':
        printf("Uso: %s -[iamxrch] <archive> [membro1 [membro2 [...]]]\n\n",
                argv[0]);
        printf("Opções (use exatamente uma):\n");
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
        return 0;
    default: // inatingível
        USAGE_EXIT(1);
    }

    return 0;
}
