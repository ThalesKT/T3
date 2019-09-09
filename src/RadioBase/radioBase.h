#ifndef _radiobase_h
#define _radiobase_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void *radioBase;

radioBase criarRadioBase(char *id, double x, double y, char *corBorda, char *corDentro, char *espessuraBorda);
void escreverRadioBaseSVG(radioBase r, FILE *saida);
double getXRadioBase(radioBase r);
double getYRadioBase(radioBase r);
bool compararIDRadioBase(radioBase r, char *id);
void desalocarRadioBase(radioBase r);
char* getIDRadioBase(radioBase r);
void setXRadioBase(radioBase r, double x);
void setYRadioBase(radioBase r, double y);
#endif 