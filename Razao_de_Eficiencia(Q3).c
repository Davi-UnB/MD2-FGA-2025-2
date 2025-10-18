#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 *A Razão de Eficiência de um Números
 *Alunos:
 *Daniel: 241025505
 *Davi: 241011018
 */

//Struct usado para representar um fator primo de um número
typedef struct {
    int valor;
    int potencia;
} fator;

//Função para calcular a potencia entre dois números
int potencia(int a, int b) {
    if (b == 0) {
        return 1;
    }
    int r = 1;
    for (int i = 0; i < b; i++) {
        r *= a;
    }
    return r;
}

//Função para implementar o Algoritmo de Trial Division
fator* trial_division(int n, int *numFatores) {
    int numInicial = n;
    printf("Aplicando o Algoritmo de Trial Division para fatorar %d\n", n);
    //Limite Prático para a cardinalidade dos fatores primos de números até 105
    fator *fatores = malloc(12 * sizeof(fator));
    for (int k = 0; k < 12; k++) {
        fatores[k].valor = 0;
        fatores[k].potencia = 0;
    }
    printf("\nPasso 1: Calcular o expoente do fator 2\n");
    //Define o fator 2
    fatores[0].valor = 2;
    while (n % 2 == 0) {
        printf("%d / 2 = %d\n", n, (n / 2));
        n /= 2;
        fatores[0].potencia++;
    }
    int p = 1;
    if (fatores[0].potencia == 0) {
        fatores[0].valor = 0;
        p = 0;
         printf("O numero %d nao tem nenhum fator de 2\n", numInicial);
    }
    else if (fatores[0].potencia == 1) printf("O numero %d tem 1 fator de 2\n", numInicial);
    else printf("O numero %d tem %d fatores de 2\n", numInicial, fatores[0].potencia);
    //Calcula para 3 e ímpares de 3
    printf("\nPasso 2: Fatorar impares a partir de 3\n");
    int limite = (int) sqrt(n);
    for (int i = 3; i <= limite; i += 2) {
        printf("Testando %d:\n", i);
        while (n % i == 0) {
            printf("%d / %d = %d\n", n, i, (n / i));
            if (fatores[p].valor == 0) fatores[p].valor = i;
            n /= i;
            fatores[p].potencia++;
        }
        if (fatores[p].valor != 0) {
            if (fatores[p].potencia == 1) printf("Ha 1 fator %d para %d\n", i, numInicial);
            else printf("Ha %d fator %d para %d\n", fatores[p].potencia, i, numInicial);
            p++;
        }
        else printf("Nao ha fator %d para %d\n", i, numInicial);
    }
    *numFatores = p;
    //Armazena valores não calculados que ainda são primos
    printf("\nPasso 3: Verificar se o quociente que sobrou e um primo\n");
    if (n > 1) {
        printf("o numero %d e um fator primo de %d\n", n, numInicial);
        fatores[p].valor = n;
        fatores[p].potencia = 1;
        *numFatores = *numFatores + 1;
    }
    else printf("Nao sobrou nenhum primo de %d\n", numInicial);
    printf("-----Fim do Algoritmo de Trial Division-----\n");
    return fatores;
}


//Função para calcular o Tau de n
int funcaoTau(int n, fator *fatores, int numFatores) {
    printf("\nFuncao Tau de %d: total de divisores positivos\n", n);
    //Impressão passo a passo do cálculo
    printf("tau(n) = ");
    for (int i = 0; i < numFatores - 1; i++) {
        printf("(%d + 1) * ", fatores[i].potencia);
    }
    printf("(%d + 1)\n", fatores[numFatores - 1].potencia);
    printf("tau(n) = ");
    int tau = 1;
    for (int i = 0; i < numFatores - 1; i++) {
        printf("%d * ", (fatores[i].potencia + 1));
        tau *= (fatores[i].potencia + 1);
    }
    printf("%d\n", (fatores[numFatores - 1].potencia + 1));
    tau *= (fatores[numFatores - 1].potencia + 1);
    printf("tau(n) = %d\n", tau);
    return tau;
}

//Função para calcular o Sigma de n
int funcaoSigma(int n, fator *fatores, int numFatores) {
    printf("\nFuncao Sigma de %d: soma dos divisores positivos\n", n);
    //Impressão passo a passo do cálculo
    printf("sigma(n) = ");
    int sigma = 1;
    for (int i = 0; i < numFatores - 1; i++) {
        printf("(%d^(%d + 1) - 1)/(%d - 1) * ", fatores[i].valor, fatores[i].potencia, fatores[i].valor);
        sigma *= ((potencia(fatores[i].valor, (fatores[i].potencia + 1)) - 1) / (fatores[i].valor - 1));
    }
    printf("(%d^(%d + 1) - 1)/(%d - 1)\n", fatores[numFatores - 1].valor, fatores[numFatores - 1].potencia, fatores[numFatores - 1].valor);
    sigma *= ((potencia(fatores[numFatores - 1].valor, (fatores[numFatores - 1].potencia + 1)) - 1) / (fatores[numFatores - 1].valor - 1));
    printf("sigma(n) = ");
    for (int i = 0; i < numFatores - 1; i++) {
        printf("(%d^%d - 1)/%d * ", fatores[i].valor, (fatores[i].potencia + 1), (fatores[i].valor - 1));
    }
    printf("(%d^%d - 1)/%d\n", fatores[numFatores - 1].valor, (fatores[numFatores - 1].potencia + 1), (fatores[numFatores - 1].valor - 1));
    printf("sigma(n) = ");
    for (int i = 0; i < numFatores - 1; i++) {
        printf("(%d - 1)/%d * ", potencia(fatores[i].valor, (fatores[i].potencia + 1)), (fatores[i].valor - 1));
    }
    printf("(%d - 1)/%d\n", potencia(fatores[numFatores - 1].valor, (fatores[numFatores - 1].potencia + 1)), (fatores[numFatores - 1].valor - 1));
    printf("sigma(n) = ");
    for (int i = 0; i < numFatores - 1; i++) {
        printf("%d/%d * ", (potencia(fatores[i].valor, (fatores[i].potencia + 1)) - 1), (fatores[i].valor - 1));
    }
    printf("%d/%d\n", (potencia(fatores[numFatores - 1].valor, (fatores[numFatores - 1].potencia + 1)) - 1), (fatores[numFatores - 1].valor - 1));
    printf("sigma(n) = ");
    for (int i = 0; i < numFatores - 1; i++) {
        printf("%d * ", ((potencia(fatores[i].valor, (fatores[i].potencia + 1)) - 1)/ (fatores[i].valor - 1)));
    }
    printf("%d\n", ((potencia(fatores[numFatores - 1].valor, (fatores[numFatores - 1].potencia + 1)) - 1) / (fatores[numFatores - 1].valor - 1)));
    printf("sigma(n) = %d\n", sigma);
    return sigma;
}


//Função principal
int main (void) {
    printf("---Atividade de Matematica Discreta 2---\nNome: Daniel, matricula: 241025505\nNome: Davi, matricula: 241011018\nQuestao 3\n");
    //Leitura Inicial de Dados
    int n = 0;
    while (1) {
        printf("Informe o valor de N: ");
        scanf("%d", &n);
        //Valida se n informado é 1
        if (n == 1) {
            printf("1 nao tem fatores primos a serem calculados\n");
            return 0;
        }
        //Quebra o laço caso o n informado seja válido
        if (n >= 1 && n <= 105) {
            break;
        }
        printf("Por favor, insira apenas valores de N entre 1 e 105!\n");
    }

    //Cálculo dos fatores de n
    int numFatores = 0;
    fator *fatores = trial_division(n, &numFatores);
    //Impressão dos fatores de n
    printf("\nLista de fatores calculados:\n");
    printf("%d = ", n);
    for (int i = 0; i < numFatores - 1; i++) {
        printf("%d^%d * ", fatores[i].valor, fatores[i].potencia);
    }
    printf("%d^%d\n", fatores[numFatores - 1].valor, fatores[numFatores - 1].potencia);

    //Cálculo de Tau e Sigma de n
    int tau = funcaoTau(n, fatores, numFatores);
    int sigma = funcaoSigma(n, fatores, numFatores);

    //Cálculo da Razão de Eficiência
    double razaoDeEficiencia = sigma / (double) tau;
    printf("\n-----Calculo da Razao de Eficiencia-----\n");
    printf("R(N) = sigma(N)/tau(N)\n");
    printf("R(%d) = sigma(%d)/tau(%d)\n", n, n, n);
    printf("R(%d) = %d/%d\n", n, sigma, tau);
    printf("R(%d) = %.2f\n", n, razaoDeEficiencia);
    printf("A Razao de Eficiencia de %d e %.2f\n", n, razaoDeEficiencia);
    printf("-----FIM DO PROGRAMA-----");

    free(fatores);
    return 0;
}
