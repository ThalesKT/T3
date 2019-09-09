#ifndef _quadra_h
#define _quadra_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void *Quadra;

Quadra criarQuadra(char *cep, double x, double y, double altura, double largura,
char *corBorda, char *corDentro, char *espessuraBorda);
void escreverQuadraSVG(Quadra q, FILE *saida);
double getXQuadra(Quadra q);
double getYQuadra(Quadra q);
double getAlturaQuadra(Quadra q);
double getLarguraQuadra(Quadra q);
void desalocarQuadra(Quadra q);
char* getCepQuadra(Quadra q);
bool compararIDQuadra(Quadra q, char *cep);
void setCorBordaQuadra(Quadra q, char *cor);
void setXQuadra(Quadra q, double x);
void setYQuadra(Quadra q, double y);
#endif // !_quadra_h
