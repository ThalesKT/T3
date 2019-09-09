#ifndef _predio_h
#define _predio_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef void *Predio;

Predio criarPredio(char *cep, char face, double numero, double f, double profundidade, double mrg);
void desalocarPredio(Predio prd);
char* getCepPredio(Predio prd);
double getXPredio(Predio prd);
double getYPredio(Predio prd);
double getMaximoXPredio(Predio prd);
double getMaximoYPredio(Predio prd);
double getNumeroPredio(Predio prd);
void escreverPredioSVG(Predio prd, double xQuadra,
 double yQuadra, double larguraQuadra,
  double alturaQuadra, FILE *saida);


#endif 
