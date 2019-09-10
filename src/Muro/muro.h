#ifndef _muro_h
#define _muro_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../Ponto/ponto.h"

typedef void *Muro;
/*Arquivo com informações pertinentes para muro que é um dos Elementos urbanos do T3
*/

/* Esta função recebe os parametros lidos do .geo e processados no "arquivoGeo.c" e faz a criação do
muro, retornando-o para posteriormente ser inserido na lista de muros.
*/
Muro criarMuro(double x1, double y1, double x2, double y2);

/*Faz com que libere a memória do muro, esta função é utilizada em conjunto com a função desalocarLista
executando isso em todos elementos da lista de muros e limpando toda a memória.
*/
void desalocarMuro(Muro m);

/*Estas duas funções recebem um ponteiro void, faz o cast e retorna um ponteiro void do tipo Ponto, que é uma struct
aonde armazena dois pontos(x,y)
*/
Ponto getPonto1Muro(Muro m);
Ponto getPonto2Muro(Muro m);

/*Está função é utilizada em conjunto com a função escreverListaSVG, recebendo como parametros o arquivo SVG
ja aberto e o muro, e juntamente com a função mencionada acima irá percorrer toda a lista executando
esta função em cada elemento.
*/
void escreverMuroSVG(Muro m, FILE *saida);
#endif