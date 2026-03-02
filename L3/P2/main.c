
#include <stdio.h>
#include <math.h>



//definir a função usando o fact() 
#define F( n, k) ( fact(n)/ ( fact(k) * fact((n) - (k)) ) )
//criar a função que calcula o fatorial de numeros
unsigned long fact(int n) {

    unsigned long res = 1;
    
    
    if ( n >= 0){
        for(int i = 1; i <= n ;  i ++ ){

            res *= i;

        }
    }


    return res;
}


int main () {

    int i = 0;
    int f = 0;

    printf("M: " );
    scanf( "%d", &i);

    
    
    
    
    
    
    //um loop para fazer i números de linhas
    
    for ( int n = 0; n < i; n++) {
        
        
        
            
         //outro loop para k número de colunas e calcular os valores   
        for ( int k = 0; k <= n; k++) {
                    
            f = F( n, k);
             printf("%d ", f) ;
        }

        
        printf( "\n") ;
    } 






    return 0;
}
