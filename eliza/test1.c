/*Rodrigo Torres- ist1117968
Diogo Pinto - ist1117735
Grupo 121
LEEC - 25/26*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
char *getRest(char **info, char *dataBase, int count);
//char **readFile(        );
void removeSymbols(char * vector);
int searcher(char *info, char **dataBase, int count);
char *round_robin(char **dataBase, int count, int*responsesBlock, int Block, int *crr);
char *conjution(char * response, bool is_portuguese);
int main(int argc, char **argv)
{

    //terminal handler
    char *filename = "eliza.dat";
    FILE *output = stdout;
    FILE *input = stdin;
    FILE *log = NULL;
    int terhandler;
    bool is_portuguese = false;//para saber depois na conjução se é em portugues ou não
    while ((terhandler = getopt(argc, argv, "hi:o:l:f:p:")) != -1)
  {
    switch (terhandler)
      {
      case 'h':
        printf("Arguments:\n-h\t\tmostra a ajuda para o utilizador(esta mensagem) e termina\n");
        printf("-i[filename]\tnome do ficheiro de entrada, em alternativa a stdin\n");
        printf("-o[filename]\tnome do ficheiro de saída, em alternativa a stdout\n");
        printf("-l[filename]\tfazer log do input e output para o ficheiro filename\n");
        printf("-i[filename]\tusar ficheiro filename com base de dados de respostas em vez de \"eliza.dat\"\n");
        printf("-p\t\tusar regras de português, em vez de inglês\n");
        break;
      case 'i':
       input = fopen(optarg, "r");
                if (input == NULL) {
                    fprintf(stderr, "Erro ao abrir o ficheiro %s", optarg);
                    exit(EXIT_FAILURE);
                }

        break;
      case 'o':
        output = fopen(optarg, "w");
                if (output == NULL) {
                    fprintf(stderr, "Erro ao abrir o ficheiro %s", optarg);
                    exit(EXIT_FAILURE);
                }
        //supostamente cria um ficheiro com o nome dado e escreve o output aí
        //testado e a funcionar (espero eu)
        break;
        case 'l':
        log = fopen(optarg, "w");
                if (log == NULL) {
                    fprintf(stderr, "Erro ao abrir o ficheiro %s", optarg);
                    exit(EXIT_FAILURE);
                }
        break;
      case 'f':
       filename = optarg;
        break;
      case 'p':
        is_portuguese = true;
        //Português ao invés de inglês
        // para ser honesto n sei como hei de fzr isto portanto boa sorte Torres☆*: .｡. o(≧▽≦)o .｡.:*☆
        break;




        case '?':
        if (optopt == 'i' || optopt == 'l' || optopt == 'o' || optopt == 'f')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
            return 1;
      default:
        abort ();
    }


}

















    //open the file and read it
    FILE *pfile = fopen(filename, "r");
    char buffer[1024] = {0}; //mete tudo a 0
    int capacity_keywords = 10;
    int capacity_responses = 10;
    char **pinitial_3 = calloc(12, sizeof(char*)); //como vou ignorar algum data ent meto tudo NULL para depois se der problema souber que é daqui
    char **pkey_words = malloc(capacity_keywords * sizeof(char*));
    char **presponses = malloc(capacity_responses * sizeof(char*));
    //char **pespecial = calloc(1, sizeof(char*));
    if(pfile == NULL){
        printf("Could not open file\n");
        exit(EXIT_FAILURE);
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
    fprintf(output, "%s\n", pinitial_3[2]);


    if(log != NULL) fprintf(log, "%s\n", pinitial_3[2]); //escrever as inputs no log
    /* temos de nos preocupar com o receber input, encontrar a equivalencia em termos de keywords e rotacionar as palavras*/
    char **pinput = calloc(10, sizeof(char*)); //estou a usar aqui o calloc pq como vou precisar guardar informação convem que comece em null
    while(true){
        if(fgets(buffer, sizeof(buffer), input) == NULL) break;
            if(log != NULL) fprintf(log, "%s\n", buffer); //escrever as inputs no log
            buffer[strcspn(buffer, "\r\n")] = '\0';  //vamos tratar o input ja no buffer para assim caso recebemos BYE ou ADEUS o programa para
            if(buffer[0] == '\0') continue;
            for(int i = 0; buffer[i] != '\0'; i++){
                buffer[i] = toupper(buffer[i]);
            }
            removeSymbols(buffer);
            if(strcmp(buffer, "\0") == 0) continue; // caso o input seja so espaços
            if(strcmp(buffer, is_portuguese ? "ADEUS":"BYE") == 0){ //falta meter o is_portuguese aqui para depois funcionar para o adeus
                fprintf(output, "%s\n", pinitial_3[10]);
                if(log != NULL) fprintf(log, "%s\n", pinitial_3[10]);// escrever output no log

                break;
            }
            /*if(!is_portuguese && strcmp(buffer, "BYE") == 0){ //falta meter o is_portuguese aqui para depois funcionar para o adeus
                fprintf(output, "%s\n", pinitial_3[10]);
                if(log != NULL) fprintf(log, "%s\n", pinitial_3[10]);// escrever output no log

                break;
            }
            */
            pinput[0] = strdup(buffer);
            //criar condição para caso de repeticao de input
            if(pinput[1] != NULL && strcmp(pinput[0], pinput[1]) == 0){ //caso o ultimo input seja igual ao input atual
                fprintf(output, "%s\n", pinitial_3[6]);
                if(log != NULL) fprintf(log, "%s\n", pinitial_3[6]);// escrever output no log
                free(pinput[0]);
                continue;
            }
            if(pinput[1] != NULL) free(pinput[1]); //liberta o ultimo input
            pinput[1] = strdup(pinput[0]); //guarda o input atual

            int match = searcher(pinput[0], pkey_words, count_keywords); //vai receber o index da keyword onde foi encontrado a correspondencia
            if(match == -1) match = count_keywords - 1; //vamos pegar  no ultima string de todas dentro do array de keywords para obtermos o index do bloco
            int currentBlock = pkey_words_block[match]; //obter o index do block onde esta a correspondencia
                //char *finishResponses = getRest(pinput, pkey_words[match], count_keywords);
                /*if(finishResponses != NULL){
                printf("%s %s\n", round_robin(presponses, count_responses, presponses_block, currentBlock, counterRound_robin), finishResponses);
                */
                //}else{
            char *resp = round_robin(presponses, count_responses, presponses_block, currentBlock, counterRound_robin);
            //bool ISAsterisk = false
            char *asterisk = strchr(resp, '*');
            if(asterisk != NULL){
                char *rest = getRest(pinput, pkey_words[match], count_keywords);
                char *finishResponses = conjution(rest, is_portuguese);
                if(finishResponses != NULL){
                    char *final_of_string = strdup(asterisk + 1); //passa para uma sting todo o resto depois do *
                    *asterisk = '\0'; //remove o * no resp ja que estes estao associados pelo mesmo adereco
                    int size = strlen(finishResponses) + strlen(resp) + strlen(final_of_string) + 1;
                    resp = realloc(resp, size * sizeof(char));
                    strcat(resp, finishResponses);
                    strcat(resp, final_of_string);
                    free(finishResponses);
                    free(final_of_string);
                }
            }
                fprintf(output, "%s\n", resp);
                if(log != NULL) fprintf(log, "%s\n", resp);// escrever output no log
                free(resp);
                free(pinput[0]); //limpagem de memoria do stdin
    }
    //fechar os ficheiros do terminal
    fclose(output);
    fclose(input);
    fclose(log);



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
    bool repeatedSpaces = true; //começa true pq nao queremos espacos no inicio da string
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
    if(j > 0 && vector[j-1] == ' ') j--;
    vector[j] = '\0'; //garantir que a sting tem o seu fim marcado
}
int searcher(char *info, char **dataBase, int count){
    for(int i = 0; i < count; i++){
        char *search = strstr(info, dataBase[i]); //ve se encontra alguma semelhança nas strings e atribui a search
        while(search){
            bool checkBefore = (search == info) || (*(search-1) == ' '); //cheka a parte detras para ver se nao ha nenhuma palavra que nao pertence
            bool checkAfter = (search[strlen(dataBase[i])] == '\0') || (search[strlen(dataBase[i])] == ' ');//isto cheka a que tem a frente da palavra
            //bool isAsteriskyou = (search[strlen(dataBase[i])] == '*');
            //if(isAsteriskyou) return 15;
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
char *getRest(char **info, char *dataBase, int count){
        char *rest = strstr(info[0], dataBase); //encontra a keyword na string
        if(rest != NULL){
        rest += strlen(dataBase); //vai para a frente da keyword para assim nao termos a keyword no print
        if(*rest == '\0') return NULL;
        //if(*rest == ' ') rest++; //se o primeiro rest for um espaço vamos o remover
        return rest;
        }
    return NULL; //por boa pratica devemos returnar sempre algo no fim do codigo mesmo que pareça impossivel chegar ate aqui
}
char *conjution(char * response, bool is_portuguese){
    //char **conjution = malloc(15 * sizeof(char*)); //para o que que a palavra tem de se substituir para
    //char **cases = malloc(14 * sizeof(char*)); //que palavras vao ser substituidas
    // 1. Define English mappings (Removed YOU so we can handle it specially)
    if(response == NULL) return NULL; //porque pode ser que o getrest tenha returnado nada e nos nao querremos quebrar o flow no main
    char *en_cases[] = {"ARE", "AM", "WERE", "WAS", "I", "YOUR", "MY", "IVE", "YOUVE", "IM", "ME", "US", "WE"};
    char *en_conj[]  = {"AM", "ARE", "WAS", "WERE", "YOU", "MY", "YOUR", "YOUVE", "IVE", "YOURE", "YOU", "YOU", "YOU"};
    int en_count = 13;

    // 2. Define Portuguese mappings (from your project guidelines)
    char *pt_cases[] = {"EU", "TU", "COMIGO", "CONTIGO", "TEU", "SEU", "MEU", "TEUS", "SEUS", "MEUS", "TUA", "SUA", "MINHA", "TUAS", "SUAS", "MINHAS", "MIM", "TI"};
    char *pt_conj[]  = {"TU", "EU", "CONTIGO", "COMIGO", "MEU", "MEU", "TEU", "MEUS", "MEUS", "TEUS", "MINHA", "MINHA", "TUA", "MINHAS", "MINHAS", "TUAS", "TI", "MIM"};
    int pt_count = 18;

    // mudar isto talvez mas serve para escolher qual usar
    char **cases = is_portuguese ? pt_cases : en_cases;
    char **conj  = is_portuguese ? pt_conj : en_conj;
    int count    = is_portuguese ? pt_count : en_count;
    char *new_resp = calloc(strlen(response) * 2 + 2, sizeof(char)); //criar a nova resposta tendo cuidado com o facto que a nova resposta pode ter mais bits que a anterior devido a por exemplo passar de I para YOU
    if(response[0] == ' ') strcpy(new_resp, " "); //adiciona o espaco vazio que existe no inicio da string
    char *word = strtok(response, " "); //basicamente separa a string em tipo varias caixas com palavras dentro, essa separacao e feita onde ha os ' '

    while(word != NULL) {
        char *next_word = strtok(NULL, " "); //salta para a proxima "caixa"
        bool isLast = (next_word == NULL); //se for null ou seja a string acabou sabemos que a atual e a ultima e isso ajuda no caso do you
        bool replaced = false; //saber se ja foi substituida ou nao na string


        if (!is_portuguese && strcmp(word, "YOU") == 0) { //para o caso especial do you que pode dar dois outputs diferentes
            if (isLast) strcat(new_resp, "ME");
            else strcat(new_resp, "I");
            replaced = true;
        }
        else {
            for(int i = 0; i < count; i++) {
                if(strcmp(word, cases[i]) == 0) {
                    strcat(new_resp, conj[i]);
                    replaced = true;
                    break; //para o for porque ja encontramos a conjucao
                }
            }
        }
        if(!replaced) {  //se nao for algo para substituir ent mantem-se
            strcat(new_resp, word);
        }
        if(!isLast) { //enqaunto nao for a ultima palavra metemos um espaco depois
            strcat(new_resp, " ");
        }
        word = next_word; //avançar para o proximo, nao temos aqui o strtok(NULL, " ") porque precisamos dele para o isLast e por isso ja tinhamos o usado
    }
    //free(response); //libertar o espaco da antiga
    return new_resp;
    }

    /*for(int i = 0; i < 14; i++){
        char *search = strstr(response[0], cases[i]);
    }*/

/*for(int i = 0; i < 15; i++) free(conjution[i]);
free(conjution);
for(int i = 0; i < 14; i++) free(cases[i]);
free(cases);
}*/
