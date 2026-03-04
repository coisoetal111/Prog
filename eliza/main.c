/*O objetivo desta parte inicial do codigo e de abrir o ficheiro de forma dinamica e ser
capaz de o ler*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
//char remove_symbol(char buffer);
void removeSymbols(char * vector);
int searcher(char **info, char **dataBase, int count);
int main()
{   //open the file and read it
    FILE *pfile = fopen("file.txt", "r");
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
    //para as palavras chaves
    int count_keywords = 0;
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
            count_keywords++;
    }
    //para as respostas delas
    int count_responses = 0;
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
            count_responses++;
    }
    while(fgets(buffer, sizeof(buffer), pfile) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';
            pespecial[0] = strdup(buffer);
            for(int i = 0; pespecial[0][i] != '\0'; i++){
                pespecial[0][i] = toupper(pespecial[0][i]);
            }
    }
    fclose(pfile);




    /*tudo em relação a ler o ficheiro esta feito
    hora de trabalhar com o stdin*/
    printf("%s\n", pinitial_3[0]);

    /* temos de nos preocupar com o receber input, encontrar a equivalencia em termos de keywords e rotacionar as palavras*/
    char **pinput = malloc(sizeof(char*));
    while(true){
        if(fgets(buffer, sizeof(buffer), stdin) != NULL){
            buffer[strcspn(buffer, "\n")] = '\0';  //vamos tratar o input ja no buffer para assim caso recebemos BYE ou ADEUS o programa para
            for(int i = 0; buffer[i] != '\0'; i++){
                buffer[i] = toupper(buffer[i]);
            }
            if(strcmp(buffer, "BYE") == 0){ //depois vamos ter de estudar o que fazer em relação ao adeus
            printf("\n%s", pinitial_3[2]);
            break;
            }
            removeSymbols(buffer);
            pinput[0] = strdup(buffer);
            int match = searcher(pinput, pkey_words, count_keywords);
            if(!match) printf("\n%s", *pespecial);
        }








        //limpagem de memoria do stdin
        free(pinput);
    }








































    //limpagem de memoria do dados que vinham do ficheiro
    for(int i = 0; i < 3; i++) free(pinitial_3[i]);
    free(pinitial_3);
    for(int i = 0; i < count_keywords; i++) free(pkey_words[i]);
    free(pkey_words);
    for(int i = 0; i < count_responses; i++) free(presponses[i]);
    free(presponses);
    free(pespecial[0]); //será necessario fazer este free?
    free(pespecial);

    return 0;
    //EXIT_SUCESS (0);
}
//este codigo com a ajuda do isalnum que remove qualquer simbolo vai remover o simbolos dos inputs stdin
void removeSymbols(char * vector){
    int i = 0;
    int j = 0;
    while(vector[i]){ //loop funciona ate encontrar o \0 porque este de todos os outros é o que possui o valor de 0 no ASCII
        if(isalnum(vector[i]) || vector[i] == ' '){
                vector[j++] = vector[i]; //j++ nao significa que começa no 1 mas sim que começa no zero e sobe depois para 1
        }
        i++;
    }
    vector[j] = '\0'; //garantir que a sting tem o seu fim marcado
}
int searcher(char **info, char **dataBase, int count){
    int match = 0;
    char *search = strtok(info[0], " "); //"divide" as palavra separadas com os espaços e da ao search apenas uma palavra a antes do 1 espaço
    while(search){
        for(int i = 0; i < count; i++){
            if(strcmp(search, dataBase[i]) == 0){
                match = 1; //tem uma resposta. este codigo deve ser aprimorado ou ate respensado para depois cumprir com os objetivos
                break;
            }
            search = strtok(NULL, " "); //faz com que comece no \0 que tinha parado pela primeira fez e procure o proximo espaço ou o fim

        }
        free(search);
    }
    //if(!match) printf("\n%s", pes)
    return match;
}
