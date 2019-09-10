#ifndef _circulo_h
#define _circulo_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void *Circulo;
/*Arquivo com informações pertinentes para circulo que é uma das formas do T1
*/

/* Esta função recebe os parametros lidos do .geo e processados no "arquivoGeo.c" e faz a criação do
circulo, retornando-o para posteriormente ser inserido na lista de formas.
*/
Circulo criarCirculo(char *id, double raio, double x, double y, char *corBorda, char *corDentro,
char *espessuraBorda);

/*Essa função recebe o arquivo SVG já aberto e o circulo, faz o cast dentro para Struct do circulo e 
escreve os dados do circulo
*/
void escreverCirculoSVG(Circulo c, FILE *saida);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo circulo e retorna
X e Y respectivamente.
*/
double getXCirculo(Circulo circ);
double getYCirculo(Circulo circ);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo circulo e retorna
raio.
*/
double getRaioCirculo(Circulo circ);

/*As 4seguintes funções recebem um ponteiro void, dentro da função faz um cast para struct circulo e então
fazem o retorno. xMaximo, yMaximo, xMinimo e yMinimo respectivamente
*/
double getMaximoXCirculo(Circulo circ);
double getMaximoYCirculo(Circulo circ);
double getMinimoXCirculo(Circulo circ);
double getMinimoYCirculo(Circulo circ);

/*Faz com que libere a memória do circulo, esta função é utilizada em conjunto com a função desalocarLista
executando isso em todos elementos da lista de circulo e limpando toda a memória.
*/
void desalocarCirculo(Circulo circ);

/* Essa função recebe um ponteiro void e um id, dentro da função ele casta ponteiro void para o tipo Struct
circulo, e assim compara se o id dentro da struct é o mesmo que o id fornecido no parametro.
*/
bool compararIDCirculo(Circulo c, char *id );

#endif // !_circulo_h#define _circulo_h

