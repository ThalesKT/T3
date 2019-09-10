#ifndef _arquivoQry_h
#define _arquivoQry_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

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
#include "../Muro/muro.h"
#include "../Predio/predio.h"
#include "svgQry.h"
#include "../Vertices/vertices.h"
#include "../Segmentos/segmentos.h"

void arquivoQry(char *pesquisageo, char *pesquisaconsulta,
char *saidaconsultatxt, char *saidaconsultasvg, char *boundingbox,
Lista listaFormas, Lista listaQuadras, Lista listaHidrantes, Lista listaSemaforo,
Lista listaRadioBase, Lista listaPredios, Lista listaMuros, FILE *consultaSVG);
void comandoBB(FILE *boundingbox, char *cor, Lista listaFormas);
void elipseEnvoltaRetangulo(Elemento rect, FILE *boudingbox, char *cor);
void retanguloEnvoltaCirculo(Elemento circ, FILE *boundingbox, char *cor);
void removerQuadrasDQ(Lista listaQuadras, double x, double y, double distancia, char *tipoMetrica,
FILE *saidaTXT);
void colorirQuadrasDentroCirculo(Lista listaQuadras, Circulo c, char *cor, FILE *saidaTXT);
void desalocarElementosDentroRetangulo(Lista listaQuadras, Lista listaHidrantes, Lista listaRadioBase,
Lista listaSemaforo, Retangulo r, double dx, double dy, FILE *saidaTXT);
void heapsortMenor(Elemento a[], int n, int valor, double (*getComparator)(Elemento objeto));
void heapsortMaior(Elemento a[], int n, int valor, double (*getComparator)(Elemento objeto));
void processarFocoIncendio(Lista listaSemaforos, Lista listaHidrantes, double x,
 double y, int ns, double r, FILE *txt, FILE *svg);
 void processarObjetosProximos(Lista listaElemento, Lista listaQuadras, char sinal, int k,
 char cep[], char face, double num, FILE* txt, FILE *svg, char tipo[]);
void processarBombaRL(Lista listaPredios, Lista listaMuros, double x, double y, FILE *svg);


#endif