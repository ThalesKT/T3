#include "circulo.h"


typedef struct circulo {
    char id[75], corDentro[75], corBorda[75], espessuraBorda[75];
    double raio, x, y;

}*StCirculo;

Circulo criarCirculo(char *id, double raio, double x, double y, char *corBorda, char *corDentro,
char *espessuraBorda) {
    Circulo c = malloc(sizeof(struct circulo));
    StCirculo circulo = (StCirculo) c;
    strcpy(circulo->id, id);
    circulo->raio = raio;
    circulo->x = x;
    circulo->y = y;
    strcpy(circulo->corBorda, corBorda);
    strcpy(circulo->corDentro, corDentro);
    strcpy(circulo->espessuraBorda, espessuraBorda);
    
    return circulo;
}

void escreverCirculoSVG(Circulo c, FILE *saida) {
    StCirculo circ = (StCirculo) c;

    fprintf(saida, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"%s\" fill=\"%s\" />\n",
    circ->x,
    circ->y,
    circ->raio,
    circ->corBorda,
    circ->espessuraBorda,
    circ->corDentro);

}


double getXCirculo(Circulo circ) {
    StCirculo c = (StCirculo) circ;
    return c->x;
} 

double getYCirculo(Circulo circ) {
    StCirculo c = (StCirculo) circ;
    return c->y;
} 

double getRaioCirculo(Circulo circ) {
    StCirculo c = (StCirculo) circ;
    return c->raio;
} 

double getMaximoXCirculo(Circulo circ) {
    StCirculo c = (StCirculo) circ;
    return c->x + c->raio;
} 

double getMaximoYCirculo(Circulo circ) {
    StCirculo c = (StCirculo) circ;
    return c->y + c->raio;
} 

double getMinimoXCirculo(Circulo circ) {
    StCirculo c = (StCirculo) circ;
    return c->x - c->raio;
} 

double getMinimoYCirculo(Circulo circ) {
    StCirculo c = (StCirculo) circ;
    return c->y -  c->raio;
} 

void desalocarCirculo(Circulo circ) {
    StCirculo c = (StCirculo) circ;
    free(c);
}

bool compararIDCirculo(Circulo c, char *id ) {
    StCirculo circ = (StCirculo) c;
    return strcmp(circ->id, id ) == 0;
}