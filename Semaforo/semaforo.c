#include "semaforo.h"

typedef struct semaforo {
    double x, y;
    char corDentro[75], corBorda[75], espessuraBorda[75], id[75];
}*StSemaforo;

Semaforo criarSemaforo(char *id, double x, double y, char *corBorda, char *corDentro, char *espessuraBorda){
    Semaforo s = malloc(sizeof (struct semaforo));
    StSemaforo semaforo = (StSemaforo) s;
    semaforo->x = x;
    semaforo->y = y;
    strcpy(semaforo->id, id);
    strcpy(semaforo->corBorda, corBorda);
    strcpy(semaforo->corDentro, corDentro);
    strcpy(semaforo->espessuraBorda, espessuraBorda);
    return semaforo;
}

void escreverSemaforoSVG(Semaforo s, FILE *saida) {
    StSemaforo semaf = (StSemaforo) s;


    fprintf(saida, "<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\"/>\n",
    semaf->x,
    semaf->y,
    semaf->corDentro,
    semaf->corBorda,
    semaf->espessuraBorda);

    fprintf(saida, "<text x=\"%lf\" y=\"%lf\" fill=\"white\" font-size=\"9\" style=\"z-index:100\">S</text>\n",
    (semaf->x - 3.2),
    semaf->y + 3);

}

double getXSemaforo(Semaforo s) {
    StSemaforo sem = (StSemaforo) s;
    return sem->x;
}

double getYSemaforo(Semaforo s) {
    StSemaforo sem = (StSemaforo) s;
    return sem->y;
}

bool compararIDSemaforo(Semaforo s, char *id) {
    StSemaforo sem = (StSemaforo) s;
    return strcmp(sem->id, id);
}

void desalocarSemaforo(Semaforo s) {
    StSemaforo sem = (StSemaforo) s;
    free(s);
}

void setXSemaforo(Semaforo s, double x) {
    StSemaforo sem = (StSemaforo) s;
    sem->x = x;
}

void setYSemaforo(Semaforo s, double y) {
    StSemaforo sem = (StSemaforo) s;
    sem->y = y;
}

char* getIDSemaforo(Semaforo s) {
    StSemaforo sem = (StSemaforo) s;
    return sem->id;
}