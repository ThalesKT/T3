#ifndef _muro_h
#define _muro_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../Ponto/ponto.h"

typedef void *Muro;

Muro criarMuro(double x1, double y1, double x2, double y2);
void desalocarMuro(Muro m);
Ponto getPonto1Muro(Muro m);
Ponto getPonto2Muro(Muro m);
void escreverMuroSVG(Muro m, FILE *saida);
#endif