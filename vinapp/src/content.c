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
    
    char usr_string[9] = {0};
    char grp_string[9] = {0};
    char permstring[11] = {0};
    char timestring[17] = {0};
    for (size_t i = 0; i < dirnmemb; i++) {
        format_uid(usr_string, dir[i].uid);
        format_gid(grp_string, dir[i].gid);
        format_perm(permstring, dir[i].perm);
        format_modtime(timestring, dir[i].td);
        printf("%s %s/%s %8ld %s %s\n",
               permstring,  usr_string, grp_string,
               dir[i].size, timestring, dir[i].name+2);
    }
}
