#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

typedef struct _Run_Results {
    char *pos;
    char *esc;
    char *pos_esc;
    char *dorsal;
    char *nome;
    char *sexo;
    char *tempo;
    struct _Run_Results *next;
} Run_Results;

Run_Results *final_info(char *file);
Run_Results *_info(char *line);
Run_Results *insert_info(Run_Results *info_head, Run_Results *info);
void free_lista(Run_Results *info_head);
void escs(char*, Run_Results *info_head);
void nomes(char*, Run_Results *info_head);



int main(int argc, char **argv) {
    Run_Results *total_info;
    char *filename = "RunResults.txt";
    int terhandler;
    int n = 0;
    int e = 0;
    char* nome;
    char *esc;


     while ((terhandler = getopt(argc, argv, "hi:e:n:")) != -1)
  {
    switch (terhandler)
      {
      case 'h':
        printf("Arguments:\n-h\t\tmostra a ajuda para o utilizador(esta mensagem) e termina\n");
        printf("-i[filename]\tusar ficheiro de entrada “ficheiro” em vez de “RunResults.txt”, por omissão\n");
        printf("-e[filename]\tpesquisar o “escalão”, mostrando a informação dos participantes desse escalão\n");
        printf("-n[filename]\tpesquisar o “nome” do participante, mostrando a informação dos participantes que tenham esse “nome” ou partes desse “nome”. Note que, se quiser pesquisar um nome e apelido, deve pôr o nome dentro de aspas, para que o programa receba apenas uma única string (sem as aspas)\n");
        
        break;
      case 'e':
        e = 1;
        esc = optarg;
        break;
        case 'n':
        n = 1;
        nome = optarg;
        break;
      case 'i':
       filename = optarg;
        break;
      
        case '?':
        if (optopt == 'i' || optopt == 'e' || optopt == 'n')
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
    total_info = final_info(filename);
    if(n == 1) nomes(nome, total_info);
    if(e == 1) escs(esc, total_info);
    free_lista(total_info);
}

Run_Results *final_info(char *file) {
    Run_Results *info, *info_head = NULL;
    FILE *fptr = fopen(file, "r");
    int count = -1, size = 256;
    char temp[size], *token;

    if (fptr == NULL) {
        printf("Erro ao abrir o ficheiro com o nome: %s\n", file);
        exit(EXIT_FAILURE);
    }
    while (fgets(temp, size, fptr) != NULL) {
        if (count == -1) {
            count++;
            continue;
        }
        info = _info(temp);
        info_head = insert_info(info_head, info);
    }

    fclose(fptr);

    

    return info_head;

}

Run_Results *_info(char *line) {
    Run_Results *info;
    char *token;
    int position = 0;

    if ((info = (Run_Results*) calloc(1, sizeof(Run_Results))) == NULL) {
        printf("Erro ao alocar a memoria.\n");
        exit(EXIT_FAILURE);
    }

    char **ptr[] = {&info->pos, &info->esc, &info->pos_esc, &info->dorsal, &info->nome, &info->sexo, &info->tempo};
    token = strtok(line, "\t");

    while (token != NULL) {
        token[strcspn(token, "\n")] = '\0';
        if ((*ptr[position] = malloc(strlen(token)+1)) == NULL) {
            printf("Erro ao alocar memoria no malloc.\n");
            exit(EXIT_FAILURE);
        }
        strcpy(*ptr[position], token);
        position++;
        token = strtok(NULL, "\t");
    }
    info->next = NULL;

    return info;
}

Run_Results *insert_info(Run_Results *info_head, Run_Results *info) {
    Run_Results *AuxT;

    if (info_head == NULL) {
        info_head = info;
    } else {
        AuxT = info_head;
        while (AuxT->next != NULL)
            AuxT = AuxT->next;
        AuxT->next = info;
    }

    return info_head;
}


void free_lista(Run_Results *info_head) {
    Run_Results *Aux;

    Aux = info_head;
    while (info_head != NULL) {
        Aux = info_head;
        info_head = info_head->next;
        free(Aux->pos);
        free(Aux->esc);
        free(Aux->pos_esc);
        free(Aux->dorsal);
        free(Aux->nome);
        free(Aux->sexo);
        free(Aux->tempo);
        free(Aux);
    }
}

void nomes(char* nome, Run_Results *info_head){

    Run_Results *Aux = info_head;

    while (Aux != NULL)
    {
       if(strstr(nome,Aux->nome) != NULL || strstr(Aux->nome,nome) != NULL) printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", Aux->pos, Aux->esc, Aux->pos_esc, Aux->dorsal, Aux->nome, Aux->sexo, Aux->tempo);

        Aux = Aux->next;

       
    }
    
}

void escs(char* esc, Run_Results *info_head){

    Run_Results *Aux = info_head;

    while (Aux != NULL)
    {
       if(strcmp(esc,Aux->esc) == 0) printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", Aux->pos, Aux->esc, Aux->pos_esc, Aux->dorsal, Aux->nome, Aux->sexo, Aux->tempo);

        Aux = Aux->next;
    }
    
}

