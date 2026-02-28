/* Escreva um programa que receba o número de total de segundos como um inteiro e imprima o número total de
horas, minutos e segundos correspondente. Não utilize quaisquer condições ou ciclos.
 */

#include <stdio.h>

int main() {
    int s = 0, m = 0, h = 0, r = 0;
    scanf("%d" , &r);



    h = r/3600;


    m = r%3600;

    s = m%60;
    m = m/60;
    printf("%d horas " , h);
    printf("%d minutos " , m);
    printf("%d segundos", s);



    return 0;
}
