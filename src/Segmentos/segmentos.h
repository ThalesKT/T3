#ifndef _segmentos_h
#define _segmentos_h

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../Vertices/vertices.h"

typedef void* Segmento;

Segmento criarSegmento(Vertice v1, Vertice v2);
void desalocarSegmento(Segmento s);
void setInicioVerticesSegmento(Segmento s);
Vertice getV1Segmento(Segmento s);
Vertice getV2Segmento(Segmento s);
void setDistanciaSegmento(Segmento s, double distancia);
double getDistanciaSegmento(Segmento s);

#endif // !