#ifndef _retangulo_h
#define _retangulo_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef void *Retangulo;
/*Arquivo com informações pertinentes para Retangulo que é uma das formas do T1
*/

/* Esta função recebe os parametros lidos do .geo e processados no "arquivoGeo.c" e faz a criação do
retangulo, retornando-o para posteriormente ser inserido na lista de formas.
*/
Retangulo criarRetangulo(char *id, double altura, double largura, double x, double y, 
char *corBorda, char *corDentro, char *espessuraBorda);

/*Essa função recebe o arquivo SVG já aberto e o retangulo, faz o cast dentro para Struct do retangulo e 
escreve os dados do retangulo
*/
void escreverRetanguloSVG(Retangulo r, FILE *saida);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo retangulo e retorna
X e Y respectivamente.
*/
double getXRetangulo(Retangulo ret);
double getYRetangulo(Retangulo ret);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo retangulo e retorna
largura e altura respectivamente.
*/
double getLarguraRetangulo(Retangulo ret);
double getAlturaRetangulo(Retangulo ret);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo retangulo e retorna
xMaximo e yMaximo respectivamente.
*/
double getMaximoXRetangulo(Retangulo ret);
double getMaximoYRetangulo(Retangulo ret);

/*Faz com que libere a memória do retangulo, esta função é utilizada em conjunto com a função desalocarLista
executando isso em todos elementos da lista de formas e limpando toda a memória.
*/
void desalocarRetangulo(Retangulo ret);

/* Essa função recebe um ponteiro void e um id, dentro da função ele casta ponteiro void para o tipo Struct
retangulo, e assim compara se o id dentro da struct é o mesmo que o id fornecido no parametro.
*/
bool compararIDRetangulo(Retangulo ret, char *id);
#endif // !_retangulo_h
