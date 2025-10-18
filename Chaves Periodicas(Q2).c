#include <stdio.h>
#include <stdlib.h>

long mdc(long m, long n);
long mmc_2(long a, long b);
long mmc_n(int *v, int n);

int main(void) {

    int n; // Quantidade de chaves
    printf("-----------------------------------\n");
    printf("Exercicio : Chaves Periodicas\n");
    printf("Daniel : 241025505\n");
    printf("Davi : 241011018\n");
    printf("-----------------------------------\n\n");

    printf("Abordagem Escolhida: Minimo Multiplo Comum (MMC)\n");
    printf("Justificativa: Para encontrar o primeiro ano em que todas as chaves se ativam simultaneamente,\n");
    printf("e necessario calcular o menor multiplo comum de todos os ciclos, que e a definicao do MMC.\n\n");

    printf("--- PASSO 1: ENTRADA DE DADOS ---\n\n");
    do {
        printf("Digite a quantidade de chaves (1 a 10): ");
        scanf("%d", &n);

        if (n < 1 || n > 10) {
            printf("Erro: a quantidade de chaves deve estar entre 1 e 10.\n");
        }

    } while (n < 1 || n > 10);

    int *v = (int*) malloc (n * sizeof(int));
    if (v == NULL) {
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
    printf("\n");

    printf("--- PASSO 2: CALCULO DO MMC ---\n\n");
    long r = mmc_n(v, n);

    printf("\n--- PASSO 3: CONCLUSAO ---\n\n");
    if (r <= 50) {
        printf("O resultado (%ld) esta dentro do limite de 50 anos.\n", r);
        printf("-> Primeiro ano sincronizado: %ld\n", r);
    } else {
        printf("O resultado (%ld) ultrapassa o limite de 50 anos.\n", r);
        printf("-> Nao foi possivel sincronizar as chaves.\n");
    }

    printf("\n"); //Espaço extra pra melhorar legibilidade

    free(v);
    return 0;
}

/**
 *Calcula o MDC mostrando os passos de forma aninhada e clara.
 */
long mdc(long m, long n) {
    printf("        Sub-calculo: MDC(%ld, %ld) com Algoritmo de Euclides.\n", m, n);
    long m_original = m;
    long n_original = n;
    long resto;
    while (n != 0) {
        resto = m % n;
        printf("            -> %ld %% %ld = %ld\n", m, n, resto);
        m = n;
        n = resto;
    }
    printf("        MDC(%ld, %ld) = %ld.\n", m_original, n_original, m);
    return m;
}

/**
 *Calcula o MMC de dois números, mostrando a fórmula aplicada.
 */
long mmc_2(long a, long b) {
    printf("    Aplicando a formula: MMC(a, b) = (a * b) / MDC(a, b)\n");
    long mdc_resultado = mdc(a, b);
    long resultado = (a * b) / mdc_resultado;
    printf("    MMC(%ld, %ld) = (%ld * %ld) / %ld = %ld.\n", a, b, a, b, mdc_resultado, resultado);
    return resultado;
}

/**
 *Calcula o MMC de N números, explicando a propriedade e numerando os passos.
 */
long mmc_n(int *v, int n) {
    if (n == 1) {
        printf("Apenas um ciclo fornecido (%d). O MMC e o proprio valor.\n", v[0]);
        return v[0];
    }

    printf("Propriedade utilizada: O MMC de N numeros pode ser calculado de forma associativa.\n");
    printf("MMC(c1, c2, ..., cn) = MMC( ... MMC(MMC(c1, c2), c3), ... , cn)\n\n");

    printf("Sub-passo 2.1: Calculando o MMC para o primeiro ciclo (base da iteracao).\n");
    printf("    Por definicao, o MMC de um unico numero e o proprio numero.\n");
    long resultado = v[0];
    printf("    Resultado parcial inicial: %ld\n", resultado);

    for (int i = 1; i < n; i++) {
        printf("\nSub-passo 2.%d: Calculando o MMC entre o resultado parcial (%ld) e o proximo ciclo (%d).\n", i + 1, resultado, v[i]);
        resultado = mmc_2(resultado, v[i]);
        printf("    Resultado parcial atualizado: %ld\n", resultado);
    }
    printf("\nO MMC final de todos os ciclos e: %ld\n", resultado);
    return resultado;
}