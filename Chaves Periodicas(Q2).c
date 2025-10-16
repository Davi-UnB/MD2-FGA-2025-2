#include <stdio.h>
#include <stdlib.h>

long mdc(long m, long n);
long mmc_2(int a, int b);
long mmc_n(int *v, int n);

int main(void) {

    int n; // Quantidade de chaves
    printf("-----------------------------------\n");
    printf("Exercicio : Chaves Periodicas\n");
    printf("Daniel : 241025505\n");
    printf("Davi : 241011018\n");
    printf("-----------------------------------\n");

    do {
        printf("Digite a quantidade de chaves (1 a 10): ");
        scanf("%d", &n);

        if (n < 1 || n > 10) {
            printf("Erro: a quantidade de chaves deve estar entre 1 e 10.\n");
        }

    } while (n < 1 || n > 10);


    int *v = (int*) malloc (n * sizeof(int)); // Alocação Dinâmica
    if (v == NULL) { // Verificação de êxito da alocação
        printf("Erro: Falha ao alocar memoria.\n");
        return -1;
    }


    for (int i = 0; i < n; i++) {
        do {
            printf("Digite o ciclo da chave da posicao %d (entre 2 e 20): ", i + 1);
            scanf("%d", &v[i]);

            if (v[i] < 2 || v[i] > 20) {
                printf("Valor invalido! O ciclo deve estar entre 2 e 20.\n");
            }

        } while (v[i] < 2 || v[i] > 20);
    }



    int r = mmc_n(v,n); // Calculo do mmc dos ciclos das n chaves.

    if (r <= 50) {

        printf("Primeiro ano sincronizado %d\n",r);

    }
    else {
        printf("Nao foi possivel sincronizar dentro de 50 anos.\n");
    }



    free(v);
}


long mdc(long m, long n){ /*Implementação Recursiva do Algoritmo de Euclides*/
    if (n==0) return m;
    return mdc (n, m % n);
}

long mmc_2(int a, int b) { /*MMC de dois números*/

    return a*b / mdc(a, b);

}

long mmc_n(int *v, int n) { // MMC(a,b,c)=MMC(MMC(a,b),c)
    int resultado = v[0];
    for (int i = 1; i < n; i++) {
        resultado = mmc_2(resultado, v[i]);
    }
    return resultado;
}