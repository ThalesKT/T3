#ifndef _hidrante_h
#define _hidrante_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef void *Hidrante;

Hidrante criarHidrante(char *id, double x, double y, char *corBorda, char *corDentro, char *espessuraBorda);
void escreverHidranteSVG(Hidrante h, FILE *saida);
double getXHidrante(Hidrante h);
double getYHidrante(Hidrante h);
bool compararIDHidrante(Hidrante h, char *id); 
void desalocarHidrante(Hidrante h);
void setXHidrante(Hidrante h, double x);
void setYHidrante(Hidrante h, double y);
char* getIDHidrante(Hidrante h);
#endif 