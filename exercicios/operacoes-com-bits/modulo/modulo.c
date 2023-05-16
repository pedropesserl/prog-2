#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE_EXIT(err) do {                                              \
        fprintf(stderr, "Uso: %s <dividendo> < 2 | 4 | 16 >\n", argv[0]); \
        exit(1);                                                          \
    } while(0)

#define ll long long

struct Mod {
    unsigned char mod2:1;
    unsigned char mod4:2;
    unsigned char mod16:4;
};

ll mod(ll dividendo, ll divisor) {
    struct Mod m;
    m.mod2 = dividendo;
    m.mod4 = dividendo;
    m.mod16 = dividendo;
    
    switch (divisor) {
        case 2:
            return m.mod2;
        case 4:
            return m.mod4;
        case 16:
            return m.mod16;
        default:
            fprintf(stderr, "Erro: inalcançável"); // unreachable
            exit(1);
    }
}

int main(int argc, char **argv) {
    if (argc != 3 || (strcmp(argv[2], "2") != 0 && strcmp(argv[2], "4") != 0 && strcmp(argv[2], "16") != 0))
        USAGE_EXIT(1);

    ll a;
    sscanf(argv[1], "%lld", &a);
    ll b;
    sscanf(argv[2], "%lld", &b);

    printf("%lld\n", mod(a, b));

    return 0;
}
