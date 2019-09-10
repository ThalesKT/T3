#ifndef _quadra_h
#define _quadra_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void *Quadra;
/*Arquivo com informações pertinentes para Quadra que é um dos Elementos urbanos do T2
*/

/* Esta função recebe os parametros lidos do .geo e processados no "arquivoGeo.c" e faz a criação da
quadra, retornando-o para posteriormente ser inserido na lista de quadras.
*/
Quadra criarQuadra(char *cep, double x, double y, double altura, double largura,
char *corBorda, char *corDentro, char *espessuraBorda);

/*Está função é utilizada em conjunto com a função escreverListaSVG, recebendo como parametros o arquivo SVG
ja aberto e a quadra, e juntamente com a função mencionada acima irá percorrer toda a lista executando
esta função em cada elemento.
*/
void escreverQuadraSVG(Quadra q, FILE *saida);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo quadra e retorna
X e Y respectivamente.
*/
double getXQuadra(Quadra q);
double getYQuadra(Quadra q);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo quadra e retorna
altura e largura respectivamente.
*/
double getAlturaQuadra(Quadra q);
double getLarguraQuadra(Quadra q);

/*Faz com que libere a memória da quadra, esta função é utilizada em conjunto com a função desalocarLista
executando isso em todos elementos da lista de quadras e limpando toda a memória.
*/
void desalocarQuadra(Quadra q);

/* Está função recebe um ponteiro void, dentro da função há um cast para o tipo quadra e então é retornado
o cep armazenado dentro da struct
*/
char* getCepQuadra(Quadra q);

/* Essa função recebe um ponteiro void e um id, dentro da função ele casta ponteiro void para o tipo Struct
quadra, e assim compara se o id(cep) dentro da struct é o mesmo que o id(cep) fornecido no parametro.
*/
bool compararIDQuadra(Quadra q, char *cep);

/*Está função tem como objetivo alterar a cor da borda da quadra através de um comando do qry T2.
Recebem um ponteiro void e a cor nova, dentro da função é realizado o cast e então alterada a cor.
*/
void setCorBordaQuadra(Quadra q, char *cor);

/*Estas duas funções tem com objetivo alterar o valor de um Elemento, recebendo como parametros o Elemento
que vai ser alterado, e o valor novo. As funções fazem alterações respectivamente em X e Y.
*/
void setXQuadra(Quadra q, double x);
void setYQuadra(Quadra q, double y);
#endif // !_quadra_h
