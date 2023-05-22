#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 100
#define uint unsigned int
#define EPSILON 1e-7

struct pessoa {
    uint cpf;
    uint idade;
};

int compar_int(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int compar_double(const void *a, const void *b) {
    if (fabs(*(double*)a - *(double*)b) < EPSILON)
        return 0;
    if (*(double*)a > *(double*)b)
        return 1;
    return -1;
}

int compar_pessoa_por_idade(const void *a, const void *b) {
    return (int)(((struct pessoa*)a)->idade - ((struct pessoa*)b)->idade);
}

int compar_pessoa_por_cpf(const void *a, const void *b) {
    return (int)(((struct pessoa*)a)->cpf - ((struct pessoa*)b)->cpf);
}

int main() {
    srand(time(0));

    int inteiros[MAX];
    double doubles[MAX];
    struct pessoa pessoas[MAX];

    for (int i = 0; i < MAX; i++) {
        inteiros[i] = rand();
        doubles[i] = (double) ((double)rand() / 10000.0);
        pessoas[i].cpf = rand();
        pessoas[i].idade = rand() % 101;
    }

    printf("Vetor de inteiros:\n");
    for (int i = 0; i < MAX; i++)
        printf("%d ", inteiros[i]);
    printf("\n");

    printf("Vetor de doubles:\n");
    for (int i = 0; i < MAX; i++)
        printf("%lf ", doubles[i]);
    printf("\n");

    printf("Vetor de pessoas:\n");
    for (int i = 0; i < MAX; i++)
        printf("CPF: %011u, IDADE: %3u\n", pessoas[i].cpf, pessoas[i].idade);
    printf("\n");

    printf("Ordenação:\n\n");

    qsort(inteiros, MAX, sizeof(int), compar_int);
    printf("Vetor de inteiros:\n");
    for (int i = 0; i < MAX; i++)
        printf("%d ", inteiros[i]);
    printf("\n\n");

    qsort(doubles, MAX, sizeof(double), compar_double);
    printf("Vetor de doubles:\n");
    for (int i = 0; i < MAX; i++)
        printf("%lf ", doubles[i]);
    printf("\n\n");

    qsort(pessoas, MAX, sizeof(struct pessoa), compar_pessoa_por_cpf);
    printf("Vetor de pessoas ordenado pelo cpf:\n");
    for (int i = 0; i < MAX; i++)
        printf("CPF: %011u, IDADE: %3u\n", pessoas[i].cpf, pessoas[i].idade);
    printf("\n");

    qsort(pessoas, MAX, sizeof(struct pessoa), compar_pessoa_por_idade);
    printf("Vetor de pessoas ordenado pela idade:\n");
    for (int i = 0; i < MAX; i++)
        printf("CPF: %011u, IDADE: %3u\n", pessoas[i].cpf, pessoas[i].idade);
    printf("\n");


    return 0;
}
