#ifndef _arquivoQry_h
#define _arquivoQry_h

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
#include "svgQry.h"

void arquivoQry(char *pesquisageo, char *pesquisaconsulta,
char *saidaconsultatxt, char *saidaconsultasvg, char *boundingbox,
Lista listaFormas, Lista listaQuadras, Lista listaHidrantes, Lista listaSemaforo,
Lista listaRadioBase, FILE *consultaSVG);
void comandoBB(FILE *boundingbox, char *cor, Lista listaFormas);
void elipseEnvoltaRetangulo(Elemento rect, FILE *boudingbox, char *cor);
void retanguloEnvoltaCirculo(Elemento circ, FILE *boundingbox, char *cor);
void removerQuadrasDQ(Lista listaQuadras, double x, double y, double distancia, char *tipoMetrica,
FILE *saidaTXT);
void colorirQuadrasDentroCirculo(Lista listaQuadras, Circulo c, char *cor, FILE *saidaTXT);
void desalocarElementosDentroRetangulo(Lista listaQuadras, Lista listaHidrantes, Lista listaRadioBase,
Lista listaSemaforo, Retangulo r, double dx, double dy, FILE *saidaTXT);



#endif