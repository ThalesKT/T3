#include "segmentos.h"

typedef struct segmento {
    Vertice v1, v2;
    double distancia;
}*StSegmento;

Segmento criarSegmento(Vertice v1, Vertice v2) {
    Segmento s = malloc(sizeof(struct segmento));
    StSegmento segmento = (StSegmento) s;
    segmento->v1 = v1;
    segmento->v2 = v2;
    return segmento;
}

void desalocarSegmento(Segmento s) {
    StSegmento segmento = (StSegmento) s;
    free(segmento);
}

void setInicioVerticesSegmento(Segmento s) {
    StSegmento segmento = (StSegmento) s;
    double dAngulo = getAnguloVertice(segmento->v2) - getAnguloVertice(segmento->v1);
    if(dAngulo <= -M_PI) dAngulo+=(2*M_PI);
    if(dAngulo > M_PI) dAngulo-=(2*M_PI);

    bool inicio = dAngulo > 0 ? true : false;
    setInicioVertice(segmento->v1, inicio);
    setInicioVertice(segmento->v2, !inicio);
}

Vertice getV1Segmento(Segmento s) {
    StSegmento segmento = (StSegmento) s;
    return segmento->v1;
}

Vertice getV2Segmento(Segmento s) {
    StSegmento segmento = (StSegmento) s;
    return segmento->v2;
}

void setDistanciaSegmento(Segmento s, double distancia) {
    StSegmento segmento = (StSegmento) s;
    segmento->distancia = distancia;
}

double getDistanciaSegmento(Segmento s) {
    StSegmento segmento = (StSegmento) s;
    return segmento->distancia;
}