#ifndef _hidrante_h
#define _hidrante_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef void *Hidrante;
/*Arquivo com informações pertinentes para hidrante que é um dos Elementos urbanos do T2
*/

/* Esta função recebe os parametros lidos do .geo e processados no "arquivoGeo.c" e faz a criação do
hidrante, retornando-o para posteriormente ser inserido na lista de hidrantes.
*/
Hidrante criarHidrante(char *id, double x, double y, char *corBorda, char *corDentro, char *espessuraBorda);

/*Está função é utilizada em conjunto com a função escreverListaSVG, recebendo como parametros o arquivo SVG
ja aberto e o hidrante, e juntamente com a função mencionada acima irá percorrer toda a lista executando
esta função em cada elemento.
*/
void escreverHidranteSVG(Hidrante h, FILE *saida);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo hidrante e retorna
X e Y respectivamente.
*/
double getXHidrante(Hidrante h);
double getYHidrante(Hidrante h);

/* Essa função recebe um ponteiro void e um id, dentro da função ele casta ponteiro void para o tipo Struct
hidrante, e assim compara se o id dentro da struct é o mesmo que o id fornecido no parametro.
*/
bool compararIDHidrante(Hidrante h, char *id); 

/*Faz com que libere a memória do hidrante, esta função é utilizada em conjunto com a função desalocarLista
executando isso em todos elementos da lista de hidrantes e limpando toda a memória.
*/
void desalocarHidrante(Hidrante h);

/*Estas duas funções tem com objetivo alterar o valor de um Elemento, recebendo como parametros o Elemento
que vai ser alterado, e o valor novo. As funções fazem alterações respectivamente em X e Y.
*/
void setXHidrante(Hidrante h, double x);
void setYHidrante(Hidrante h, double y);

/*Está função recebe um ponteiro void, dentro da função é realizado o cast para o struct hidrante, e então
é retornado o ID que está armazenado na struct
*/
char* getIDHidrante(Hidrante h);
#endif 