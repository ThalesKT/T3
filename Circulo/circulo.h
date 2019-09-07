#ifndef _circulo_h
#define _circulo_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void *Circulo;

Circulo criarCirculo(char *id, double raio, double x, double y, char *corBorda, char *corDentro,
char *espessuraBorda);
void escreverCirculoSVG(Circulo c, FILE *saida);
double getXCirculo(Circulo circ);
double getYCirculo(Circulo circ);
double getRaioCirculo(Circulo circ);
double getMaximoXCirculo(Circulo circ);
double getMaximoYCirculo(Circulo circ);
double getMinimoXCirculo(Circulo circ);
double getMinimoYCirculo(Circulo circ);
void desalocarCirculo(Circulo circ);
bool compararIDCirculo(Circulo c, char *id );

#endif // !_circulo_h#define _circulo_h

