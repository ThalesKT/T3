#include "quadra.h"

typedef struct quadra {
    double x, y, altura, largura;
    char cep[150], corDentro[75], corBorda[75], espessuraBorda[75];

}*StQuadra;

Quadra criarQuadra(char *cep, double x, double y, double altura, double largura,
char *corBorda, char *corDentro, char *espessuraBorda) {
    Quadra q = malloc(sizeof(struct quadra));
    StQuadra quadra = (StQuadra) q;
    quadra->x = x;
    quadra->y = y;
    quadra->altura = altura;
    quadra->largura = largura;
    strcpy(quadra->cep, cep);
    strcpy(quadra->corBorda, corBorda);
    strcpy(quadra->corDentro, corDentro);
    strcpy(quadra->espessuraBorda, espessuraBorda);
    return quadra;
}

void escreverQuadraSVG(Quadra q, FILE *saida) {
    StQuadra quadra = (StQuadra) q;

    fprintf(saida,"<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\" /> \n",
    quadra->largura,
    quadra->altura,
    quadra->x,
    quadra->y,
    quadra->corBorda,
    quadra->corDentro,
    quadra->espessuraBorda);

    fprintf(saida, "<text x=\"%lf\" y=\"%lf\" fill=\"red\" font-size=\"9\" style=\"z-index:100\">%s</text>\n",
    quadra->x,
    quadra->y + 16,
    quadra->cep);
}


double getXQuadra(Quadra q) {
    StQuadra quadra = (StQuadra) q;
    return quadra->x;
}

double getYQuadra(Quadra q) {
    StQuadra quadra = (StQuadra) q;
    return quadra->y;
}

double getAlturaQuadra(Quadra q) {
    StQuadra quadra = (StQuadra) q;
    return quadra->altura;
}

double getLarguraQuadra(Quadra q) {
    StQuadra quadra = (StQuadra) q;
    return quadra->largura;
}

void desalocarQuadra(Quadra q) {
    StQuadra quadra = (StQuadra) q;
    free(quadra);
}

char* getCepQuadra(Quadra q) {
    StQuadra quadra = (StQuadra) q;
    return quadra->cep;
}

bool compararIDQuadra(Quadra q, char *cep) {
    StQuadra quadra = (StQuadra) q;
    return strcmp(quadra->cep, cep) == 0;
}

void setCorBordaQuadra(Quadra q, char *cor) {
    StQuadra quadra = (StQuadra) q;
    strcpy(quadra->corBorda, cor);
}

void setXQuadra(Quadra q, double x) {
    StQuadra quadra = (StQuadra) q;
    quadra->x = x;
}

void setYQuadra(Quadra q, double y) {
    StQuadra quadra = (StQuadra) q;
    quadra->y = y;
}