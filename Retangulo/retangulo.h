#ifndef _retangulo_h
#define _retangulo_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef void *Retangulo;

Retangulo criarRetangulo(char *id, double altura, double largura, double x, double y, 
char *corBorda, char *corDentro, char *espessuraBorda);
void escreverRetanguloSVG(Retangulo r, FILE *saida);
double getXRetangulo(Retangulo ret);
double getYRetangulo(Retangulo ret);
double getLarguraRetangulo(Retangulo ret);
double getAlturaRetangulo(Retangulo ret);
double getMaximoXRetangulo(Retangulo ret);
double getMaximoYRetangulo(Retangulo ret);
void desalocarRetangulo(Retangulo ret);
bool compararIDRetangulo(Retangulo ret, char *id);
#endif // !_retangulo_h
