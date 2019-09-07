#ifndef _colisao_h
#define _colisao_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "../listaEstatica/listaEstatica.h"
#include "../Circulo/circulo.h"
#include "../Retangulo/retangulo.h"
#include "../Calculos/calculos.h"

bool elementosColidem(Elemento elemento1, Elemento elemento2,
char *tipo1, char *tipo2);
bool colisaoCirculoRetangulo(Circulo c, Retangulo r);
bool colisao2Retangulo(Retangulo r1, Retangulo r2);
bool colisao2Circulo(Circulo c1, Circulo c2);

#endif 