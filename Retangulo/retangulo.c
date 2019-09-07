#include "retangulo.h"

typedef struct retangulo{
    char id[15], corDentro[35], corBorda[35], espessuraBorda[35];
    double altura, largura, x, y;

}*StRetangulo;


Retangulo criarRetangulo(char *id, double altura, double largura, double x, double y, 
char *corBorda, char *corDentro, char *espessuraBorda) {
    Retangulo r = malloc(sizeof(struct retangulo));
    StRetangulo ret = (StRetangulo) r;
    strcpy(ret->id,id);
    ret->altura = altura;
    ret->largura = largura;
    ret->x = x;
    ret->y = y;
    strcpy(ret->corBorda, corBorda);
    strcpy(ret->corDentro, corDentro);
    strcpy(ret->espessuraBorda, espessuraBorda);
    return ret;
    
}

void escreverRetanguloSVG(Retangulo r, FILE *saida) {
    StRetangulo ret = (StRetangulo) r;

    fprintf(saida,"<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" /> \n",
    ret->largura,
    ret->altura,
    ret->x,
    ret->y,
    ret->corBorda,
    ret->corDentro,
    ret->espessuraBorda);

}

double getXRetangulo(Retangulo ret) {
    StRetangulo r = (StRetangulo) ret;
    return r->x;
}

double getYRetangulo(Retangulo ret) {
    StRetangulo r = (StRetangulo) ret;
    return r->y;
}

double getLarguraRetangulo(Retangulo ret) {
    StRetangulo r = (StRetangulo) ret;
    return r->largura;
}

double getAlturaRetangulo(Retangulo ret) {
    StRetangulo r = (StRetangulo) ret;
    return r->altura;
}

double getMaximoXRetangulo(Retangulo ret) {
    StRetangulo r = (StRetangulo) ret;
    return r->x + r->largura;
}

double getMaximoYRetangulo(Retangulo ret) {
    StRetangulo r = (StRetangulo) ret;
    return r->y + r->altura;
}

void desalocarRetangulo(Retangulo ret) {
    StRetangulo r = (StRetangulo) ret;
    free(r);

}

bool compararIDRetangulo(Retangulo ret, char *id) {
    StRetangulo r = (StRetangulo) ret;
    return strcmp(r->id, id);
}