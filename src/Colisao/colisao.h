#ifndef _colisao_h
#define _colisao_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "../listaEstatica/listaEstatica.h"
#include "../Circulo/circulo.h"
#include "../Retangulo/retangulo.h"
#include "../Calculos/calculos.h"

/*Recebe dois elementos e os respectivos tipos para tratar dentro da função, e retorna true caso eles colidam
e false caso não colidam. Função utilizada no qry do T1
*/
bool elementosColidem(Elemento elemento1, Elemento elemento2,
char *tipo1, char *tipo2);

/*Função utilizada dentro do elementosColidem para caso o tipo1 seja "r" e tipo2 "c" ou vice versa
*/
bool colisaoCirculoRetangulo(Circulo c, Retangulo r);

/*Função utilizada dentro do elementosCOlidem para caso o tipo1 e tipo2 sejam "r"
*/
bool colisao2Retangulo(Retangulo r1, Retangulo r2);

/*Função utilizada dentro do elementosCOlidem para caso o tipo1 e tipo2 sejam "c"
*/
bool colisao2Circulo(Circulo c1, Circulo c2);

#endif 