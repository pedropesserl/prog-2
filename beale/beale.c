#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE_EXIT(err) do {       \
        fprintf(stderr, "Uso: ./beale <opção> ");  \
        exit(err);                 \
    } while (0)

int main(int argc, char **argv) {
    if (argc < 2)
        USAGE_EXIT(1);

    printf("Alô, mamãe!\n");
    return 0;
}
