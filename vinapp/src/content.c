#include <stdio.h>
#include "libbin.h"
#include "libarchiver.h"

void list_archive(char *archive_path) {
    FILE *archive = fopen(archive_path, "rb");
    if (!archive)
        DNE_ERR(2, archive_path);

    if (get_size(archive) == 0) {
        printf("O arquivo %s está vazio.\n", archive_path);
        return;
    }

    size_t dirnmemb = 0;
    struct File_info *dir = read_dir(archive, &dirnmemb);
    
    char timestring[17] = {0};
    char permstring[11] = {0};
    for (size_t i = 0; i < dirnmemb; i++) {
        format_modtime(timestring, dir[i].td);
        format_perm(permstring, dir[i].perm);
        printf("%s %s/%s %8ld %s %s\n",
               permstring,  dir[i].uid, dir[i].gid,
               dir[i].size, timestring, dir[i].name+2);
    }
}
