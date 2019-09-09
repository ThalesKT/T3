#include "radioBase.h"

typedef struct RadioBase {
    double x, y;
    char corDentro[75], corBorda[75], espessuraBorda[75], id[75];
}*StRadioBase;

radioBase criarRadioBase(char *id, double x, double y, char *corBorda, char *corDentro, char *espessuraBorda){
    radioBase s = malloc(sizeof (struct RadioBase));
    StRadioBase RadioBase = (StRadioBase) s;
    RadioBase->x = x;
    RadioBase->y = y;
    strcpy(RadioBase->id, id);
    strcpy(RadioBase->corBorda, corBorda);
    strcpy(RadioBase->corDentro, corDentro);
    strcpy(RadioBase->espessuraBorda, espessuraBorda);
    return RadioBase;
}

void escreverRadioBaseSVG(radioBase r, FILE *saida) {
    StRadioBase torre = (StRadioBase) r;

    fprintf(saida, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\"/>\n",
    torre->x,
    torre->y,
    torre->corDentro,
    torre->corBorda,
    torre->espessuraBorda);

    fprintf(saida, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"9\" style=\"z-index:100\">T</text>\n",
    torre->x - 3.2,
    torre->y + 3);

}

double getXRadioBase(radioBase r) {
    StRadioBase radio = (StRadioBase) r;
    return radio->x;
}

double getYRadioBase(radioBase r) {
    StRadioBase radio = (StRadioBase) r;
    return radio->y;
}

bool compararIDRadioBase(radioBase r, char *id) {
    StRadioBase radio = (StRadioBase) r;
    return strcmp(radio->id, id) == 0;
}

void desalocarRadioBase(radioBase r) {
    StRadioBase radio = (StRadioBase) r;
    free(radio);
}

void setXRadioBase(radioBase r, double x) {
    StRadioBase radio = (StRadioBase) r;
    radio->x = x;
}

void setYRadioBase(radioBase r, double y) {
    StRadioBase radio = (StRadioBase) r;
    radio->y = y;
}

char* getIDRadioBase(radioBase r) {
    StRadioBase radio = (StRadioBase) r;
    return radio->id;
}