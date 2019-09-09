#ifndef _semaforo_h
#define _semaforo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef void *Semaforo;

Semaforo criarSemaforo(char *id, double x, double y, char *corBorda, char *corDentro, char *espessuraBorda);
void escreverSemaforoSVG(Semaforo s, FILE *saida);
double getXSemaforo(Semaforo s);
double getYSemaforo(Semaforo s);
bool compararIDSemaforo(Semaforo s, char *id);
void desalocarSemaforo(Semaforo s);
void setXSemaforo(Semaforo s, double x);
void setYSemaforo(Semaforo s, double y);
char* getIDSemaforo(Semaforo s);
#endif 