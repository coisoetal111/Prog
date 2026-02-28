#include <stdio.h>
#include <stdlib.h>

int main()
{

    int n = 0;
    float m = 0.;
    int soma = 0;
    int i = 1;

    scanf("%d", &n);

    for(i; i <= n; i++){

        if( n%i == 0){

            printf("%d ", i);

            soma += i;

            m++;
        }

    }

    m = soma / m;

    printf("a media e: %f", m);


    return 0;
}
