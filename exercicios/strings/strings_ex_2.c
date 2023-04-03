/* Calcular o tamanho de uma string (sem usar strlen). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: ./strings_ex_2 <string>\n");
        exit(1);
    }
    
    const char *input = argv[1];

    int i = 0;
    while (strcmp(&input[i], "\0") != 0) {
        i++;
    }

    printf("Tamanho do input: %d\n", i);

    return 0;
}
