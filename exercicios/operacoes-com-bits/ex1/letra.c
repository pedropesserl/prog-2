#include <stdio.h>

#define EH_VOGAL(c) (c == 'A' || c == 'a' || c == 'E' || c == 'e' || c == 'I' || c == 'i' || c == 'O' || c == 'o' || c == 'U' || c == 'u')

struct Letra {
    char letra;
    unsigned char valor:5;
    unsigned char vogal:1;
    unsigned char maiuscula:1;
    unsigned char depois_de_m:1;
    unsigned char ult_prim:2;
    unsigned char vizinha:1;
    unsigned char n_ate_ult:5;
};

int main() {
    struct Letra l;
    printf("Digite uma letra:\n");
    int c = getchar();
    if (c < 'A' || c > 'z') {
        fprintf(stderr, "O caracter precisa ser uma letra.\n");
        return 1;
    }

    l.letra = c;
    l.vogal = EH_VOGAL(c);
    l.maiuscula = 'A' <= c && c <= 'Z';
    l.depois_de_m = ('N' <= c && c <= 'Z') || ('n' <= c && c <= 'z');
    l.ult_prim = c == 'A' || c == 'a' ? 1 : c == 'Z' || c == 'z' ? 2 : 0;
    l.vizinha = (!l.ult_prim) && (EH_VOGAL(c-1) || EH_VOGAL(c+1));
    l.n_ate_ult = l.maiuscula ? 'Z' - c : 'z' - c;
    l.valor = l.maiuscula ? c - 64 : c - 96;

    printf("Valor: %d\n", l.valor);
    printf("É vogal: %d\n", l.vogal);
    printf("É maiúscula: %d\n", l.maiuscula);
    printf("Vem depois da letra M: %d\n", l.depois_de_m);
    printf("Primeira (01), última (10) ou nenhuma (00): %d\n", l.ult_prim);
    printf("Vizinha é vogal: %d\n", l.vizinha);
    printf("Numero de letras até a última: %d\n", l.n_ate_ult);
    printf("Tamanho da estrutura utilizada: %ld\n", sizeof(l));

    return 0;
}
