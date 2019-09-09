#ifndef _ponto_h
#define _ponto_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void* Ponto;

Ponto criarPonto(double x, double y);
void desalocarPonto(Ponto p);
double getXPonto(Ponto p);
double getYPonto(Ponto p);
void setXPonto(Ponto p, double x);
void setYPonto(Ponto p, double y);
void setMinPonto(Ponto p, double x, double y);
void setMaxPonto(Ponto p, double x, double y);


#endif