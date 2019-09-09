#include "arquivoQry.h"

void comandoBB(FILE *boundingbox, char *cor, Lista listaFormas) {
    char tipo[15];
    int i = getPrimeiroElementoLista(listaFormas);
    for(i; i != -1; i = getProximoElemento(listaFormas,i)){
        Elemento elemento = getElementoListaPosicao(listaFormas, i);
        getTipoElemento(listaFormas, i, tipo);
        if(strcmp(tipo, "c") == 0) {
            escreverCirculoSVG(elemento, boundingbox);
            retanguloEnvoltaCirculo(elemento, boundingbox, cor);

        } else if(strcmp(tipo, "r") == 0) {
            escreverRetanguloSVG(elemento, boundingbox);
            elipseEnvoltaRetangulo(elemento, boundingbox, cor);

        }
    }
}

void elipseEnvoltaRetangulo(Elemento rect, FILE *boudingbox, char *cor) {
    double x, y, raiox, raioy;
    x = getXRetangulo(rect) + getLarguraRetangulo(rect) / 2;
    y = getYRetangulo(rect) + getAlturaRetangulo(rect) / 2;

    raiox = getLarguraRetangulo(rect) / 2;
    raioy = getAlturaRetangulo(rect) / 2;

    escreverElipseBB(x, y, raiox, raioy, boudingbox, cor);
}

void retanguloEnvoltaCirculo(Elemento circ, FILE *boundingbox, char *cor) {
    double altura, largura, x, y;
    altura = getRaioCirculo(circ) * 2;
    largura = altura;
    x = getXCirculo(circ) - getRaioCirculo(circ);
    y = getYCirculo(circ) - getRaioCirculo(circ);
    escreverRetanguloBB(largura, altura, x, y, boundingbox, cor);
}

void removerQuadrasDQ(Lista listaQuadras, double x, double y, double distancia, char *tipoMetrica,
FILE *saidaTXT) {

    fprintf(saidaTXT,"\tCEP DAS QUADRAS REMOVIDAS\n ");
    int posicaoLista = getPrimeiroElementoLista(listaQuadras);
    //LISTA VAZIA...
    if(posicaoLista == -1) {
        return;
    }

    if(strcmp(tipoMetrica, "L1") == 0 || strcmp(tipoMetrica,"l1") == 0) {
        //printf("METRICA L1\n");
        while(true) {
            Quadra q = getElementoListaPosicao(listaQuadras, posicaoLista);
            Retangulo r = criarRetangulo("L1", getAlturaQuadra(q),
            getLarguraQuadra(q), getXQuadra(q), getYQuadra(q),"mediumturquoise", "firebrick"," 3px");

            //se for a ultima da lista
            if(getProximoElemento(listaQuadras, posicaoLista) == -1) {
                if(retanguloInternoL1(x, y, r, distancia)) {
                    fprintf(saidaTXT,"CEP DELETADO = %s \n",getCepQuadra(q));
                    excluirElementoPosicaoX(listaQuadras, posicaoLista, desalocarQuadra);
                }
                desalocarRetangulo(r);
                break;
                //outra posição qlquer
            } else {
                posicaoLista = getProximoElemento(listaQuadras, posicaoLista);
                if(retanguloInternoL1(x, y, r, distancia)) {
                  fprintf(saidaTXT,"CEP DELETADO = %s \n", getCepQuadra(q));
                  excluirElementoPosicaoX(listaQuadras, getAnteriorElemento(listaQuadras, posicaoLista), desalocarQuadra);
                }
            }
            desalocarRetangulo(r);
        }
    } else if(strcmp(tipoMetrica, "L2") == 0 || strcmp(tipoMetrica, "L2") == 0) {
        Circulo c = criarCirculo("L2", distancia, x, y, "yellow", "blue", "3px");
        //printf("METRICA L2\n");

        while(true) {
            Quadra q = getElementoListaPosicao(listaQuadras, posicaoLista);
            Retangulo r = criarRetangulo("TAFODA", getAlturaQuadra(q), getLarguraQuadra(q), getXQuadra(q),
            getYQuadra(q), "black", "blue", "3px");

            if(getProximoElemento(listaQuadras, posicaoLista) == -1) {
                if(retanguloInternoCirculo(r, c)) {
                    fprintf(saidaTXT,"CEP DELETADO = %s \n",getCepQuadra(q));
                    excluirElementoPosicaoX(listaQuadras, posicaoLista, desalocarQuadra);
                }
                desalocarRetangulo(r);
                break;
            } else {
                posicaoLista = getProximoElemento(listaQuadras, posicaoLista);
                if(retanguloInternoCirculo(r,c)) {
                    fprintf(saidaTXT,"CEP DELETADO = %s \n",getCepQuadra(q));
                    excluirElementoPosicaoX(listaQuadras, getAnteriorElemento(listaQuadras, posicaoLista), desalocarQuadra);
                }
            }
            desalocarRetangulo(r);
        }
        desalocarCirculo(c);
    }
    fprintf(saidaTXT,"DQ FINALIZADO \n\n\n");
}



void colorirQuadrasDentroCirculo(Lista listaQuadras, Circulo c, char *cor, FILE *saidaTXT) {
    //printf("testando \n");
    fprintf(saidaTXT,"Quadras com bordas alteradas pelo comando CBQ\n");
    int i = getPrimeiroElementoLista(listaQuadras);
    for( i ; i != -1; i = getProximoElemento(listaQuadras, i)) {
        Quadra q = getElementoListaPosicao(listaQuadras, i);
        Retangulo r = criarRetangulo("pererecasaltitante", getAlturaQuadra(q), getLarguraQuadra(q),
        getXQuadra(q), getYQuadra(q), "corLInda", "temqvir10", "209px");
        if(retanguloInternoCirculo(r, c)) {
            setCorBordaQuadra(q, cor);
            fprintf(saidaTXT,"CEP QUADRA: %s \n", getCepQuadra(q));
        }
        desalocarRetangulo(r);
    }
}

void desalocarElementosDentroRetangulo(Lista listaQuadras, Lista listaHidrantes, Lista listaRadioBase,
Lista listaSemaforo, Retangulo r, double dx, double dy, FILE *saidaTXT) {
    fprintf(saidaTXT,"ELEMENTOS MOVIDOS PELO COMANDO TRNS\n");
    int i;
    i = getPrimeiroElementoLista(listaQuadras);
    for(i; i != -1; i = getProximoElemento(listaQuadras, i)) {
        Quadra q = getElementoListaPosicao(listaQuadras, i);
        Retangulo rq = criarRetangulo("ultimocomando", getAlturaQuadra(q), getLarguraQuadra(q),
        getXQuadra(q), getYQuadra(q), "corlinda", "sla", "4px");
        if(retanguloInternoRetangulo(rq, r)) {
            fprintf(saidaTXT, "NOVA LOCALIZAÇÃO QUADRA\n");
            fprintf(saidaTXT, "CEP = %s COORDENADAS ANTERIORES: %.2lf %2lf -> NOVAS COORDENADAS: %.2lf %.2lf\n",
            getCepQuadra(q), getXQuadra(q), getYQuadra(q), getXQuadra(q) + dx, getYQuadra(q) + dy);
            setXQuadra(q, getXQuadra(q) + dx);
            setYQuadra(q, getYQuadra(q) + dy);
        }
        desalocarRetangulo(rq);
    }

    i = getPrimeiroElementoLista(listaHidrantes);
    for(i; i != -1; i = getProximoElemento(listaHidrantes, i)) {
        Hidrante h = getElementoListaPosicao(listaHidrantes, i);
        if(pontoInternoRetangulo(getXHidrante(h), getYHidrante(h), r) ) {
            fprintf(saidaTXT, "NOVA LOCALIZAÇÃO HIDRANTE \n");
            fprintf(saidaTXT, "ID: %s COORDENADAS ANTERIORES: %.2lf %.2lf -> NOVAS COORDENADAS: %.2lf %.2lf\n",
            getIDHidrante(h), getXHidrante(h), getYHidrante(h), getXHidrante(h) + dx, getYHidrante(h) + dy);
            setXHidrante(h, getXHidrante(h) + dx);
            setYHidrante(h, getYHidrante(h) + dy);
        }

    }

    i = getPrimeiroElementoLista(listaRadioBase);
    for(i; i != -1; i = getProximoElemento(listaRadioBase, i)) {
        radioBase rb = getElementoListaPosicao(listaRadioBase, i);
        if(pontoInternoRetangulo(getXRadioBase(rb), getYRadioBase(rb), r) ) {
            fprintf(saidaTXT, "NOVA LOCALIZAÇÃO TORRE \n");
            fprintf(saidaTXT, "ID: %s COORDENADAS ANTERIORES: %.2lf %.2lf -> NOVAS COORDENADAS: %.2lf %.2lf\n",
            getIDRadioBase(rb), getXRadioBase(rb), getYRadioBase(rb), getXRadioBase(rb) + dx, getYRadioBase(rb) + dy);
            setXRadioBase(rb, getXRadioBase(rb) + dx);
            setYRadioBase(rb, getYRadioBase(rb) + dy);
        }

    }

    i = getPrimeiroElementoLista(listaSemaforo);
    for(i; i != -1; i = getProximoElemento(listaSemaforo, i)) {
        Semaforo s = getElementoListaPosicao(listaSemaforo, i);
        if(pontoInternoRetangulo(getXSemaforo(s), getYSemaforo(s), r) ) {
            fprintf(saidaTXT, "NOVA LOCALIZAÇÃO SEMAFORO \n");
            fprintf(saidaTXT, "ID: %s COORDENADAS ANTERIORES: %.2lf %.2lf -> NOVAS COORDENADAS: %.2lf %.2lf\n",
            getIDSemaforo(s), getXSemaforo(s), getYSemaforo(s), getXSemaforo(s) + dx, getYSemaforo(s) + dy);
            setXSemaforo(s, getXSemaforo(s) + dx);
            setYSemaforo(s, getYSemaforo(s) + dy);
        }

    }
}

// Struct e função utilizadas para qsort
typedef struct obj {
        double distancia;
        void *Elemento;
} *pObj;

double get_obj_comparador(Elemento o) {
    pObj elemento = (pObj) o;
    return elemento->distancia;
}

void processarFocoIncendio(Lista listaSemaforos, Lista listaHidrantes, double x,
 double y, int ns, double r, FILE *txt, FILE *svg) {
    
    int i, tamanhoLista = getTamanhoLista(listaSemaforos);

    // Semaforos mais proximos do foco de incendio
    pObj* semaforos_comparar = (pObj*)malloc(tamanhoLista*sizeof(pObj));

    i = getPrimeiroElementoLista(listaSemaforos);
    int index = 0;
    for(i; i != -1; i = getProximoElemento(listaSemaforos, i)) {
        Semaforo s = getElementoListaPosicao(listaSemaforos, i);

        double distancia = distanciaL2(x, y, getXSemaforo(s), getYSemaforo(s));

        pObj o = malloc(sizeof(struct obj));
        o->distancia = distancia;
        o->Elemento = s;

        semaforos_comparar[index] = o;
        index++;
    }

    //qsort(semaforos_comparar, tamanhoLista, sizeof(struct obj), compCrescente);
    heapsortMenor((Elemento*)semaforos_comparar, tamanhoLista, ns, get_obj_comparador);
    fprintf(txt, "-- SEMAFOROS PRÓXIMOS AO FOCO DE INCENDIO --\n");
    for(int i = tamanhoLista - ns; i < tamanhoLista; i++) {
        Semaforo s = ((pObj)semaforos_comparar[i])->Elemento;
        fprintf(txt, "ID -> %s\n", getIDSemaforo(s));

        Circulo c1 = criarCirculo("tafoda", 7, getXSemaforo(s), getYSemaforo(s), "orange", "none", "3px");
        escreverCirculoSVG(c1, svg);
        desalocarCirculo(c1);

        Circulo c2 = criarCirculo("tafoda", 9, getXSemaforo(s), getYSemaforo(s), "gold", "none", "3px");
        escreverCirculoSVG(c2, svg);
        desalocarCirculo(c2);

        Muro m = criarMuro(x, y, getXSemaforo(s), getYSemaforo(s));
        escreverMuroSVG(m, svg);
        desalocarMuro(m);
    }

    for(int i = 0; i < tamanhoLista; i++) free(semaforos_comparar[i]);
    free(semaforos_comparar);
    fprintf(txt, "-------------------------------------------\n");

    // Hidrantes dentro de uma distancia r do foco de incendio
    Circulo circ = criarCirculo("tafoda", r, x, y, "gold", "none", "3px");
    i = getPrimeiroElementoLista(listaHidrantes);
    fprintf(txt, "-- HIDRANTES PRÓXIMOS AO FOCO DE INCENDIO --\n");
    for(i; i != -1; i = getProximoElemento(listaHidrantes, i)) {
        Hidrante h = getElementoListaPosicao(listaHidrantes, i);

        if(pontoInternoCirculo(getXHidrante(h), getYHidrante(h), circ)) {
            fprintf(txt, "ID -> %s\n", getIDHidrante(h));

            Circulo c1 = criarCirculo("tafoda", 7, getXHidrante(h), getYHidrante(h), "orange", "none", "3px");
                escreverCirculoSVG(c1, svg);
            desalocarCirculo(c1);

            Circulo c2 = criarCirculo("tafoda", 9, getXHidrante(h), getYHidrante(h), "gold", "none", "3px");
                escreverCirculoSVG(c2, svg);
            desalocarCirculo(c2);

            Muro m = criarMuro(x, y, getXHidrante(h), getYHidrante(h));
            escreverMuroSVG(m, svg);
            desalocarMuro(m);
        }
    }
    desalocarCirculo(circ);
    fprintf(txt, "-------------------------------------------\n");
}


void processarObjetosProximos(Lista listaElemento, Lista listaQuadras, char sinal, int k,
 char cep[], char face, double num, FILE* txt, FILE *svg, char tipo[]) {

    int i;
    double x, y;
    Lista lista;

    if(strcmp(tipo, "hidrante") == 0) {
        lista = listaElemento;
    } else if(strcmp(tipo, "semaforo") == 0) {
        lista = listaElemento;
    }

    int tamanhoLista = getTamanhoLista(lista);

    Quadra q = getElementoLista(listaQuadras, cep, compararIDQuadra);
    if(q == NULL) return;
    if(face == 'N') {
        x = getXQuadra(q) + num;
        y = getYQuadra(q) + getAlturaQuadra(q);
    } else if(face == 'S') {
        x = getXQuadra(q) + num;
        y = getYQuadra(q);
    } else if(face == 'L') {
        x = getXQuadra(q);
        y = getYQuadra(q) + num;
    } else if(face == 'O') {
        x = getXQuadra(q) + getLarguraQuadra(q);
        y = getYQuadra(q) + num;
    }

    pObj* objetos_comparar = (pObj*)malloc(tamanhoLista*sizeof(pObj));

    i = getPrimeiroElementoLista(lista);
    int index = 0;
    for(i; i != -1; i = getProximoElemento(lista, i)) {
        Elemento o = getElementoListaPosicao(lista, i);

        double distancia;
        if(strcmp(tipo, "hidrante") == 0) {
            distancia = distanciaL2(x, y, getXHidrante(o), getYHidrante(o));
        } else if(strcmp(tipo, "semaforo") == 0) {
            distancia = distanciaL2(x, y, getXSemaforo(o), getYSemaforo(o));
        }

        pObj ob = malloc(sizeof(struct obj));
        ob->distancia = distancia;
        ob->Elemento = o;

        objetos_comparar[index] = ob;
        index++;
    }

    if(sinal == '-')
        heapsortMenor((Elemento*)objetos_comparar, tamanhoLista, k, get_obj_comparador);
        //qsort(objetos_comparar, lista_length(lista), sizeof(struct obj), compCrescente);
    else
        heapsortMaior((Elemento*)objetos_comparar, tamanhoLista, k, get_obj_comparador);
        //qsort(objetos_comparar, lista_length(lista), sizeof(struct obj), compDecrescente);
    fprintf(txt, "-- %d %s MAIS %s DO CEP %s --\n", k, ((strcmp(tipo, "hidrante") == 0) ? "HIDRANTES" : "SEMAFOROS"), (sinal == '+' ? "PRÓXIMOS" : "DISTANTES"), cep);
    for(int i = tamanhoLista - k; i < tamanhoLista; i++) {
        Elemento o = ((pObj)objetos_comparar[i])->Elemento;
        Circulo c1, c2;
        Muro m;

        if(strcmp(tipo, "hidrante") == 0) {
            fprintf(txt, "ID -> %s\n", getIDHidrante(o));
            c1 = criarCirculo("dificil", 7, getXHidrante(o), getYHidrante(o), "orange", "none", "3px");
            c2 = criarCirculo("demais", 9, getXHidrante(o), getYHidrante(o), "gold", "none", "3px");
            m = criarMuro(x, y, getXHidrante(o), getYHidrante(o));
        } else if(strcmp(tipo, "semaforo") == 0) {
            fprintf(txt, "ID -> %s\n", getIDSemaforo(o));
            c1 = criarCirculo("dificil", 7, getXSemaforo(o), getYSemaforo(o), "orange", "none", "3px");
            c2 = criarCirculo("demais", 9, getXSemaforo(o), getYSemaforo(o), "gold", "none", "3px");
            m = criarMuro(x, y, getXSemaforo(o), getYSemaforo(o));
        }

        escreverCirculoSVG(c1, svg);
        desalocarCirculo(c1);

        escreverCirculoSVG(c2, svg);
        desalocarCirculo(c2);

        escreverMuroSVG(m, svg);
        desalocarMuro(m);
    }
    for(int i = 0; i < tamanhoLista; i++) free(objetos_comparar[i]);
    free(objetos_comparar);
    fprintf(txt, "-------------------------------------------\n");
}