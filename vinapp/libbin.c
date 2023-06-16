/* #include <sys/stat.h> */
/* #include <sys/types.h> */
/* #include <unistd.h> */
#include "libbin.h"

size_t get_size(FILE *f) {
    fseek(f, 0, SEEK_END);
    size_t sz = ftell(archive);
    rewind(archive);
    return sz;
}

void open_space(FILE *f, size_t space, size_t pos) {
    fprintf(stderr, "open_space: não implementada\n");
    exit(1);
}
