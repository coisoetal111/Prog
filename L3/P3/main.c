#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>




int main(){

    int n = 0;
    int k = 10;
    int c0 = 0;
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    int c4 = 0;
    int c5 = 0;
    int c6 = 0;
    int c7 = 0;
    int c8 = 0;
    int c9 = 0;

    float num_aleatorios[100];
    int interv[100];
    
    printf("n: ");
    scanf("%d", &n);
    printf("k: ");
    scanf("%d", &k);
    int aux = n;

    srand(time(NULL));


    while(k > 9 || k < 0){

        printf("k tem de ser um número entre 0 e 9");
        scanf("%d", &k);

    }

    while (n > 0)
    {
        
        num_aleatorios[n - 1] = (rand() % 101)/100.0;
        n--;
    }


    for (int i = 0; i < aux; i++)
    {
         interv[i] = k * num_aleatorios[i];
        if (interv[i] == k ){

            interv[i] = k-1;

        }

    }

    for (int i = 0; i < aux; i++)
    {
        
        switch (interv[i])
        {
        case 0:
        c0++;
        break;
        case 1:
        c1++;
        break;
        case 2:
        c2++;
        break;
        case 3:
        c3++;
        break;
        case 4:
        c4++;
        break;
        case 5:
        c5++;
        break;
        case 6:
        c6++;
        break;
        case 7:
        c7++;
        break;
        case 8:
        c8++;
        break;
        case 9:
        c9++;
        break;

        
        default:
            break;
        }
        

    }


    for(int i = aux; i > 0; i--){

        if (c0 >= i)
        {
            printf("*");
        } else {
            printf(" ");

        }

         if (c1 >= i)
        {
            printf("*");
        } else {
            printf(" ");

        }

         if (c2 >= i)
        {
            printf("*");
        } else {
            printf(" ");

        }

         if (c3 >= i)
        {
            printf("*");
        } else {
            printf(" ");

        }

         if (c4 >= i)
        {
            printf("*");
        } else {
            printf(" ");

        }

         if (c5 >= i)
        {
            printf("*");
        } else {
            printf(" ");

        }

         if (c6 >= i)
        {
            printf("*");
        } else {
            printf(" ");

        }

         if (c7 >= i)
        {
            printf("*");
        } else {
            printf(" ");

        }

         if (c8 >= i)
        {
            printf("*");
        } else {
            printf(" ");

        }

         if (c9 >= i)
        {
            printf("*");
        } else {
            printf(" ");

        }
        

        printf("\n");


    }



    
    
    


}