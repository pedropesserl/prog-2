/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <sys/stat.h> */
/* #include <sys/types.h> */
/* #include <unistd.h> */
/* #include "libbin.h" */

/* struct Dir *le_dir(FILE *archive) { */
    
/* } */

#include <stdio.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>

int main(void) {
    const char *file = "/bin/";
    struct stat arch_stat;
    stat(file, &arch_stat);
    printf("modo: %x\n", arch_stat.st_mode);
    printf("GID: %d\n", arch_stat.st_gid);
    printf("UID: %d\n", arch_stat.st_uid);
    struct group *grp = getgrgid(arch_stat.st_gid);
    printf("grupo: %s\n", grp->gr_name);
    struct passwd *pwd = getpwuid(arch_stat.st_uid);
    printf("user: %s\n", pwd->pw_name);
}
