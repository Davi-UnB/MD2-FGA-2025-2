#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 *Projeto de Programação: Sistema RSA com Fatoração de Pollard e Aplicação de Teoremas Modulares em Três Etapas
 *Alunos:
 *Daniel: 241025505
 *Davi: 241011018
 */


//Função para tornar letras minúsculas em maiúsculas
void casoMaiusculo(char *palavra) {
    if (palavra == NULL) return;
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (palavra[i] >= 'a' && palavra[i] <= 'z') {
            palavra[i] = palavra[i] - 32;
        }
    }
}
//Função para imprimir String
void imprimirString(char palavra[]) {
    int i = 0;
    while (palavra[i] != '\0') {
        printf("%c", palavra[i]);
        i++;
    }
    printf("\n");
}

//Função para imprimir Array de int
void imprimirInt(int vetor[]) {
    int i = 0;
    while (vetor[i] != 99) {
        if (vetor[i + 1] != 99) {
        if (vetor[i] == 0) printf("00 - ");
        else printf("%d - ", vetor[i]);
        }
        else if (vetor[i] == '0') printf("00");
        else printf("%d", vetor[i]);
        i++;
    }
    printf("\n");
}

//Função para calcular o MDC entre 2 números
int calculo_mdc(int a, int b) {
    int quociente = 0, resto = 0, dividendo = a, divisor = b;
    if (b > a) {
        dividendo = b;
        divisor = a;
    }
    int x = dividendo, y = divisor;
    //Verifica se uma das entradas é 0
    if (divisor == 0) {
        printf("mdc(%d, %d) = %d\n", x, y, dividendo);
        return dividendo;
    }
    //Implementação do Algoritmo de Euclides
    while (1) {
        quociente = dividendo / divisor;
        resto = dividendo % divisor;
        printf("%d = %d * %d + %d\n", dividendo, divisor, quociente, resto);
        //Encerra o cálculo retornando o penúltimo resto calculado
        if (resto == 0) {
            printf("mdc(%d, %d) = %d\n", x, y, divisor);
            return divisor;
        }
        //Redefine os valores para uma nova iteração do algoritmo
        dividendo = divisor;
        divisor = resto;
    }
}

//Função para contar dígitos
int contaDigitos(int a) {
    int digitos = 0;
    while (1) {
        a = a / 10;
        digitos++;
        if (a == 0) return digitos;
    }
}

//Função para aplicar o Algoritmo de Euclides Estendido no Cálculo do Inverso Modular
int calculo_inversoModular(int a, int b) {
    int quociente = 0, resto = 0, dividendo = a, divisor = b, mdc = 0;
    if (b > a) {
        dividendo = b;
        divisor = a;
    }

    int x = dividendo, y = divisor;
    //Verifica se uma das entradas é 0
    if (divisor == 0)
        printf("mdc(%d, %d) = %d\n", x, y, dividendo);
        mdc = dividendo;
    //Vetores para armazenar o histórico de cálculos
    int *dividendos = (int *)malloc((5 * contaDigitos(divisor)) * sizeof(int));
    int *divisores = (int *)malloc((5 * contaDigitos(divisor)) * sizeof(int));
    int *quocientes = (int *)malloc((5 * contaDigitos(divisor)) * sizeof(int));
    int *restos = (int *)malloc((5 * contaDigitos(divisor)) * sizeof(int));

    //Implementação do Algoritmo de Euclides
    printf("---Etapa 1: Algoritmo de Euclides para encontrar MDC---\n");
    int k = 0;
    while (1) {
        quociente = dividendo / divisor;
        resto = dividendo % divisor;
        //Armazena os termos
        dividendos[k] = dividendo;
        divisores[k] = divisor;
        quocientes[k] = quociente;
        restos[k] = resto;
        printf("%d = %d * %d + %d\n", dividendo, divisor, quociente, resto);
        //Encerra o cálculo retornando o penúltimo resto calculado
        if (resto == 0) {
            printf("mdc(%d, %d) = %d\n", x, y, divisor);
            mdc = divisor;
            break;
        }
        //Redefine os valores para uma nova iteração do algoritmo
        dividendo = divisor;
        divisor = resto;
        k++;
    }

    //Algoritmo de Euclides Estendido
    printf("---Etapa 2: Isolar os Restos---\n");
    for (int i = 0; i <= k; i++) {
        printf("%d = %d - (%d * %d)\n", restos[i], dividendos[i], divisores[i], quocientes[i]);
    }

    printf("---Etapa 3: Calcular X e Y---\n");
    int i_inicial = k - 1;

    printf("Isolando o mdc:\n");

    long long coef1, coef2;
    long long termo1, termo2;
    coef1 = 1;
    termo1 = dividendos[i_inicial];
    coef2 = -quocientes[i_inicial];
    termo2 = divisores[i_inicial];

    printf("%lld = %lld * %lld + (%lld) * %lld\n", mdc, coef1, termo1, coef2, termo2);

    // Substituição Reversa
    for (int i = i_inicial - 1; i >= 0; i--) {
        printf("\n// Substituindo o termo %lld. Da equacao '%d = %d * %d + %d', temos:\n",
            termo2, dividendos[i], quocientes[i], divisores[i], restos[i]);
        printf("// %lld = %d - %d * %d\n", termo2, dividendos[i], quocientes[i], divisores[i]);
        printf("%lld = %lld * %lld + (%lld) * (%d - %d * %d)\n",
            mdc, coef1, termo1, coef2, dividendos[i], quocientes[i], divisores[i]);
        long long novo_coef2 = coef1 - coef2 * quocientes[i];

        printf("%lld = %lld * %d + (%lld) * %lld\n",
            mdc, coef2, dividendos[i], novo_coef2, termo1);

        coef1 = coef2;
        termo1 = dividendos[i];
        coef2 = novo_coef2;
        termo2 = divisores[i];
    }

    printf("\n--- Resultado da Substituicao ---\n");
    printf("Identidade de Bezout: %lld = %lld * %lld + %lld * %lld\n", mdc, coef1, termo1, coef2, termo2);

    long long int inverso;
    if (a == termo1) {
        inverso = coef1;
    } else {
        inverso = coef2;
    }

    printf("O coeficiente de a=%d e: %lld\n", a, inverso);
    int resposta = (inverso % b + b) % b;

    if (inverso < 0) {
        printf("O inverso e negativo. Ajustando para o intervalo [0, %d): %d\n", b, resposta);
    }

    printf("\n--- Resultado Final ---\n");
    printf("O inverso modular de %d (mod %d) e: %d\n\n", a, b, resposta);

    free(dividendos);
    free(divisores);
    free(quocientes);
    free(restos);

    return resposta;
}

//Função para calcular a diferença absoluta entre dois números
int diferencaAbsoluta(int a, int b) {
    int resultado = a - b;
    if (resultado < 0)
        resultado *= -1;
    return resultado;
}

//Função para Verificar se um número é primo
int verificaPrimo(int numero) {
    int raiz = (int) sqrt(numero);
    for (int i = 2; i <= raiz; i++) {
        if ((numero % i ) == 0)
            return 0;
    }
    return 1;
}

//Função para calcular a exponenciação modular
int exponenciacao(int a, int b, int n) {
    long long int resultado = 1;
    for (int i = 0; i < b; i++) {
        resultado = resultado * a;
        resultado = resultado % n;
    }
    return resultado;
}

//Função para Encontrar primeiro expoente que resulte em 1 mod n
int encontrarExpoente(int M, int n) {
    printf("Calculo para encontrar primeiro expoente que resulte em 1 mod %d\n", n);
    long long int potenciaAnterior = M;
    int potencia = 2;
    while (1) {
        printf("%d^%d congruente a %lld congruente a %d mod %d\n", M, potencia, (M * potenciaAnterior), ((M * potenciaAnterior) % n), n);
        potenciaAnterior = (M * potenciaAnterior) % n;
        if (potenciaAnterior == 1) return potencia;
        potencia++;
    }

}

//Função para Criptografar e Descriptografar
int criptografar(int mensagem, int expoente, int n, int numEuler, int seletor) {
    //Caso Especial de Criptografar 0
    if (mensagem == 0) {
        printf("Caso especial: a mensagem e 00. O resultado da exponenciacao modular e 0.\n");
        return 0;
    }
    //Início da Criptografia
    if (n == 1) printf("Queremos encontrar C tal que C congruente a %d^%d mod %d\n", mensagem, expoente, n);
    else printf("Queremos encontrar M tal que M congruente a %d^%d mod %d\n", mensagem, expoente, n);
    int valorCriptografado = 0;
    //Pequeno Teorema de Fermat
    if (calculo_mdc(mensagem, n) == 1 && verificaPrimo(n)) {
        printf("Sera usado o Pequeno Teorema de Fermat pois mdc(%d, %d) = 1 e %d e primo\n", mensagem, n, n);
        printf("%d^(%d) congruente a 1 mod %d\nlogo, ", mensagem, (n - 1), n);
        printf("%d^%d congruente a %d^(%d mod (%d - 1)) mod %d, logo\n", mensagem, expoente, mensagem, expoente, n, n);
        valorCriptografado = exponenciacao(mensagem, (expoente % (n - 1)), n);
        if (n == 1) printf("C = %d\n", valorCriptografado);
        else printf("M = %d\n", valorCriptografado);
        return valorCriptografado;
    }
    //Teorema de Euler
    else if (calculo_mdc(mensagem, n) == 1) {
        printf("Sera usado o Teorema de Euler pois mdc(%d, %d) = 1\n", mensagem, n);
        printf("%d^(%d) congruente a 1 mod %d,logo\n", mensagem, numEuler, n);
        printf("%d^%d congruente a %d^(%d mod %d) mod %d, logo\n", mensagem, expoente, mensagem, expoente, numEuler, n);
        printf("%d^%d congruente a %d^%d mod %d\n", mensagem, expoente, mensagem, (expoente % numEuler), n);
        valorCriptografado = exponenciacao(mensagem, (expoente % numEuler), n);
        if (n == 1) printf("C = %d\n", valorCriptografado);
        else printf("M = %d\n", valorCriptografado);
        return valorCriptografado;
    }
    //Teorema da Divisão Euclidiana
    else {
        printf("Sera usado o Teorema da Divisao Euclidiana para reduzir o expoente, pois nenhum outro teorema é aplicavel\n");
        int resultadoMDC = calculo_mdc(mensagem, n);
        if (resultadoMDC != 1) {
        printf("AVISO: A mensagem (%d) e o modulo n (%d) nao sao coprimos (mdc = %d).\n", mensagem, n, resultadoMDC);
        printf("Os teoremas de reducao de expoente nao se aplicam. Calculando diretamente.\n");
        valorCriptografado = exponenciacao(mensagem, expoente, n);
        if (seletor == 1) printf("C = %d\n", valorCriptografado);
        else printf("M = %d\n", valorCriptografado);
        return valorCriptografado;
        }
        else {
            printf("A mensagem (%d) e o módulo n (%d) são coprimos (mdc = %d), portanto o Teorema da Divisão Euclidiana pode ser aplicado.\n", mensagem, n, resultadoMDC);
            int potencia = encontrarExpoente(mensagem, n);
            printf("%d congruente a %d * %d + %d mod %d\n", expoente, potencia, (expoente / potencia), (expoente % potencia), n);
            printf("%d^%d congruente a %d^(%d * %d + %d) mod %d\n", mensagem, expoente, mensagem, potencia, (expoente / potencia), (expoente % potencia), n);
            printf("%d^%d congruente a (%d^%d)^%d * %d^%d mod %d\n", mensagem, expoente, mensagem, potencia, (expoente / potencia), mensagem, (expoente % potencia), n);
            printf("%d^%d congruente a 1^%d * %d^%d mod %d\n", mensagem, expoente, (expoente / potencia), mensagem, (expoente % potencia), n);
            printf("%d^%d congruente a %d^%d mod %d\n", mensagem, expoente, mensagem, (expoente % potencia), n);
            int valorCriptografado = exponenciacao(mensagem, (expoente % potencia), n);
            printf("%d^%d congruente a %d mod %d\n", mensagem, expoente, valorCriptografado, n);
            return valorCriptografado;
        }
    }
}

int main(void) {
    printf("---Atividade de Matematica Discreta 2---\nNome: Daniel, matricula: 241025505\nNome: Davi, matricula: 241011018\nQuestao 1\n");
    int n1 = 0, n2 = 0;
    char mensagem[1025];
    printf("Insira uma mensagem a ser codificada com limite de ate 1024 caracteres: ");
    fgets(mensagem, sizeof(mensagem), stdin);
    while (1) {
        //Entrada dos valores iniciais
        printf("ATENCAO: Cada numero deve ser produto de primos distintos, para garantir a eficiencia do algoritmo!\n");
        printf("ATENCAO: Informe apenas valores de 3 a 4 digitos!\n");
        printf("Informe o primeiro numero: ");
        scanf("%d", &n1);
        printf("Informe o segundo numero: ");
        scanf("%d", &n2);
        //Valida a quantidade de dígitos das entradas
        if (n1 < 100 || n1 > 9999 || n2 < 100 || n2 > 9999) {
            printf("Por favor, informe apenas valores de 3 a 4 digitos para que o metodo de Pollard seja eficiente!\n");
        }
        else {
            break;
        }
    }

    //Etapa 1: Fatoração Iterativa (Método p de Pollard)
    int primos[2] = {1, 1};
    for (int i = 0; i < 2; i++) {
        int num = 0, fatorPrimo = 0, x = 2, k = 0, f = 0, mdc = 0;
        if (i == 0) num = n1;
        else num = n2;
        printf("Calculo do numero primo nao trivial de N%d: %d\n", (i + 1), num);
        while (1) {
            printf("------------------------------\n");
            printf("Iteracao %d\n", k);
            f = ((x * x) + 1) % num;
            mdc = calculo_mdc(diferencaAbsoluta(x, f), num);
            printf("X%d = f(X%d)modN%d = %d\n", (k + 1), k, (i + 1), f);
            printf("mdc(|%d - %d|, %d) = mdc(%d, %d) = %d\n", f, x, num, diferencaAbsoluta(x, f), num, mdc);
            if (mdc > 1) {
                printf("------------------------------\n");
                printf("Algoritmo encerrado com fator nao trivial de N%d, p%d = %d\n\n", (i + 1), (i + 1), mdc);
                primos[i] = mdc;
                break;
            }
            if (k > 499) {
                printf("------------------------------\n");
                printf("Limite de tentativas excedido! Nenhum fator encontrado para N%d\n\n", (i + 1));
                printf("Programa encerrado\n");
                exit(0);
                break;
            }
            x = f;
            k++;
        }
    }
    printf("Os primos encontrados sao:\np = %d\nq = %d\n\n", primos[0], primos[1]);

    //Etapa 2: Geração das Chaves RSA
    int p = primos[0], q = primos[1];
    int n = p * q;
    int z = (p - 1) * (q - 1);
    int E = 0;
    printf("n = %d\nz = %d\n", n, z);
    printf("---Calculo para Encontrar o menor E que seja coprimo de z---\n");
    for (int j = 2; j < n; j++) {
        printf("Numero Testado: %d\n", j);
        int valor = calculo_mdc(j, z);
        if (valor == 1) {
            E = j;
            printf("------------------------------\n");
            break;
        }
    }
    int D = calculo_inversoModular(E, z);

    //Etapa 3: Codificação e Decodificação da mensagem
    //Pré-Codificação
    int mensagemPreCripto[1025];
    int w = 0;
    //Criptografa os caracteres ASCII na pré-codificação recomendada
    while (mensagem[w] != '\0') {
        if (mensagem[w] == ' ') mensagemPreCripto[w] = 0;
        else mensagemPreCripto[w] = mensagem[w] - 54;
        w++;
    }
    mensagemPreCripto[w] = 99;
    mensagemPreCripto[w] = 99;

    //Codificação
    int mensagemCodificada[1025];
    for (int r = 0; r < w; r++) {
        mensagemCodificada[r] = criptografar(mensagemPreCripto[r], E, n, z, 1);
    }
    mensagemCodificada[w] = 99;

    //Decodificação
    char mensagemDecodificada[1025];
    for (int l = 0; l < w; l++) {
        int valorDecodificado = criptografar(mensagemCodificada[l], D, n, z, 2);
        if (valorDecodificado != 0) mensagemDecodificada[l] = valorDecodificado + 54;
        else mensagemDecodificada[l] = ' ';
    }
    mensagemDecodificada[w] = '\0';

    //Impressão dos Resultados
    printf("Mensagem a Criptografar: ");
    imprimirString(mensagem);
    printf("Mensagem Pre-Criptografada: ");
    imprimirInt(mensagemPreCripto);
    printf("\nMensagem Criptografada: ");
    imprimirInt(mensagemCodificada);
    printf("\nMensagem Descriptografada: ");
    imprimirString(mensagemDecodificada);

    return 0;
}
