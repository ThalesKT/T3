#ifndef _vertices_h
#define _vertices_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../Ponto/ponto.h"

typedef void *Vertice;
typedef void *Segmento;

#include "../Segmentos/segmentos.h"
#include "../Calculos/calculos.h"


Vertice criarVertice(double x, double y, double xCentro, double yCentro);
void desalocarVertice(Vertice v);
double getAnguloVertice(Vertice v);
void setInicioVertice(Vertice v, bool inicio);
bool getInicioVertice(Vertice v);
double getXVertice(Vertice v);
double getYVertice(Vertice v);
Ponto getPVertice(Vertice v);
double setSVertice(Vertice v, Segmento s);
Segmento getSVertice(Vertice v);
void setAnguloVertice(Vertice v, double angulo);
double getDistanciaVertice(Vertice v);
int getSizeVertice();
bool compararVertice(Vertice v1, Vertice v2);

#endif //