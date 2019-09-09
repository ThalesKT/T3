#include "predio.h"


typedef struct predio {
    char cep[35], face;
    double numero, f, profundidade, mrg;
    double x, xMaximo, y, yMaximo;

}*StPredio;


Predio criarPredio(char *cep, char face, double numero, double f, double profundidade, double mrg) {
    Predio prd = malloc(sizeof(struct predio));
    StPredio predio = (StPredio) prd;
    strcpy(predio->cep, cep);
    predio->face = face;
    predio->numero = numero;
    predio->f = f;
    predio->profundidade = profundidade;
    predio->mrg = mrg;

    return predio;
}

void desalocarPredio(Predio prd) {
    StPredio predio = (StPredio) prd;
    free(predio);
}

char *getCepPredio(Predio prd) {
    StPredio predio = (StPredio) prd;
    return predio->cep;
}

double getXPredio(Predio prd) {
    StPredio predio = (StPredio) prd;
    return predio->x;
}

double getYPredio(Predio prd) {
    StPredio predio = (StPredio) prd;
    return predio->y;
}

double getMaximoXPredio(Predio prd) {
    StPredio predio = (StPredio) prd;
    return predio->xMaximo;
}

double getMaximoYPredio(Predio prd) {
    StPredio predio = (StPredio) prd;
    return predio->yMaximo;
}

double getNumeroPredio(Predio prd) {
    StPredio predio = (StPredio) prd;
    return predio->numero;
}


void escreverPredioSVG(Predio prd, double xQuadra,
 double yQuadra, double larguraQuadra,
  double alturaQuadra, FILE *saida) {
    StPredio predio = (StPredio) prd;
    double yPredio, xPredio, xTexto, yTexto;

    if(predio->face == 'N') {
        xPredio = xQuadra + predio->numero - (predio->f/2);
        yPredio = yQuadra + alturaQuadra - predio->mrg - predio->profundidade;
        xTexto = xQuadra + predio->numero - 3;
        yTexto = yQuadra + alturaQuadra - predio->mrg - 3;

        fprintf(saida, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            xPredio,
            yPredio, 
            predio->f, 
            predio->profundidade);

    } else if (predio->face == 'S') {
        xPredio = xQuadra + predio->numero - (predio->f/2);
        yPredio = yQuadra + predio->mrg;
        xTexto = xQuadra + predio->numero - 3;
        yTexto = yQuadra + predio->mrg + 8;

        fprintf(saida, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            xPredio,
            yPredio, 
            predio->f,
            predio->profundidade);

    } else if(predio->face == 'L') {
        xPredio = xQuadra + predio->mrg;
        yPredio = yQuadra + predio->numero - (predio->f/2);
        xTexto = xQuadra + predio->mrg + 1;
        yTexto = yQuadra + predio->numero;

        fprintf(saida, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            xPredio,
            yPredio, 
            predio->profundidade, 
            predio->f);

    } else if(predio->face == 'O') {
        xPredio = xQuadra + larguraQuadra - predio->mrg - predio->profundidade;
        yPredio = yQuadra + predio->numero - (predio->f/2);
        xTexto = xQuadra + larguraQuadra - predio->mrg - 8;
        yTexto = yQuadra + predio->numero;

        fprintf(saida, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"blue\" stroke-width=\"2\" />\n",
            xPredio,
            yPredio, 
            predio->profundidade, 
            predio->f);

    }
    
    fprintf(saida, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"7\" style=\"z-index:100 \">%.0lf</text>\n",
            xTexto,
            yTexto,
            predio->numero);
    
    predio->x = xPredio;
    predio->y = yPredio;
    if(predio->face == 'N' || predio->face == 'S') {
        predio->xMaximo = xPredio + predio->f;
        predio->yMaximo = yPredio + predio->profundidade;
    } else {
        predio->xMaximo = xPredio + predio->profundidade;
        predio->yMaximo = yPredio + predio->f;
    }
}
