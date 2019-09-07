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
        printf("METRICA L1\n");
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
        printf("METRICA L2\n");

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
