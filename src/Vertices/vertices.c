#include "vertices.h"

typedef struct vertice {
    Ponto p;
    Segmento s;
    bool inicio, visivel;
    double angulo, distancia; //
} *StVertice;

Vertice criarVertice(double x, double y, double xCentro, double yCentro) {
    Vertice v = malloc(sizeof(struct vertice));
    StVertice vertice = (StVertice) v;
    Ponto p = criarPonto(x, y);
    vertice->p = p;
    vertice->angulo = calcularAngulo(p, xCentro, yCentro);
    vertice->distancia = distanciaL2(x, y, xCentro, yCentro);
    return vertice;
}

void desalocarVertice(Vertice v) {
    StVertice vertice = (StVertice) v;
    desalocarPonto(vertice->p);
    if(vertice->inicio) desalocarSegmento(vertice->s);
    free(vertice);
}

double getAnguloVertice(Vertice v) {
    StVertice vertice = (StVertice) v;
    return vertice->angulo;
}

void setInicioVertice(Vertice v, bool inicio) {
    StVertice vertice = (StVertice) v;
    vertice->inicio = inicio;
}

bool getInicioVertice(Vertice v) {
    StVertice vertice = (StVertice) v;
    return vertice->inicio;
}

double getXVertice(Vertice v) {
    StVertice vertice = (StVertice) v;
    return getXPonto(vertice->p);
}

double getYVertice(Vertice v) {
    StVertice vertice = (StVertice) v;
    return getYPonto(vertice->p);
}

Ponto getPVertice(Vertice v) {
    StVertice vertice = (StVertice) v;
    return vertice->p;
}

double setSVertice(Vertice v, Segmento s) {
    StVertice vertice = (StVertice) v;
    vertice->s = s;
}

Segmento getSVertice(Vertice v) {
    StVertice vertice = (StVertice) v;
    return vertice->s;
}

void setAnguloVertice(Vertice v, double angulo) {
    StVertice vertice = (StVertice) v;
    vertice->angulo = angulo;
}

double getDistanciaVertice(Vertice v) {
    StVertice vertice = (StVertice) v;
    return vertice->distancia;
}

int getSizeVertice() {
    return sizeof(struct vertice);
}

bool compararVertice(Vertice v1, Vertice v2) {
    return getXPonto(v1) == getXPonto(v2) && getYPonto(v1) == getYPonto(v2);
}