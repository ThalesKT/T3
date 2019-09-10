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


int comparador(const void *x, const void *y) {
    Vertice a = *((Vertice*) x);
    Vertice b = *((Vertice*) y);
    if(getAnguloVertice(a) < getAnguloVertice(b))
        return -1;
    else if(getAnguloVertice(a) > getAnguloVertice(b))
        return 1;
    else if(getDistanciaVertice(a) < getDistanciaVertice(b))
        return -1;
    else if(getDistanciaVertice(a) > getDistanciaVertice(b))
        return 1;
    else if(!getInicioVertice(a) && getInicioVertice(b))
        return -1;
    else if(getInicioVertice(a) && !getInicioVertice(b))
        return 1;
    return 0;
}


void processarBombaRL(Lista listaPredios, Lista listaMuros, double x, double y, FILE *svg) {
    Ponto pontoMin = criarPonto(x, y);
    Ponto pontoMax = criarPonto(x, y);
    int i, tamListaSegmentos = (getTamanhoLista(listaPredios)*4) + getTamanhoLista(listaMuros) + 4;
    
    Segmento* lista_segmentos = (Segmento*)malloc(tamListaSegmentos*sizeof(Segmento));

    // Aqui será definida a lista de segmentos
    i = getPrimeiroElementoLista(listaPredios);
    int index = 0;
    for(i; i != -1; i = getProximoElemento(listaPredios, i)) {
        Predio p = getElementoListaPosicao(listaPredios, i);

        setMinPonto(pontoMin, getXPredio(p), getYPredio(p));
        setMaxPonto(pontoMax, getMaximoXPredio(p), getMaximoYPredio(p));

        Vertice v_x1 = criarVertice(getXPredio(p), getYPredio(p), x, y);
        Vertice v_x2 = criarVertice(getXPredio(p), getYPredio(p), x, y);
        Vertice v_x_max1 = criarVertice(getMaximoXPredio(p), getYPredio(p), x, y);
        Vertice v_x_max2 = criarVertice(getMaximoXPredio(p), getYPredio(p), x, y);
        Vertice v_y_max1 = criarVertice(getXPredio(p), getMaximoYPredio(p), x, y);
        Vertice v_y_max2 = criarVertice(getXPredio(p), getMaximoYPredio(p), x, y);
        Vertice v_xy_max1 = criarVertice(getMaximoXPredio(p), getMaximoYPredio(p), x, y);
        Vertice v_xy_max2 = criarVertice(getMaximoXPredio(p), getMaximoYPredio(p), x, y);

        Segmento s1 = criarSegmento(v_x1, v_x_max1);
        Segmento s2 = criarSegmento(v_x2, v_y_max1);
        Segmento s3 = criarSegmento(v_x_max2, v_xy_max1);
        Segmento s4 = criarSegmento(v_y_max2, v_xy_max2);
        
        setInicioVerticesSegmento(s1);
        setInicioVerticesSegmento(s2);
        setInicioVerticesSegmento(s3);
        setInicioVerticesSegmento(s4);

        lista_segmentos[index] = s1; index++;
        lista_segmentos[index] = s2; index++;
        lista_segmentos[index] = s3; index++;
        lista_segmentos[index] = s4; index++;
    }

    i = getPrimeiroElementoLista(listaMuros);
    for(i; i != -1; i = getProximoElemento(listaMuros, i)) {
        Muro m = getElementoListaPosicao(listaMuros, i);

        // Eu nao sei onde esta os pontos do muro, portanto tenho que testar os dois ;/
        Ponto p1 = getPonto1Muro(m);
        Ponto p2 = getPonto2Muro(m);

        setMinPonto(pontoMin, getXPonto(p1), getYPonto(p1));
        setMinPonto(pontoMin, getXPonto(p2), getYPonto(p2));
        setMaxPonto(pontoMax, getXPonto(p1), getYPonto(p1));
        setMaxPonto(pontoMax, getXPonto(p2), getYPonto(p2));

        if(getXPonto(p1) == x && getXPonto(p2) == x || getYPonto(p1) == y && getYPonto(p2) == y) 
            continue;

        Vertice v1 = criarVertice(getXPonto(p1), getYPonto(p1), x, y);
        Vertice v2 = criarVertice(getXPonto(p2), getYPonto(p2), x, y);

        Segmento s = criarSegmento(v1, v2);

        setInicioVerticesSegmento(s);
        
        lista_segmentos[index] = s; index++;
    }
  
    tamListaSegmentos = index + 4;

    // Até aqui foi definida a lista de segmentos,
    // com os vertices marcados de inicio ou fim e seus respectivos angulos em relação à x,y

    // Aqui é definido o ponto max+100 do maior ponto e ponto min-100 do menor ponto
    // Alem disso sao adicionados à lista de segmentos os segmentos de borda
    setXPonto(pontoMin, getXPonto(pontoMin) - 100);
    setYPonto(pontoMin, getYPonto(pontoMin) - 100);
    setXPonto(pontoMax, getXPonto(pontoMax) + 100);
    setYPonto(pontoMax, getYPonto(pontoMax) + 100);

    double x_min = getXPonto(pontoMin);
    double x_max = getXPonto(pontoMax);
    double y_min = getYPonto(pontoMin);
    double y_max = getYPonto(pontoMax);

    Vertice v_ce = criarVertice(x_min, y_min, x, y);
    Vertice v_ce1 = criarVertice(x_min, y_min, x, y);
    Vertice v_cd = criarVertice(x_max, y_min, x, y);
    Vertice v_cd1 = criarVertice(x_max, y_min, x, y);
    Vertice v_be = criarVertice(x_min, y_max, x, y);
    Vertice v_be1 = criarVertice(x_min, y_max, x, y);
    Vertice v_bd = criarVertice(x_max, y_max, x, y);
    Vertice v_bd1 = criarVertice(x_max, y_max, x, y);

    Segmento sc = criarSegmento(v_ce1, v_cd);
    Segmento sd = criarSegmento(v_cd1, v_bd);
    Segmento sb = criarSegmento(v_bd1, v_be);
    Segmento se = criarSegmento(v_be1, v_ce);

    setInicioVerticesSegmento(sc);
    setInicioVerticesSegmento(sd);
    setInicioVerticesSegmento(sb);
    setInicioVerticesSegmento(se);

    setSVertice(v_ce1, sc);
    setSVertice(v_cd, sc);
    setSVertice(v_cd1, sd);
    setSVertice(v_bd, sd);
    setSVertice(v_bd1, sb);
    setSVertice(v_be, sb);
    setSVertice(v_be1, se);
    setSVertice(v_ce, se);

    lista_segmentos[index] = sc; index++;
    lista_segmentos[index] = sd; index++;
    lista_segmentos[index] = sb; index++;
    lista_segmentos[index] = se; index++;

    // Aqui será feito o segmento para o corte inicial dos segmentos que interceptam
    Vertice v_inicial = criarVertice(x, y, 0, 0);
    Vertice v_final = criarVertice(getXPonto(pontoMin) - 1, y, 0, 0);
    Segmento s_inicial = criarSegmento(v_inicial, v_final); // Semi reta do ponto inicial até x_min
    setSVertice(v_inicial, s_inicial);
    setSVertice(v_final, s_inicial);

    setInicioVertice(v_inicial, true);
    setInicioVertice(v_final, false);

    // Para verificar a linha de corte inicial, descomentar:
    // Muro mur = criarMuro(x, y, getXPonto(pontoMin) - 1, y);
    // Muro_escreverSvg(mur, svg);
    
    escreverBombaRL(svg, x, y);

    int tamListaVertices = tamListaSegmentos*2;
    Vertice* lista_vertices = (Vertice*)malloc(tamListaVertices*sizeof(Vertice));
    index = 0;
    for(int i = 0; i < tamListaSegmentos; i++) {
        // Verificar se os segmentos interceptam
        if(verificarSegmentosInterceptam(s_inicial, lista_segmentos[i])) {

            tamListaVertices+=2;
            lista_vertices = (Vertice*)realloc(lista_vertices, tamListaVertices*sizeof(Vertice));
            Segmento s = lista_segmentos[i];

            // x onde s_inicial e segmento interceptam
            double x_inter = buscarXInterseccaoSegmento(s, y);
            
            Vertice v_inicio = getInicioVertice(getV1Segmento(s)) ? getV1Segmento(s) : getV2Segmento(s);
            Vertice v_final = getInicioVertice(getV1Segmento(s)) ? getV2Segmento(s) : getV1Segmento(s);
            
            Vertice v_final_meio = criarVertice(x_inter, y, x, y);
            setInicioVertice(v_final_meio, false);
            setAnguloVertice(v_final_meio, M_PI);
            Vertice v_inicial_meio = criarVertice(x_inter, y, x, y);
            setInicioVertice(v_inicial_meio, true);
            setAnguloVertice(v_inicial_meio, -M_PI);

            Segmento s1 = criarSegmento(v_inicio, v_final_meio);
            Segmento s2 = criarSegmento(v_inicial_meio, v_final);

            setSVertice(v_inicio, s1);
            setSVertice(v_final_meio, s1);
            setSVertice(v_inicial_meio, s2);
            setSVertice(v_final, s2);

            lista_vertices[index] = v_inicio; index++;
            lista_vertices[index] = v_final_meio; index++;
            lista_vertices[index] = v_inicial_meio; index++;
            lista_vertices[index] = v_final; index++;

            // Dar free no segmento q foi repartido, pois nao tera mais acesso a ele
            desalocarSegmento(s);
        } else {
            Segmento s = lista_segmentos[i];
            Vertice v1 = getV1Segmento(s);
            Vertice v2 = getV2Segmento(s);    
            setSVertice(v1, s);
            setSVertice(v2, s);

            lista_vertices[index] = v1; index++;
            lista_vertices[index] = v2; index++;
        }
    }

    qsort(lista_vertices, tamListaVertices, sizeof(Vertice), comparador);
    // heapsortMaior(lista_vertices, tamListaVertices, tamListaVertices, getAnguloVertice);
    
    // A partir daqui será varrido todos os vertices no sentido horario começando pela esquerda
    Lista segmentos_ativos = inicializarLista((int)tamListaVertices/2);
    Vertice biombo = criarVertice(getXVertice(lista_vertices[0]), getYVertice(lista_vertices[0]), x, y);
    setSVertice(biombo, getSVertice(lista_vertices[0]));

    for(int i = 0; i < tamListaVertices; i++) {

        Vertice v = lista_vertices[i];
        Segmento sv = getSVertice(v);
        Segmento s_formado_v = buscarSegmentoFormadoComVertice(x, y, v, pontoMin, pontoMax);
        Segmento seg_mais_prox = NULL;

        int j = getPrimeiroElementoLista(segmentos_ativos);

        // Definindo a menor distancia entre centro e o vertice como MAX
        double menor_dist = INT_MAX;
        for(j; j != -1; j = getProximoElemento(segmentos_ativos, j)) {
            Segmento s = getElementoListaPosicao(segmentos_ativos, j);
            if(s == sv) continue;

            // Verificar se segmento formado e o da lista interceptam
            if(verificarSegmentosInterceptam(s_formado_v, s)) {
                // Buscar ponto de intersecção
                Ponto intersec = buscarPontoInterseccao(s_formado_v, s);
                double dist_centro_intersec = distanciaL2(x, y, getXPonto(intersec), getYPonto(intersec));
                if(dist_centro_intersec < menor_dist) {
                    menor_dist = dist_centro_intersec;
                    seg_mais_prox = s;
                }
                desalocarPonto(intersec);
            }
        }

        if(getInicioVertice(v)) {
            // Circulo c1 = criarCirculo(getXVertice(v), Vertice_get_y(v), 2, "green", "green", "2px");
            // Circulo_escreverSvg(c1, svg);
        
            bool segEhOMaisProx;
            if(distanciaL2(x, y, getXVertice(v), getYVertice(v)) < menor_dist){
                segEhOMaisProx = true;

            } else {
                segEhOMaisProx = false;
                
            }
            //SEGFAUT DAQUI PARA BAIXO
            if(segEhOMaisProx) {
                Ponto intersec_biombo = buscarPontoInterseccao(s_formado_v, getSVertice(biombo));
                Vertice v_intersec = criarVertice(getXPonto(intersec_biombo), getYPonto(intersec_biombo), x, y);
                Segmento s1 = criarSegmento(biombo, v_intersec);
                Segmento s2 = criarSegmento(v_intersec, v);
                
                escreverTrianguloBRL(svg, x, y, biombo, v_intersec);
                //escreverTrianguloBRL(svg, x, y, v_intersec, v);

                biombo = v;
                desalocarPonto(intersec_biombo);
            }

            inserirFinalLista(segmentos_ativos, sv,"s","temqterid");
            

        } else {
            // Circulo c1 = criarCirculo(getXVertice(v)-5, Vertice_get_y(v)-5, 2, "red", "red", "2px");
            // Circulo_escreverSvg(c1, svg);
            bool segEhOMaisProx;
            if(distanciaL2(x, y, getXVertice(v), getYVertice(v)) <= menor_dist)
                segEhOMaisProx = true;
            else
                segEhOMaisProx = false;

            if(segEhOMaisProx) {
                if(seg_mais_prox != NULL) {
                    Ponto intersec_biombo = buscarPontoInterseccao(s_formado_v, seg_mais_prox);
                    Vertice v_intersec = criarVertice(getXPonto(intersec_biombo), getYPonto(intersec_biombo), x, y);

                    Segmento s1 = criarSegmento(biombo, v);
                    Segmento s2 = criarSegmento(v, v_intersec);

                    escreverTrianguloBRL(svg, x, y, v, v_intersec);
                    escreverTrianguloBRL(svg, x, y, biombo, v);

                    biombo = v_intersec;
                    setSVertice(biombo, seg_mais_prox);
                    desalocarPonto(intersec_biombo);
                 } else {
                    Segmento s = criarSegmento(biombo, v);
                    escreverTrianguloBRL(svg, x, y, biombo, v);
                    biombo = v;
                 }
            }

            excluirElementoMemoriaLista(segmentos_ativos, sv);
        }

    }
    for(int i = 0; i < tamListaVertices; i++) desalocarVertice(lista_vertices[i]);
    // lista_destruir(segmentos_ativos, destruirSegmento);
    desalocarPonto(pontoMin);
    desalocarPonto(pontoMax);
    desalocarVertice(v_final);
    desalocarVertice(v_inicial);
    free(lista_segmentos);
    free(lista_vertices);
}