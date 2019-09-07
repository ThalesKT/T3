#ifndef _svgQry_h
#define _svgQry_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../Circulo/circulo.h"
#include "../Hidrante/hidrante.h"
#include "../listaEstatica/listaEstatica.h"
#include "../Parametros/parametro.h"
#include "../Quadra/quadra.h"
#include "../RadioBase/radioBase.h"
#include "../Retangulo/retangulo.h"
#include "../Semaforo/semaforo.h"
#include "../Calculos/calculos.h"
#include "../Colisao/colisao.h"

void escreverRetanguloQRY(FILE *svgQRY, Elemento elemento1, Elemento elemento2, bool colidem,
char *tipo1, char *tipo2);

void escreverPontoInternoQRY(FILE *consultaSVG, Elemento elemento1,
 double x, double y, bool interno, char *tipo1);

void escreverRetaQRY(FILE *consultaSVG, Elemento elemento1, Elemento elemento2,
char *tipo1, char *tipo2);

void escreverDistanciaPMassaQRY(FILE *consultaSVG, Elemento elemento1, Elemento elemento2, double distancia,
char *tipo1, char *tipo2);

void escreverElipseBB(double x, double y, double raiox, double raioy, FILE *boundingbox, char*cor);

void escreverRetanguloBB(double largura, double altura, double x, double y, FILE *boundingbox, char *cor);
#endif // !_svgQry_h
