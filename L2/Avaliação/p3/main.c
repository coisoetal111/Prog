/*Os projéteis seguem uma trajetória parabólica no ar devido à aceleração da gravidade. Considere a equação em
baixo que descreve a relação entre o ângulo de partida 𝜃, velocidade inicial 𝑣𝑜 e distância 𝑑, onde 𝑔 = 9.8 𝑚/𝑠
2
.
De forma a que o projétil não bata no teto também é necessário verificar que a altura não excede um valor
especificado pelo utilizador. Assuma que o projétil é enviado do chão (altura = 0). Escreva um programa que
recebe como parâmetros o ângulo de partida 𝜃 em graus, velocidade inicial 𝑣𝑜 e altura do teto, indica a que
distância deve estar o centro do cesto e imprime uma mensagem a indicar se o projétil bate ou não no teto. Note
que a função sin do C recebe o ângulo em radianos.*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Defenir algumas constantes úteis para o exercicio */

#define g 9.8
#define PI 3.1416

int main()
{
    float a = 0, ad = 0, v = 0, d = 0, ac = 0;

    printf("A altura é: ");
    scanf("%f", &ad);
    printf("A velocidade inicial é: ");
    scanf("%f", &v);
    printf("O ângulo é: ");
    scanf("%f", &a);

    a = a * (PI/180);

    d = (v * v * sinf(2*a))/g;
    ac = (v * v * sinf(a) * sinf(a))/(2*g);


    printf("A distância é: %f m \n", d);

    /* Verificar se altura calculada é superior á altura dada ( ver se a bola bate no teto ) */

    if(ad < ac){
        printf("A bola vai bater no teto!");
    }
    return 0;
}
