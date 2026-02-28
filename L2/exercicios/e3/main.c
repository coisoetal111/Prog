#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    scanf("%d", &n);


    for(int i = 1; i <= n; i++){

        for(int h = 1; h <= i; h++){

            printf("*");
        }

        printf("\n");
    }



    for(int j = n; j > 1; j--){

        for(int k = j - 1; k > 1; k--){

            printf("*");
        }

        printf("\n");
    }




    return 0;
}
