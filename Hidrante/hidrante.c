#include "hidrante.h"

typedef struct hidrante {
    double x, y;
    char corDentro[75], corBorda[75], espessuraBorda[75], id[75];
}*StHidrante;

Hidrante criarHidrante(char *id, double x, double y, char *corBorda, char *corDentro, char *espessuraBorda){
    Hidrante h = malloc(sizeof (struct hidrante));
    StHidrante hidrante = (StHidrante) h;
    hidrante->x = x;
    hidrante->y = y;
    strcpy(hidrante->id, id);
    strcpy(hidrante->corBorda, corBorda);
    strcpy(hidrante->corDentro, corDentro);
    strcpy(hidrante->espessuraBorda, espessuraBorda);
    return hidrante;
}

void escreverHidranteSVG(Hidrante h, FILE *saida) {
    StHidrante hidra = (StHidrante) h;


    fprintf(saida, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\"/>\n",
    hidra->x,
    hidra->y,
    hidra->corDentro,
    hidra->corDentro,
    hidra->espessuraBorda);

    fprintf(saida, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"9\" style=\"z-index:100\">H</text>\n",
    hidra->x - 3.2,
    hidra->y + 3);

}

double getXHidrante(Hidrante h) {
    StHidrante hid = (StHidrante) h;
    return hid->x;
}

double getYHidrante(Hidrante h) {
    StHidrante hid = (StHidrante) h;
    return hid->y;
}

bool compararIDHidrante(Hidrante h, char *id) {
    StHidrante hid = (StHidrante) h;
    return strcmp(hid->id, id) == 0;
}

void desalocarHidrante(Hidrante h) {
    StHidrante hid = (StHidrante) h;
    free(hid);
}

void setXHidrante(Hidrante h, double x) {
    StHidrante hid = (StHidrante) h;
    hid->x = x;
}

void setYHidrante(Hidrante h, double y) {
    StHidrante hid = (StHidrante) h;
    hid->y = y;
}

char* getIDHidrante(Hidrante h) {
    StHidrante hid = (StHidrante) h;
    return hid->id;
}