#ifndef _listaEstatica_h_
#define _listaEstatica_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void *Lista;
typedef void *Elemento;
/* Estrutura utilizada no T2 E T3 para armazenar dados
*/

/*Recebe um valor processador no arquivoGeo.c caso seja informado no arquivo .geo e então 
aloca espaço necessário para quantidade passada no parametro.
*/
Lista inicializarLista(int tamanhoMax);

/*Recebe uma lista e uma função, passando a função por todos elementos da lista desalocando
*/
void desalocarLista(Lista l, void(*destruirElemento)(Elemento elemento));


/*Funções utilizacadas para realização de for fora do escopo da lista.
*/
/*Recebe uma lista e retorna um inteiro referente a proxima posição livre
*/
int getPosicaoLivreLista(Lista l);

/*Recebe uma lista e retorna o primeiro elemento
*/
int getPrimeiroElementoLista(Lista l);

/*Recebe um inteiro referente a posição, uma lista e retorna o próximo elemento. Assim como a de baixo
retorna o elemento anterior com os mesmos parametros
*/
int getProximoElemento(Lista l, int posicao);
int getAnteriorElemento(Lista l, int posicao);

/*Recebe uma lista, um elemento, um tipo para poder identificar o q é e o id.
Faz a inserção do elemento no final da lista caso haja espaço
*/
bool inserirFinalLista(Lista l, Elemento elemento, char *tipo, char *id);

/*Recebe uma lista, um id, uma função para comprar id e uma função para desalocar o elemento,
caso retorno de comparar seja true a função desalocar é executada
*/
bool excluirElementoLista(Lista l, char *identificador, 
    bool(*comparar)(Elemento elementoLista, char *identificador), 
    void(*desalocarElemento)(Elemento elemento));
int getTamanhoLista(Lista l);

/*Recebe uma lista, um ID e uma função, caso o retorno da função comprar seja true
o elemento foi encontrado e vai ser retornado.
*/
Elemento getElementoLista(Lista l, 
    char *identificador, 
    bool(*comparar)(Elemento elementoLista, char *identificador));

/*Recebe uma lista, e uma função, executando a função por todos elementos da lista e inserindo no
svg
*/
void escreverListaSVG(Lista l, void(*escreverSVG)(Elemento elemento,FILE *saida), FILE *saida);

/*Estas duas funções tem como objetivo conseguir um elemento. A primeira é utilizada na listaFormas
pois recebe uma lista contendo Rentagulo e Circulos, e o tipo diz o q quer juntamente com id.
*/
Elemento getElementoeTipo(Lista l, char *tipo1, char *id);
Elemento getElementoListaPosicao(Lista l, int i);

/*Esta função recebe uma lista e uma posição e retorna qual tipo de elemento naquela posição
*/
void getTipoElemento(Lista l, int i, char *tipo);

/*recebe uma lista, um inteiro indicando a posição e uma função para apagar determinado objeto
*/
bool excluirElementoPosicaoX(Lista l, int i, void(*apagarObjeto)(Elemento elemento));

bool excluirElementoMemoriaLista(Lista l, Elemento elemento);
#endif // !_listaEstatica_h_

