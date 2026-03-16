#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados de cada participante
typedef struct {
    int pos_geral;
    char escalao[10];
    int pos_escalao;
    int dorsal;
    char nome[100];
    char sexo;
    char tempo[20];
} Participante;


Participante* carregar_ficheiro(const char *nome_ficheiro, int *num_participantes) {
    FILE *ficheiro = fopen(nome_ficheiro, "r");
    if (ficheiro == NULL) {
        perror("Erro ao abrir o ficheiro");
        return NULL;
    }
    int capacidade = 10;
    int total = 0;
    Participante *lista = (Participante*) malloc(capacidade * sizeof(Participante));
    if (lista == NULL) {
        fclose(ficheiro);
        return NULL;
    }

    char linha[256];
    
    
    if (fgets(linha, sizeof(linha), ficheiro) == NULL) {
        fclose(ficheiro);
        free(lista);
        return NULL;
    }

    
    while (fgets(linha, sizeof(linha), ficheiro) != NULL) {
        
        if (total >= capacidade) {
            capacidade *= 2;
            lista = (Participante*) realloc(lista, capacidade * sizeof(Participante));
        }

        
        char *token = strtok(linha, "\t\n");
        if (token == NULL) continue; 
        lista[total].pos_geral = atoi(token);

        token = strtok(NULL, "\t\n");
        if (token) strcpy(lista[total].escalao, token);

        token = strtok(NULL, "\t\n");
        if (token) lista[total].pos_escalao = atoi(token);

        token = strtok(NULL, "\t\n");
        if (token) lista[total].dorsal = atoi(token);

        token = strtok(NULL, "\t\n");
        if (token) strcpy(lista[total].nome, token);

        token = strtok(NULL, "\t\n");
        if (token) lista[total].sexo = token[0];

        token = strtok(NULL, "\t\n");
        if (token) strcpy(lista[total].tempo, token);

        total++;
    }

    fclose(ficheiro);
    *num_participantes = total;
    return lista;
}


int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        printf("Uso: %s <ficheiro_resultados.txt> <nome_participante>\n", argv[0]);
        return 1;
    }

    int total_participantes = 0;
    Participante *participantes = carregar_ficheiro(argv[1], &total_participantes);

    if (participantes == NULL) {
        return 1;
    }

    char *nome_procurado = argv[2];
    int encontrado = 0;

    for (int i = 0; i < total_participantes; i++) {
        
        if (strstr(participantes[i].nome, nome_procurado) != NULL) {
            printf("\nParticipante Encontrado:\n");
            printf("Nome: %s\n", participantes[i].nome);
            printf("Posição Geral: %d\n", participantes[i].pos_geral);
            printf("Posição no Escalão (%s): %d\n\n", participantes[i].escalao, participantes[i].pos_escalao);
            encontrado = 1;
            break; 
        }
    }

    if (!encontrado) {
        printf("\nParticipante '%s' não foi encontrado na lista.\n\n", nome_procurado);
    }

    
    free(participantes);

    return 0;
}