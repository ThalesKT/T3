#include "ponto.h"

typedef struct ponto {
    double x, y;
} *StPonto;

Ponto criarPonto(double x, double y) {
    Ponto p = malloc(sizeof(struct ponto));
    StPonto ponto = (StPonto) p;
    ponto->x = x;
    ponto->y = y;
    return ponto;
}

void desalocarPonto(Ponto p) {
    StPonto ponto = (StPonto) p;
    free(ponto);
}

double getXPonto(Ponto p) {
    StPonto ponto = (StPonto) p;
    return ponto->x;
}

double getYPonto(Ponto p) {
    StPonto ponto = (StPonto) p;
    return ponto->y;
}

void setXPonto(Ponto p, double x) {
    StPonto ponto = (StPonto) p;
    ponto->x = x;
}

void setYPonto(Ponto p, double y) {
    StPonto ponto = (StPonto) p;
    ponto->y = y;
}

void setMinPonto(Ponto p, double x, double y) {
    StPonto ponto = (StPonto) p;
    if(x < ponto->x) ponto->x = x;
    if(y< ponto->y) ponto->y = y;
}

void setMaxPonto(Ponto p, double x, double y) {
    StPonto ponto = (StPonto) p;
    if(x > ponto->x) ponto->x = x;
    if(y > ponto->y) ponto->y = y;
}