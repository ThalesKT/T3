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

void arquivoGeo(char *pesquisageo, char *pesquisaconsulta,char *saidageosvg,
char *saidaconsultatxt, char *saidaconsultasvg, char *boundingbox);

#endif 


