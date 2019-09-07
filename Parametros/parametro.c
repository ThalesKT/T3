#include <stdio.h>
#include <stdlib.h>
#include "parametro.h"
#include <string.h>
#define TAM 128

//                       OK           OK              OK                   OK                 OK
void trataParametro(int argc, char *argv[], char **pesquisageo, char **pesquisaconsulta,char **saidageosvg,
char **saidaconsultatxt, char **saidaconsultasvg, char **boundingbox){
//       OK                        OK                        OK      
    char *diretorioentrada, *diretoriosaida, *arquivogeo, *arquivoconsulta;
    
    arquivogeo = NULL;
    *saidageosvg = NULL;
    *boundingbox = NULL;
    *pesquisageo = NULL;
    diretoriosaida = NULL;
    arquivoconsulta = NULL; 
    *saidaconsultatxt = NULL;
    *saidaconsultasvg = NULL;
    diretorioentrada = NULL;
    *pesquisaconsulta = NULL;


    for(int i=1; i<argc; i++){
        if( !strcmp(argv[i],"-e")){
            i++;
            diretorioentrada = calloc(TAM, sizeof(char));
            strcpy(diretorioentrada,argv[i]);

        } else if( !strcmp(argv[i],"-f")){
            i++;
            arquivogeo = calloc(TAM, sizeof(char));
            strcpy(arquivogeo, argv[i]);

        } else if( !strcmp(argv[i], "-q")){
            i++;
            arquivoconsulta = calloc(TAM, sizeof(char));
            strcpy(arquivoconsulta, argv[i]);

        } else if( !strcmp(argv[i], "-o")){
            i++;
            diretoriosaida = calloc(TAM, sizeof(char));
            strcpy(diretoriosaida, argv[i]);

        }
    }

    if(diretoriosaida == NULL){
        printf("Diretório de saida é obrigatório.\n");
        exit(1);

    } else if(arquivogeo == NULL){
        printf("Arquivo de entrada é necessário.\n");
        exit(1);
    }
    
    trataBarra(diretoriosaida);
    // NÃO EXISTE DIRETÓRIO DE ENTRADA
    if(diretorioentrada == NULL){
        *pesquisageo = calloc(TAM*2, sizeof(char));
        sprintf(*pesquisageo,"%s",arquivogeo);
        printf("Não existe diretório de entrada, arquivo geo deve possui diretório absoluto: %s \n",*pesquisageo);

    }

    if(diretorioentrada != NULL){
        trataBarra(diretorioentrada);
        *pesquisageo = calloc(TAM*2,sizeof(char));
        sprintf(*pesquisageo,"%s%s",diretorioentrada,arquivogeo);
        //printf("Saida geo, diretorio entrada+.geo: %s\n",*pesquisageo);
    }
    
    // Existe arquivo .qry  + o diretório entrada é NULO
    if(arquivoconsulta != NULL && diretorioentrada == NULL){
        *pesquisaconsulta = calloc(TAM*2,sizeof(char));
        sprintf(*pesquisaconsulta,"%s",arquivoconsulta);
        //printf("Não existe diretório de entrada, arquivo consulta deve possuir um diretório absoluto: %s \n",*pesquisaconsulta);
    }

    // DIRETÓRIO ENTRADA EXISTE
    if(arquivoconsulta != NULL && diretorioentrada != NULL){
        *pesquisaconsulta = calloc(TAM*2, sizeof(char));
        sprintf(*pesquisaconsulta,"%s%s",diretorioentrada,arquivoconsulta);
        //printf("Diretório entrada+arquivo consulta: %s \n",*pesquisaconsulta);
    }
    
    
    tiraPonto(arquivogeo);
    arquivogeo = separaArquivo(arquivogeo);
   
    
    *saidageosvg = calloc(TAM*2,sizeof(char));
    sprintf(*saidageosvg,"%s%s.svg",diretoriosaida,arquivogeo);
    //printf("Saida geosvg %s \n",*saidageosvg);

    if(arquivoconsulta != NULL){
        tiraPonto(arquivoconsulta);
        arquivoconsulta = separaArquivo(arquivoconsulta);
        *saidaconsultasvg = calloc(TAM*2,sizeof(char));
        *saidaconsultatxt = calloc(TAM*2,sizeof(char));
        *boundingbox = calloc(TAM*2,sizeof(char));
        sprintf(*saidaconsultasvg,"%s%s-%s.svg",diretoriosaida,arquivogeo,arquivoconsulta);
        sprintf(*saidaconsultatxt,"%s%s-%s.txt",diretoriosaida,arquivogeo,arquivoconsulta);
        sprintf(*boundingbox,"%s%s-%s-",diretoriosaida,arquivogeo,arquivoconsulta);
        
        //printf("Arquivo saida consulta svg: %s \n",*saidaconsultasvg);
        //printf("Arquivo saida consulta txt: %s \n",*saidaconsultatxt);
        //printf("Arquivo saida consulta boundingbox caso necessário: %s \n",*boundingbox);
    }

    free(diretorioentrada); 
    free(diretoriosaida); 
    free(arquivogeo); 
    free(arquivoconsulta);
}