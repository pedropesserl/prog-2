#include <stdio.h>
#include <stdlib.h>
#include "libbin.h"
#include "libarchiver.h"
#include "move.h"



void move_member(char *archive_path, char *target, char *member) {
    struct File_info *dir = NULL;
    size_t dirnmemb = 0;
    FILE *archive = fopen(archive_path, "rb+");
    if (!archive) {
        DNE_WARN(archive_path);
        return;
    }
    if (get_size(archive) == 0) {
        fclose(archive);
        printf("O arquivo %s está vazio.\n", archive_path);
        return;
    }
    dir = read_dir(archive, &dirnmemb);
    

    fclose(archive);
    free(dir);
}
