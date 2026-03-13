/*Rdrigo Torres- ist1117968
Diogo Pinto - ist1117735
Grupo 121
LEEC - 25/26*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
//char *getRest(char **info, char *dataBase, int count);
//char **readFile(        );
void removeSymbols(char * vector);
int searcher(char **info, char **dataBase, int count);
char *round_robin(char **dataBase, int count, int*responsesBlock, int Block, int *crr);
int main()
{   //open the file and read it
    FILE *pfile = fopen("eliza.dat", "r");
    char buffer[1024] = {0}; //mete tudo a 0
    int capacity_keywords = 10;
    int capacity_responses = 10;
    char **pinitial_3 = calloc(12, sizeof(char*)); //como vou ignorar algum data ent meto tudo NULL para depois se der problema souber que é daqui
    char **pkey_words = malloc(capacity_keywords * sizeof(char*));
    char **presponses = malloc(capacity_responses * sizeof(char*));
    //char **pespecial = calloc(1, sizeof(char*));
    if(pfile == NULL){
        printf("Could not open file\n");
        return 1;
    }
    /*vai salvar as informacoes vinda do ficheiro
    nos diferentes arrays de pointers*/
    //vai ver quantos blocos de palavras chaves existem ate pq esse numero vai ser igual ao de respostas e colocar num for loop
    int blocks = -3; //começar a -4 para remover os ! das frases de acolhimento e do especial
    while(fgets(buffer, sizeof(buffer), pfile) != NULL){
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if(strcmp(buffer, "!") == 0) blocks++;
    }
    int *counterRound_robin = calloc(blocks, sizeof(int));
    rewind(pfile); //volta para o inicio
    //para as 3 especiais
    int count = 0;
    while(count < 12 && fgets(buffer, sizeof(buffer), pfile) != NULL){
            //o if ignora tudo e que nao sao as palavras de acolhimento
            if(count != 0 || count != 1 || count != 3 || count != 4 || count != 5 || count != 7 || count != 8 || count != 9 || count != 11){
            buffer[strcspn(buffer, "\r\n")] = '\0'; //limpa o buff pode ser que mude para outra forma de limpar o buff
            pinitial_3[count] = strdup(buffer); //copia o que se encontra no buffer para o array alocando automaticamente a memoria suficiente
            for(int i = 0; pinitial_3[count][i] != '\0'; i++){ //tranformar letra por letra em upper case para ter tudo maiusculo
                pinitial_3[count][i] = toupper(pinitial_3[count][i]);
            }
            count++;
            } else count++;
    }
    int count_keywords = 0;
    int *pkey_words_block = malloc(blocks * sizeof(int));
    int count_responses = 0;
    int *presponses_block = malloc(blocks * sizeof(int));
    for(int i = 0; i < blocks; i++){
        //para as palavras chaves
        while(fgets(buffer, sizeof(buffer), pfile) != NULL){
                buffer[strcspn(buffer, "\r\n")] = '\0';
                if (strcmp(buffer, "!") == 0) break; // programa vai parar quando encontrar o !
                if(count_keywords >= capacity_keywords){
                    capacity_keywords *= 2;
                    pkey_words = realloc(pkey_words, capacity_keywords * sizeof(char*));
                    pkey_words_block = realloc(pkey_words_block, capacity_keywords * sizeof(int));
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
                buffer[strcspn(buffer, "\r\n")] = '\0';
                if (strcmp(buffer, ".") == 0) break; // programa vai parar quando encontrar o .
                if(count_responses >= capacity_responses){
                    capacity_responses *= 2;
                    presponses = realloc(presponses, capacity_responses * sizeof(char*));
                    presponses_block = realloc(presponses_block, capacity_responses * sizeof(int));
                }
                presponses[count_responses] = strdup(buffer);
                for(int i = 0; presponses[count_responses][i] != '\0'; i++){
                    presponses[count_responses][i] = toupper(presponses[count_responses][i]);
                }
                presponses_block[count_responses] = i; //vai marcar o index do bloco onde esta a resposta
                count_responses++;
        }
    }
    /*while(fgets(buffer, sizeof(buffer), pfile) != NULL){
            buffer[strcspn(buffer, "\r\n")] = '\0';
            pespecial[0] = strdup(buffer);
            for(int i = 0; pespecial[0][i] != '\0'; i++){
                pespecial[0][i] = toupper(pespecial[0][i]);
            }
    }*/
    fclose(pfile);
    /*tudo em relação a ler o ficheiro esta feito
    hora de trabalhar com o stdin*/
    //int * counter_blocks = calloc(blocks, sizeof(int*)); //serve para saber em qual rotação estamos em cada bloco existente e começa em 0
    printf("%s\n", pinitial_3[2]);
    /* temos de nos preocupar com o receber input, encontrar a equivalencia em termos de keywords e rotacionar as palavras*/
    char **pinput = calloc(10, sizeof(char*)); //estou a usar aqui o calloc pq como vou precisar guardar informação convem que comece em null
    while(true){
        if(fgets(buffer, sizeof(buffer), stdin) == NULL) break;
            buffer[strcspn(buffer, "\r\n")] = '\0';  //vamos tratar o input ja no buffer para assim caso recebemos BYE ou ADEUS o programa para
            if(buffer[0] == '\0') continue;
            for(int i = 0; buffer[i] != '\0'; i++){
                buffer[i] = toupper(buffer[i]);
            }
            if(strcmp(buffer, "BYE") == 0){ //depois vamos ter de estudar o que fazer em relação ao adeus
            printf("%s\n", pinitial_3[10]);
            break;
            }
            removeSymbols(buffer);
            bool isNothing = true; //podera ser adicicinado dentro de removeSymbols e serve para ver se é apenas espaços ou nao
            for(int i = 0; buffer[i] != '\0'; i++){
                if(buffer[i] != ' '){
                    isNothing = false;
                    break;
                }
            }
            if(isNothing) continue;
            pinput[0] = strdup(buffer);
            //criar condição para caso de repeticao de input
            if(pinput[1] != NULL && strcmp(pinput[0], pinput[1]) == 0){ //caso o ultimo input seja igual ao input atual
                printf("%s\n", pinitial_3[6]);
                free(pinput[0]);
                continue;
            }
            if(pinput[1] != NULL) free(pinput[1]); //liberta o ultimo input
            pinput[1] = strdup(pinput[0]); //guarda o input atual

            int match = searcher(pinput, pkey_words, count_keywords); //vai receber o index da keyword onde foi encontrado a correspondencia
            if(match == -1) match = count_keywords - 1; //vamos pegar  no ultima string de todas dentro do array de keywords para obtermos o index do bloco
            int currentBlock = pkey_words_block[match]; //obter o index do block onde esta a correspondencia
                //char *finishResponses = getRest(pinput, pkey_words[match], count_keywords);
                /*if(finishResponses != NULL){
                printf("%s %s\n", round_robin(presponses, count_responses, presponses_block, currentBlock, counterRound_robin), finishResponses);
                */
                //}else{
                char *resp = round_robin(presponses, count_responses, presponses_block, currentBlock, counterRound_robin);
                printf("%s\n", resp);
                free(resp);

        free(pinput[0]); //limpagem de memoria do stdin
    }
    //limpagem de memoria do stdin
    if(pinput[1] != NULL) free(pinput[1]);
    free(pinput);
    //limpagem de memoria do dados que vinham do ficheiro
    free(counterRound_robin);
    for(int i = 0; i < 12; i++) free(pinitial_3[i]);
    free(pinitial_3);
    for(int i = 0; i < count_keywords; i++) free(pkey_words[i]);
    free(pkey_words);
    for(int i = 0; i < count_responses; i++) free(presponses[i]);
    free(presponses);
    //free(pespecial[0]);
    //free(pespecial);
    free(pkey_words_block);
    free(presponses_block);

    //return 0; //EXIT_SUCESS (0)
    exit(EXIT_SUCCESS);
}
//este codigo com a ajuda do isalnum que remove qualquer simbolo vai remover o simbolos dos inputs stdin
void removeSymbols(char * vector){
    int i = 0;
    int j = 0;
    bool repeatedSpaces = false;
    while(vector[i]){ //loop funciona ate encontrar o \0 porque este de todos os outros é o que possui o valor de 0 no ASCII
        if(isalnum(vector[i])){ //isalnum da o valor de 0 caso encontre algo que nao e alphanumerico
                vector[j++] = vector[i]; //j++ nao significa que começa no 1 mas sim que começa no zero e sobe logo de seguida para 1
                repeatedSpaces = false;
        }
        if(vector[i] == ' '){ //caso seja um espaço temos de ver pq queremos manter os espaços mas remover os repetidos
            if(!repeatedSpaces){ //o ultimo char era uma letra ou numero qualquer
                vector[j++] = vector[i];
                repeatedSpaces = true; //comeca a ser verdade para assim no caso de haver outro espaco seguido ele nao vai ser colocado na string
            }
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
            search = strstr(search+1, dataBase[i]); //vai avaçando na palavra que achamos para ver se e ou nao o que queremos
        }
    }
    return -1; //este return e -1 para garantir que nunca pode ter um valor igual ao i que tbm damos return
}
char *round_robin(char **dataBase, int count, int*responsesBlock, int Block, int *crr){
    int block_min = -1;
    int block_size = 0;
    for(int i = 0; i < count; i++){
        if( responsesBlock[i] == Block){
            if (block_min == -1) block_min = i; //armaneza o array de resposta onde o bloco começa
            block_size++; //vai armanezar quantas respostas existem dentro do bloco
        }
    }
    //se o valor do bloco tiver um index menor que o inicio ou se ja tiver chegado ao fim do bloco ele reseta
    if(crr[Block] < block_min || crr[Block] >= block_min + block_size) crr[Block] = block_min;
    char *result = strdup(dataBase[crr[Block]]);
    crr[Block]++; //incrementa o valor do index dentro do bloco em 1 para assim haver a rotatividade esperada
    return result;
}
/*char *getRest(char **info, char *dataBase, int count){
        char *rest = strstr(info[0], dataBase); //encontra a keyword na string
        if(rest != NULL){
        rest += strlen(dataBase); //vai para a frente da keyword para assim nao termos a keyword no print
        if(*rest == '\0') return NULL;
        if(*rest == ' ') rest++; //se o primeiro rest for um espaço vamos o remover
        return rest;
        }
    return NULL; //por boa pratica devemos returnar sempre algo no fim do codigo mesmo que pareça impossivel chegar ate aqui
}*/
