/* Escreva um programa para ler, separadamente, três caracteres correspondentes a dígitos decimais (algarismos)
e escreva o dobro do número inteiro cujos algarismos são os caracteres lidos. */



#include <stdio.h>
#include <stdlib.h>

int main()
{
    int f = 0, s = 0, t = 0, n = 0;


    printf("primeiro algarismo: ");
    scanf ("%d", &f);
     printf("segundo algarismo: ");
    scanf ("%d", &s);
     printf("terceiro algarismo: ");
    scanf ("%d", &t);

    if ( 0 <= f <=9 && 0 <= s <=9 && 0 <= t <=9){

        n = 2*( f * 100 + s * 10 + t);

        printf("%d", n);

    }

    return 0;
}
