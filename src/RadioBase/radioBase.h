#ifndef _radiobase_h
#define _radiobase_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void *radioBase;
/*Arquivo com informações pertinentes para radioBase que é um dos Elementos urbanos do T2
*/

/* Esta função recebe os parametros lidos do .geo e processados no "arquivoGeo.c" e faz a criação do
radioBase, retornando-o para posteriormente ser inserido na lista de semaforos.
*/
radioBase criarRadioBase(char *id, double x, double y, char *corBorda, char *corDentro, char *espessuraBorda);

/*Está função é utilizada em conjunto com a função escreverListaSVG, recebendo como parametros o arquivo SVG
ja aberto e o radioBase, e juntamente com a função mencionada acima irá percorrer toda a lista executando
esta função em cada elemento.
*/
void escreverRadioBaseSVG(radioBase r, FILE *saida);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo radioBase e retorna
X e Y respectivamente.
*/
double getXRadioBase(radioBase r);
double getYRadioBase(radioBase r);

/* Essa função recebe um ponteiro void e um id, dentro da função ele casta ponteiro void para o tipo Struct
radioBse, e assim compara se o id dentro da struct é o mesmo que o id fornecido no parametro.
*/
bool compararIDRadioBase(radioBase r, char *id);

/*Faz com que libere a memória do radioBase, esta função é utilizada em conjunto com a função desalocarLista
executando isso em todos elementos da lista de radioBase e limpando toda a memória.
*/
void desalocarRadioBase(radioBase r);

/*Está função recebe um ponteiro void, dentro da função é realizado o cast para o struct radioBase, e então
é retornado o ID que está armazenado na struct
*/
char* getIDRadioBase(radioBase r);

/*Estas duas funções são utilizadas para alterar o valor atual de x e y respectivamente. Ambas recebem um
ponteiro void e o novo valor a ser atualizado.
*/
void setXRadioBase(radioBase r, double x);
void setYRadioBase(radioBase r, double y);
#endif 