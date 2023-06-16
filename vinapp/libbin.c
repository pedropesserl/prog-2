/* #include <sys/stat.h> */
/* #include <sys/types.h> */
/* #include <unistd.h> */
#include "libbin.h"

FILE *ME_read_and_write(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file)
        FDNE_ERR(3);
    fclose(file);
    file = fopen(path, "rb+");
    if (!file)
        FOPEN_ERR(2);
    return file;
}
