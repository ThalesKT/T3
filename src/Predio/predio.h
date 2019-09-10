#ifndef _predio_h
#define _predio_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef void *Predio;
/*Arquivo com informações pertinentes para predio que é um dos Elementos urbanos do T3
*/

/* Esta função recebe os parametros lidos do .geo e processados no "arquivoGeo.c" e faz a criação do
predio, retornando-o para posteriormente ser inserido na lista de predios.
*/
Predio criarPredio(char *cep, char face, double numero, double f, double profundidade, double mrg);

/*Faz com que libere a memória do predio, esta função é utilizada em conjunto com a função desalocarLista
executando isso em todos elementos da lista de predios e limpando toda a memória.
*/
void desalocarPredio(Predio prd);

/*Está função recebe um ponteiro void, faz o cast e retorna o cep armazenado dentro da struct para que
seja possivel localizar em qual quadra o predio está situado.
*/
char* getCepPredio(Predio prd);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo predio e retorna
X e Y respectivamente.
*/
double getXPredio(Predio prd);
double getYPredio(Predio prd);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo predio e retorna
xMaximo e yMaximo respectivamente.
*/
double getMaximoXPredio(Predio prd);
double getMaximoYPredio(Predio prd);

/* Está função recebe um ponteiro void, faz o cast para struct predio e retorna um numero predio
armazenado dentro da struct.
*/
double getNumeroPredio(Predio prd);


/*Está função é utilizada em conjunto com a função escreverListaSVG, recebendo como parametros o arquivo SVG
ja aberto e o predio, e juntamente com a função mencionada acima irá percorrer toda a lista executando
esta função em cada elemento.
*/
void escreverPredioSVG(Predio prd, double xQuadra,
 double yQuadra, double larguraQuadra,
  double alturaQuadra, FILE *saida);


#endif 
