/*
Alunos:

    Daniel : 241025505
    Davi : 241011018

Enunciado : 
Com o código abaixo, complete as linhas 10, 14, 23, 36, 45, 72 e 78 que faltam para que o
programa funcione corretamente, realizando a divisão modular e o cálculo da congruência H ÷ G
(mod Zn) seguido de a^x mod n1, aplicando o Pequeno Teorema de Fermat ou o Teorema de
Euler, conforme o caso.

Com o código completo e preenchido corretamente, qual seria a saída com os valores: H: 7,
G: 3, Zn: 11, x: 10, n1: 13

Resposta : A saída é :
Algoritmo de Euclides: 3 mod 11 = 3
Algoritmo de Euclides: 11 mod 3 = 2
Algoritmo de Euclides: 3 mod 2 = 1
Algoritmo de Euclides: 2 mod 1 = 0

Substituindo, temos que o inverso de 3 em 11 é 4.

Fazendo a multiplicação modular: 7 * 4 mod 11 = 6
 Sendo 4 o inverso de 3.
Valor final da congruência: 4

correção extra_1


*/

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif


int mdcComPassos(int a, int b) {
    int resto;
    while (b != 0) {
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n",a, b, resto);
        a = b;
        b = resto;
    }
    return a;
}
int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    int verificar = mdcComPassos(a,m);

    if (verificar != 1) {
        printf("Não existe inverso modular, pois mdc(%d, %d) = %d\n", A, B, verificar);
        return 0;
    }

    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0){
    x1 += m0;}
    printf("\nSubstituindo, temos que o inverso de %d em %d é %d.\n\n",A, B, x1);
    return x1;
}

int powMod(int base, int exp, int mod){
    long long res = 1;
    long long b = base % mod;
    while(exp > 0){
        if(exp & 1){
            res = (res * b) % mod;}
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)res;
}

int main(){
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H, G, Zn, x, n1;

    printf("Insira H: ");
    scanf("%d",&H);
    printf("Insira G: ");
    scanf("%d",&G);
    printf("Insira Zn: ");
    scanf("%d",&Zn);
    printf("Insira x: ");
    scanf("%d",&x);
    printf("Insira n1: ");
    scanf("%d",&n1);
    printf("\n");

    int inverso = inversoModular(G,Zn);
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf(" Sendo %d o inverso de %d.\n", inverso, G);

    int resultado = powMod(a, x, n1);
    printf("Valor final da congruência: %d\n", resultado);

    return 0;
}
