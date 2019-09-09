#ifndef _calculos_h
#define _calculo_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "../listaEstatica/listaEstatica.h"
#include "../Circulo/circulo.h"
#include "../Retangulo/retangulo.h"

double distanciaL2(double x1, double y1, double x2, double y2);
double distanciaL1(double x1, double y1, double x2, double y2);
double clamp(double valor, double a, double b);
bool pontoInterno(double x, double y, Elemento elemento, char *tipo);
bool pontoInternoCirculo(double pontoX, double pontoY, Elemento c);
bool pontoInternoRetangulo(double pontoX, double pontoY, Elemento r);
void centroDeMassa(Elemento elemento, char *tipo, double *ponto);
double distanciaL2Centro(Elemento elemento1, Elemento elemento2, char *tipo1, char *tipo2);
bool retanguloInternoL1(double x, double y, Retangulo r, double dist);
bool retanguloInternoCirculo(Retangulo r, Circulo c);
bool retanguloInternoRetangulo(Retangulo r1, Retangulo r2);

#endif