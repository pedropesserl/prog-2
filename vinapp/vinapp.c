#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define USAGE_EXIT(err) do {   \
    fprintf(stderr, "Uso:\n"); \
    exit(1);                   \
} while (0)

int main(int argc, char **argv) {
    
    char c = argv[1][1];
    putchar(c);
    putchar('\n');

    char *nome;
    nome = argv[2];
    printf("%s\n", nome);

    /* char c = getopt(argc, argv, "iamxrch"); */
    /* switch (c) { */
    /*     case 'i': */
    /*         break; */
    /*     case 'a': */
    /*         break; */
    /*     case 'm': */
    /*         break; */
    /*     case 'x': */
    /*         break; */
    /*     case 'r': */
    /*         break; */
    /*     case 'c': */
    /*         break; */
    /*     case 'h': */
    /*         break; */
    /*     default: */
    /*         USAGE_EXIT(1); */
    /* } */

    return 0;
}
