#include "muro.h"

typedef struct muro {
    Ponto p1, p2;
}*StMuro;

Muro criarMuro(double x1, double y1, double x2, double y2) {
    Muro m = malloc(sizeof(struct muro));
    StMuro muro = (StMuro) m;
    muro->p1 = criarPonto(x1, y1);
    muro->p2 = criarPonto(x2, y2);
    return muro;
}

void desalocarMuro(Muro m) {
    StMuro muro = (StMuro) m;
    free(muro->p1);
    free(muro->p2);
    free(muro);
}

Ponto getPonto1Muro(Muro m) {
    StMuro muro = (StMuro) m;
    return muro->p1;
}

Ponto getPonto2Muro(Muro m) {
    StMuro muro = (StMuro) m;
    return muro->p2;
}

void escreverMuroSVG(Muro m, FILE *saida) {
    StMuro muro = (StMuro) m;
    fprintf(saida, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(0,0,0);stroke-width:2\" />\n", 
           getXPonto(muro->p1),
            getYPonto(muro->p1),
            getXPonto(muro->p2),
            getYPonto(muro->p2));
}