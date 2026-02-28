/*A radiação eletromagnética pode ser classificada em uma de sete categorias de acordo com a sua frequência, tal
como indicado na tabela em baixo. Escreva um programa que recebe a frequência e imprime o nome da classe
correspondente. Use a directiva #define recebendo a frequência como parâmetro.*/




#include <stdio.h>
#include <stdlib.h>

/* Usar o #define para defenir a condição que se usa ao longo do exercicio */

#define I(f, min, max) ((f) >= (min) && (f) < (max))

int main()
{
    double f = 0;

    scanf("%lf", &f);


        if (I(f, 0, 3e9)){
        printf("Ondas de Rádio");
        }
        else if (I(f, 3e9, 3e12)){
        printf("Micro-ondas");
    }
        else if (I(f, 3e12, 4.3e14)){
        printf("Infravermelha");
    }
        else if (I(f, 4.3e14, 7.5e14)){
        printf("Luz Visivel");
    }
        else if (I(f, 7.5e14, 3e17)){
        printf("Ultravioleta");
    }
        else if (I(f, 3e17, 3e19)){
        printf("Raios X");
    }
        else if (f > 3e19){
        printf("Raios Gama");
    }








    return 0;
}
