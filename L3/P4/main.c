#include <stdio.h>
#include <stdlib.h>




int main(){

    printf("numero a ser codificado: ");

    
    
    char number[500];
    int n = 0;
    
    
    int i = 0;
    int count = 1;

    scanf("%s", number);


    printf("Comprimento do número: ");

    scanf("%d", &n);

    int numeros[n];
    

    



    while(number[i] != '\0'){

        numeros[i] = number[i] - 48;
        i++;

    }


    char result[i+1];
    int countr = 0;


    for (int j = 0; j < i; j++)
    {
        if(numeros[j] == numeros[j+1] && count != 9){
            count++;


        }else if(count == 9){
            result[countr] = count + 48;
            countr++;
            result[countr] = numeros[j] + 48;
            countr++;
            count = 1;


        }else{
            
            
            result[countr] = count + 48;
            countr++;
            result[countr] = numeros[j] + 48;
            countr++;
            count = 1;


        }
    }

    result[countr] = '\0';

    printf("\n%s", result);
    


    int r = 0, s = 1, p = 0;
    char decode[100];
    

    while(s < countr)
    {
        for (int i = 0; i < result[r] - 48; i++)
        {
            decode[p] = result[s];
            p++;
        }

        s += 2;
        r += 2;


        
    }

    decode[p] = '\0';


    printf("\n%s", decode);
    
    







    return 0;

}

