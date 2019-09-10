#ifndef _arquivoGeo_h
#define _arquivoGeo_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../listaEstatica/listaEstatica.h"
#include "../Circulo/circulo.h"
#include "../Retangulo/retangulo.h"
#include "../Quadra/quadra.h"
#include "../Hidrante/hidrante.h"
#include "../Semaforo/semaforo.h"
#include "../RadioBase/radioBase.h"
#include "../ArquivoQry/arquivoQry.h"
#include "../Predio/predio.h"
#include "../Ponto/ponto.h"
#include "../Muro/muro.h"

/* Arquivo com função de armazenar funções que serão utilizada para percorrer o arquivo .geo.
*/

/*Arquivo recebe parametros necessários para abertura dos arquivos.
pesquisageo = path para .geo 
pesquisaconsulta = path para .qry
saidageosvg = path para .svg com nome do .geo
saidaconsultatxt = path para saida txt caso pesquisaconsulta seja != NULL
saidaconsultasvg = path para saida svg caso pesquisaconsulta seja != NULL
boundingbox = path incompleto para boundingbox caso exista no .qry
*/
void arquivoGeo(char *pesquisageo, char *pesquisaconsulta,char *saidageosvg,
char *saidaconsultatxt, char *saidaconsultasvg, char *boundingbox);

#endif 


