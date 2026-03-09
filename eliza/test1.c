/*O objetivo desta parte inicial do codigo e de abrir o ficheiro de forma dinamica e ser
capaz de o ler*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
char *getRest(char **info, char *dataBase, int count);
void removeSymbols(char * vector);
int searcher(char **info, char **dataBase, int count);
char *round_robin(char **dataBase, int count, int*responsesBlock, int Block, int* crr); 
int *crr;
int main()
{   //open the file and read it
    FILE *pfile = fopen("eliza.dat", "r");
    char buffer[1024] = {0};
    int capacity_keywords = 10;
    int capacity_responses = 10;
    char **pinitial_3 = calloc(3, sizeof(char*));
    char **pkey_words = malloc(capacity_keywords * sizeof(char*));
    char **presponses = malloc(capacity_responses * sizeof(char*));
    char **pespecial = calloc(1, sizeof(char*));
    if(pfile == NULL){
        printf("Could not open file\n");
        return 1;
    }
    /*vai salvar as informacoes vinda do ficheiro
    nos diferentes arrays de pointers*/
    //vai ver quantos blocos de palavras chaves existem ate pq esse numero vai ser igual ao de respostas e colocar num for loop
    int blocks = 0;
    while(fgets(buffer, sizeof(buffer), pfile) != NULL){
        buffer[strcspn(buffer, "\n")] = '\0';
        if(strcmp(buffer, "!") == 0) blocks++;
    }
    rewind(pfile); //volta para o inicio
    //para as 3 especiais
    int count = 0;
    while(count < 3 && fgets(buffer, sizeof(buffer), pfile) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0'; //limpa o buff pode ser que mude para outra forma de limpar o buff
            pinitial_3[count] = strdup(buffer); //copia o que se encontra no buffer para o array alocando automaticamente a memoria suficiente
            for(int i = 0; pinitial_3[count][i] != '\0'; i++){ //tranformar letra por letra em upper case para ter tudo maiusculo
                pinitial_3[count][i] = toupper(pinitial_3[count][i]);
            }
            count++;
    }
    int count_keywords = 0;
    int *pkey_words_block = malloc(blocks * sizeof(int*));
    int count_responses = 0;
    int *presponses_block = malloc(blocks * sizeof(int*));
    for(int i = 0; i < blocks; i++){
        //para as palavras chaves
        while(fgets(buffer, sizeof(buffer), pfile) != NULL){
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strcmp(buffer, "!") == 0) break; // programa vai parar quando encontrar o !
                if(count_keywords >= capacity_keywords){
                    capacity_keywords *= 2;
                    pkey_words = realloc(pkey_words, capacity_keywords * sizeof(char*));
                }
                pkey_words[count_keywords] = strdup(buffer);
                for(int i = 0; pkey_words[count_keywords][i] != '\0'; i++){
                    pkey_words[count_keywords][i] = toupper(pkey_words[count_keywords][i]);
                }
                pkey_words_block[count_keywords] = i; //vai marcar o index do bloco onde esta a palavra chave
                count_keywords++;
        }
        //para as respostas delas
        while(fgets(buffer, sizeof(buffer), pfile) != NULL){
                buffer[strcspn(buffer, "\n")] = '\0';
                if (strcmp(buffer, ".") == 0) break; // programa vai parar quando encontrar o .
                if(count_responses >= capacity_responses){
                    capacity_responses *= 2;
                    presponses = realloc(presponses, capacity_responses * sizeof(char*));
                }
                presponses[count_responses] = strdup(buffer);
                for(int i = 0; presponses[count_responses][i] != '\0'; i++){
                    presponses[count_responses][i] = toupper(presponses[count_responses][i]);
                }
                presponses_block[count_responses] = i; //vai marcar o index do bloco onde esta a resposta
                count_responses++;
        }
    }
    while(fgets(buffer, sizeof(buffer), pfile) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';
            pespecial[0] = strdup(buffer);
            for(int i = 0; pespecial[0][i] != '\0'; i++){
                pespecial[0][i] = toupper(pespecial[0][i]);
            }
    }
    fclose(pfile);
    //pode ser preciso tratar dos arrays do file para remover tbm pontuação pelo menos para keyword



    /*tudo em relação a ler o ficheiro esta feito
    hora de trabalhar com o stdin*/
    printf("%s\n", pinitial_3[0]);

    /* temos de nos preocupar com o receber input, encontrar a equivalencia em termos de keywords e rotacionar as palavras*/
    char **pinput = calloc(10, sizeof(char*)); //estou a usar aqui o calloc pq como vou precisar guardar informação convem que comece em null
    while(true){
        if(fgets(buffer, sizeof(buffer), stdin) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';  //vamos tratar o input ja no buffer para assim caso recebemos BYE ou ADEUS o programa para
            for(int i = 0; buffer[i] != '\0'; i++){
                buffer[i] = toupper(buffer[i]);
            }
            if(strcmp(buffer, "BYE") == 0){ //depois vamos ter de estudar o que fazer em relação ao adeus
            printf("%s\n", pinitial_3[2]);
            break;
            }
            removeSymbols(buffer);
            pinput[0] = strdup(buffer);
            //criar condição para caso de repeticao de input
            if(pinput[1] != NULL && strcmp(pinput[0], pinput[1]) == 0){
                printf("%s\n", pinitial_3[1]);
                continue;
            }
            if(pinput[1] != NULL) free(pinput[1]);
            pinput[1] = strdup(pinput[0]);

            int match = searcher(pinput, pkey_words, count_keywords); //vai receber o index do block onde foi encontrado a correspondencia
            if(match == -1){
               printf("\n%s", *pespecial);
               continue;
            }
            int currentBlock = pkey_words_block[match];
            char *finishResponses = getRest(pinput, pkey_words[match], count_keywords);
            if(finishResponses != NULL){
                printf("%s %s\n", round_robin(presponses, count_responses, presponses_block, currentBlock, crr), finishResponses);

            }else{
                printf("%s\n", round_robin(presponses, count_responses, presponses_block, currentBlock, crr));
            }
            //void rotation(*presponses); //a pensar em criar um array que mantem o valor da resposta para depois fazer a rotação
            //so agora para experimentacao:
        }











    }
    //limpagem de memoria do stdin
        free(pinput[0]);
        free(pinput);








































    //limpagem de memoria do dados que vinham do ficheiro
    for(int i = 0; i < 3; i++) free(pinitial_3[i]);
    free(pinitial_3);
    for(int i = 0; i < count_keywords; i++) free(pkey_words[i]);
    free(pkey_words);
    for(int i = 0; i < count_responses; i++) free(presponses[i]);
    free(presponses);
    free(pespecial[0]); //será necessario fazer este free?
    free(pespecial);

    return 0; //EXIT_SUCESS (0)
}
//este codigo com a ajuda do isalnum que remove qualquer simbolo vai remover o simbolos dos inputs stdin
void removeSymbols(char * vector){
    int i = 0;
    int j = 0;
    while(vector[i]){ //loop funciona ate encontrar o \0 porque este de todos os outros é o que possui o valor de 0 no ASCII
        if(isalnum(vector[i]) || vector[i] == ' '){ //isalnum da o valor de 1 caso encontre um numero que nao é alphanumerico
                vector[j++] = vector[i]; //j++ nao significa que começa no 1 mas sim que começa no zero e sobe depois para 1
        }
        i++;
    }
    vector[j] = '\0'; //garantir que a sting tem o seu fim marcado
}
int searcher(char **info, char **dataBase, int count){
    for(int i = 0; i < count; i++){
        char *search = strstr(info[0], dataBase[i]); //ve se encontra alguma semelhança nas strings e atribui a search
        while(search){
            bool checkBefore = (search == info[0]) || (*(search-1) == ' '); //cheka a parte detras para ver se nao ha nenhuma palavra que nao pertence
            bool checkAfter = (search[strlen(dataBase[i])] == '\0') || (search[strlen(dataBase[i])] == ' ');
            if(checkBefore && checkAfter) return i;
            search = strstr(search+1, dataBase[i]); //vai avaçando na palavra que achamos para ver se é ou nao o que queremos
        }
    }
    return -1; //este return e -1 para garantir que nunca pode ter um valor igual ao i que tbm damos return
}
char *round_robin(char **dataBase, int count, int*responsesBlock, int Block, int *crr){
    int c1 = 0;
    int c2 = 0;
   
   if(responsesBlock[*crr] != Block ){
    while(responsesBlock[c1] != Block){

        c1++;

    }
    c2 = c1;
    while(responsesBlock[c1] == Block){
    
        c1++;

    }

    *crr = c2;
}
    
    
    if(crr <= c1){
    char *result = strdup(dataBase[c2]);
    crr++;
    
    return result;
    }
}
char *getRest(char **info, char *dataBase, int count){
        char *rest = strstr(info[0], dataBase); //encontra a keyword
        if(rest != NULL){
        rest += strlen(dataBase); //vai para a frente da keyword para assim nao termos a keyword no print
        if(*rest == '\0') return NULL;
        if(*rest == ' ') rest++; //se o primeiro rest for um espaço vamos o remover
        return rest;
        }
    return NULL;
}
