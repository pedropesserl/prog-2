#include <stdio.h>
#include <string.h>

int main() {
    const char *string = "aaaaa";

    printf("%d\n", (int)string[strlen(string)]);

    return 0;
}
