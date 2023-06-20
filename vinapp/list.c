#include <stdio.h>
#include "libbin.h"
#include "libarchiver.h"

void list_archive(char *archive_path) {
    FILE *archive = fopen(archive_path, "rb");
    if (!archive)
        FDNE_ERR(2, archive_path);

    size_t dirnmemb = 0;
    struct File_info *dir = read_dir(archive, &dirnmemb);
    
    for (size_t i = 0; i < dirnmemb; i++) {
        printf("%s %s/%s %8ld %s %s\n",
                dir[i].perm, dir[i].uid, dir[i].gid,
                dir[i].size, dir[i].td,  dir[i].name);
    }
}
