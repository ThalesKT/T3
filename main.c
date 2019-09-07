#include <stdio.h>
#include <stdlib.h>
#include "./Parametros/parametro.h"
#include "./arquivoGeo/arquivoGeo.h"

int main(int argc, char *argv[]) {
    char *pesquisageo, *pesquisaconsulta, *saidageosvg, *saidaconsultatxt, *boundingbox, *saidaconsultasvg;
    FILE *teste;

    trataParametro(argc, argv, &pesquisageo, &pesquisaconsulta, &saidageosvg,
    &saidaconsultatxt, &saidaconsultasvg, &boundingbox);

    teste = fopen(pesquisageo,"r");
    if(teste == NULL){
        printf("Hove um erro na abertura do .geo. \n");
        exit(1);
    } else{
       arquivoGeo(pesquisageo, pesquisaconsulta, saidageosvg, saidaconsultatxt, saidaconsultasvg, boundingbox);
    }

    printf("O programa chegou ao fim sem nenhum erro!\n");

    free(pesquisageo);
    free(pesquisaconsulta);
    free(saidageosvg);
    free(saidaconsultatxt);
    free(boundingbox);
    free(saidaconsultasvg);
}