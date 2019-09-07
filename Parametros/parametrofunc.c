#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM 128


void trataBarra(char *diretorio){

    if(diretorio[strlen(diretorio)-1] == '/'){
        //printf("O diretório de entrada já possui barra.\n");

    } else{
        //printf("Inserindo a barra no diretório.\n");
        sprintf(diretorio,"%s/",diretorio);
        //printf("Diretorio com barra: %s \n", diretorio);
    }
}

void uneDiretorioArquivo(char *diretorio, char *arquivo ,char *saida){
    saida = calloc(TAM*2, sizeof(char));
    sprintf(saida,"%s%s",diretorio,arquivo);
}

void tiraPonto(char *ponto){
    int end = strlen(ponto) - 1;
    int stop;
    for (int i = end; ponto[i] != '.'; i--){
        stop = i;
    }

    ponto[stop-1] = '\0';
}


void trataPrimeiraBarra(char *palavra){
    int i=0;
    
    if(palavra[i] == '/'){
        for(i=0; i<strlen(palavra); i++){
            palavra[i] = palavra[i+1];
        }    
    }
}


char* separaArquivo(char *ponto){
    int str_size = strlen(ponto);
    int stop = -1;

    for(size_t i = 0; i < str_size; i++)
        if(ponto[i] == '/')
            stop = i;
            
    char* new = (char*)calloc(strlen(ponto) - stop, sizeof(char));
    for(size_t i = stop + 1; i < str_size; i++)
        new[i - stop - 1] = ponto[i];
    
    free(ponto);
    return new;
}