#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    //inicializar o código com um valor que n perturba o código
    int resp = -1;
    
    // enquanto o utilizador não responder "0" o código continua a rodar
    while( resp != 0 ) {
        //de forma a que a seed seja aleatória é criada a a partir do tempo no relógio do pc
        srand(time(NULL));

        int n1 = (rand() % 9) + 1;
        int n2 = (rand() % 9) + 1;
    

        printf(" %d x %d = ", n1, n2);
    
    
    
        scanf("%d" , &resp);


        
        while(resp != n1 * n2 && resp != 0){

            printf("Tenta outra vez\n");
            scanf("%d", &resp);

        }
        if ( resp == n1 * n2){


            printf("Boa!\n");


        }


    }



    return 0;


}