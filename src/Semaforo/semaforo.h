#ifndef _semaforo_h
#define _semaforo_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef void *Semaforo;
/*Arquivo com informações pertinentes para semaforo que é um dos Elementos urbanos do T2
*/

/* Esta função recebe os parametros lidos do .geo e processados no "arquivoGeo.c" e faz a criação do
semaforo, retornando-o para posteriormente ser inserido na lista de semaforos.
*/
Semaforo criarSemaforo(char *id, double x, double y, char *corBorda, char *corDentro, char *espessuraBorda);

/*Está função é utilizada em conjunto com a função escreverListaSVG, recebendo como parametros o arquivo SVG
ja aberto e o semaforo, e juntamente com a função mencionada acima irá percorrer toda a lista executando
esta função em cada elemento.
*/
void escreverSemaforoSVG(Semaforo s, FILE *saida);

/* Está função e a debaixo recebem um Elemento *void, casta dentro dela para o tipo semaforo e retorna
X e Y respectivamente.
*/
double getXSemaforo(Semaforo s);
double getYSemaforo(Semaforo s);

/* Essa função recebe um ponteiro void e um id, dentro da função ele casta ponteiro void para o tipo Struct
semaforo, e assim compara se o id dentro da struct é o mesmo que o id fornecido no parametro.
*/
bool compararIDSemaforo(Semaforo s, char *id);

/*Faz com que libere a memória do semaforo, esta função é utilizada em conjunto com a função desalocarLista
executando isso em todos elementos da lista de semaforos e limpando toda a memória.
*/
void desalocarSemaforo(Semaforo s);

/*Estas duas funções tem com objetivo alterar o valor de um Elemento, recebendo como parametros o Elemento
que vai ser alterado, e o valor novo. As funções fazem alterações respectivamente em X e Y.
*/
void setXSemaforo(Semaforo s, double x);
void setYSemaforo(Semaforo s, double y);

/*Está função recebe um ponteiro void, dentro da função é realizado o cast para o struct semaforo, e então
é retornado o ID que está armazenado na struct
*/
char* getIDSemaforo(Semaforo s);
#endif 