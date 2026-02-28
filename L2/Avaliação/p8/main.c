/*Considere o problema 3 e que o cesto tem um diâmetro 𝑐. Escreva um programa que calcule uma gama de valores
de ângulos aceitáveis de forma que o projétil caia dentro do cesto para uma dada distância e velocidade inicial.
Assim, o programa deve ler como parâmetros de entrada a distância 𝑑, a velocidade inicial 𝑣𝑜, o diâmetro do
cesto 𝑐 e imprimir a gama de ângulos (em graus). Utilize um ciclo while e não derive novas equações para
resolver este problema. */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* definir a funçâo que usei */
#define F(a, v) ( ( (v) * (v) * sinf( 2* (a)) )/ 9.8 )
#define PI 3.1416

int main()
{
    float d, v, c = 0;
    float a = 0;
    double angv[20000];
    int cont = 0;
    float amax, amin, amaxs, amins;




    printf("distância: ");
    scanf("%f" , &d);
    printf("velocidade inicial: ");
    scanf("%f" , &v);
    printf("diâmetro: ");
    scanf("%f" , &c);



    /* Verifica todos os angulos desde 0 a PI/2 rad*/
    while(a <= 3.1416/2 ) {

       // Se a condição se concretizar guarda o valor do ângulo no array "angulos validos"

        if(d-c/2 <= F(a, v) && F(a, v) <= d + c/2) {

            angv[cont] = a;

            cont++;



        }

        a = a + 0.0001;


    }



    amax = angv[cont - 1];
    amin = angv[0];










    for(int i = 0; i < cont; i++){


        if( angv[i + 1] > angv[i] + 0.0001 && cont > 0 ){

            amaxs = angv[i];
            amins = angv[i + 1];



            printf("Os ângulos estão entre %f graus e %f graus", amin * (180 / PI), amaxs * (180 / PI));

             printf(" e entre %f graus e %f graus", amins * (180 / PI), amax * (180 / PI));

            break;



        }


    }










    return 0;
}
