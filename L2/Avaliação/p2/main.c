

/*Escreva um programa que leia dois tempos, cada um especificado em horas (0-23), minutos (0-59) e segundos
(0-59); sendo o primeiro tempo maior do que o segundo, determine a diferença entre eles e escreva-a, também,
em horas, minutos e segundos.*/




#include <stdio.h>
#include <stdlib.h>

int main()
{
   int horasf = 0, horass = 0, minf = 0, mins = 0, secf = 0, secs = 0;
   int s = 0, m = 0, h = 0, r = 0;

   printf("O primeiro número de horas é:");

   scanf("%d", &horasf);

   printf("O primeiro número de minutos é:");

   scanf("%d", &minf);
   printf("O primeiro número de segundos é:");

   scanf("%d", &secf);
   printf("O segundo número de horas é:");

   scanf("%d", &horass);
   printf("O sgundo número de minutos é:");

   scanf("%d", &mins);
   printf("O segundo número de segundos é:");

   scanf("%d", &secs);

   /* transformar a input num número só em segundos */

   horasf = horasf * 3600;
   horass = horass * 3600;
   minf = minf * 60;
   mins = mins * 60;
   secf = secf + horasf + minf;
   secs = secs + horass + mins;
   r = secf - secs;


    if(r >= 0){

    /* usei o código do ex. 1 para transformar o resultado em horas minutos e segundos */

    h = r/3600;
    m = r%3600;

    s = m%60;
    m = m/60;
    printf("A diferença entre os dois tempos é: %d horas " , h);
    printf("%d minutos " , m);
    printf("%d segundos", s);
    }






    return 0;
}
