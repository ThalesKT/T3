#ifndef _listaEstatica_h_
#define _listaEstatica_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void *Lista;
typedef void *Elemento;

Lista inicializarLista(int tamanhoMax);
void destruirLista(Lista l, void(*destruirElemento)(Elemento elemento));
int getPosicaoLivreLista(Lista l);
int getPrimeiroElementoLista(Lista l);
int getProximoElemento(Lista l, int posicao);
int getAnteriorElemento(Lista l, int posicao);
bool inserirFinalLista(Lista l, Elemento elemento, char *tipo, char *id);
bool excluirElementoLista(Lista l, char *identificador, 
    bool(*comparar)(Elemento elementoLista, char *identificador), 
    void(*destruirElemento)(Elemento elemento));
int getTamanhoLista(Lista l);
Elemento getElementoLista(Lista l, 
    char *identificador, 
    bool(*comparar)(Elemento elementoLista, char *identificador));

void escreverListaSVG(Lista l, void(*escreverSVG)(Elemento elemento,FILE *saida), FILE *saida);
Elemento getElementoeTipo(Lista l, char *tipo1, char *id);
Elemento getElementoListaPosicao(Lista l, int i);
void getTipoElemento(Lista l, int i, char *tipo);
bool excluirElementoPosicaoX(Lista l, int i, void(*apagarObjeto)(Elemento elemento));
#endif // !_listaEstatica_h_

