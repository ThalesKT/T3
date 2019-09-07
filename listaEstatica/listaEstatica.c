#include "listaEstatica.h"



typedef struct node {
    int proximo;
    int anterior;
    void *elemento;
    char id[100];
    char tipo[3]; 
    /* Tipo 
        c = circulo
        r = retangulo
        rb = radio base
        q = quadra
        assim sucessivamente
    */

   /*
    ID = ID dos elementos do T2;
    */
}*StNode;

typedef struct infoLista {
    StNode listaNode;
    int primeiroElemento;
    int ultimoElemento;
    int tamanhoAtual, tamanhoMaximo, proximoLivre;

}*StInfoLista;

Lista inicializarLista(int tamanhoMax) {
    Lista l = malloc(sizeof(struct infoLista));
    StInfoLista list = (StInfoLista) l;

    list->listaNode = (StNode) malloc(tamanhoMax*sizeof(struct node));
    list->tamanhoMaximo = tamanhoMax;
    list->tamanhoAtual = 0;

    for(int i=0; i < (tamanhoMax - 1); i++) {
        list->listaNode[i].proximo = i + 1;
    }

    list->listaNode[tamanhoMax - 1].proximo = -1;
    list->primeiroElemento = -1;
    list->ultimoElemento = -1;
    list->proximoLivre = 0;

    return list;
}


void destruirLista(Lista l, void(*destruirElemento)(Elemento elemento)) {
    StInfoLista list = (StInfoLista) l;

    for(int i = list->primeiroElemento; i != -1; i = list->listaNode[i].proximo) {
        destruirElemento(list->listaNode[i].elemento);
    }
    free(list->listaNode);
    free(list);
}


int getPosicaoLivreLista(Lista l) { 
    StInfoLista list = (StInfoLista) l;
    int livre = list->proximoLivre;
        if(livre != -1)
            list->proximoLivre = list->listaNode[list->proximoLivre].proximo;
    
    return livre;
}

int getPrimeiroElementoLista(Lista l) {
    StInfoLista list = (StInfoLista) l;

    return list->primeiroElemento;
}

int getProximoElemento(Lista l, int posicao) { 
    StInfoLista list = (StInfoLista) l;
    return list->listaNode[posicao].proximo;
}

int getAnteriorElemento(Lista l, int posicao) { 
    StInfoLista list = (StInfoLista) l;
    return list->listaNode[posicao].anterior;
}

bool inserirFinalLista(Lista l, Elemento elemento, char *tipo, char *id) {
    StInfoLista list = (StInfoLista) l;
    int posicaoLivre = getPosicaoLivreLista(l);

    if(posicaoLivre == -1) {
        printf("Lista cheia. \n");
        return false;
    }

    if(list->primeiroElemento == -1) {
        if(list->tamanhoAtual + 1 <= list->tamanhoMaximo) { 
            list->listaNode[posicaoLivre].anterior = -1;
            list->listaNode[posicaoLivre].elemento = elemento;
            strcpy(list->listaNode[posicaoLivre].tipo, tipo);
            strcpy(list->listaNode[posicaoLivre].id, id);
            list->listaNode[posicaoLivre].proximo = -1;
            list->primeiroElemento = 0;
            list->ultimoElemento = 0;
            list->tamanhoAtual++;
            return true;
        }

    } else if(list->tamanhoAtual + 1 <= list->tamanhoMaximo) {
        list->listaNode[list->ultimoElemento].proximo = posicaoLivre;
        list->listaNode[posicaoLivre].elemento = elemento;
        strcpy(list->listaNode[posicaoLivre].tipo, tipo);
        strcpy(list->listaNode[posicaoLivre].id, id);
        list->listaNode[posicaoLivre].anterior = list->ultimoElemento;
        list->listaNode[posicaoLivre].proximo = -1;
        list->tamanhoAtual++;
        list->ultimoElemento = posicaoLivre;
        return true;
    }
    return false;

}

bool excluirElementoLista(Lista l, char *identificador, 
    bool(*comparar)(Elemento elementoLista, char *identificador), 
    void(*desalocarElemento)(Elemento elemento)) {
    
    StInfoLista list = (StInfoLista) l;
    
    for(int i = list->primeiroElemento ; i != -1; i = list->listaNode[i].proximo) {
        //se o id do elemento for igual o identificador
        if(comparar(list->listaNode[i].elemento, identificador)) {
            //se o elemento for o primeiro, a struct info vai receber o segundo elemento agora como sendo 
            //o primeiro
            if(i == list->primeiroElemento) {
                list->primeiroElemento = list->listaNode[i].proximo;
            //se o elemento for ultimo vai fazer o anteriror virar o ultimo
            } else if(list->listaNode[i].proximo == -1) {
                list->listaNode[list->listaNode[i].anterior].proximo = -1;
                list->ultimoElemento = list->listaNode[i].anterior;
            } else {
                list->listaNode[list->listaNode[i].anterior].proximo = list->listaNode[i].proximo;
                list->listaNode[list->listaNode[i].proximo].anterior = list->listaNode[i].anterior;
            }
            list->tamanhoAtual--;
            desalocarElemento(list->listaNode[i].elemento);
            list->listaNode[i].proximo = list->proximoLivre;
            list->proximoLivre = i;
            return true;
        }
    }
    return false;
}

int getTamanhoLista(Lista l) {
    StInfoLista list = (StInfoLista) l;
    return list->tamanhoAtual;
}

Elemento getElementoLista(Lista l, 
    char *identificador, 
    bool(*comparar)(Elemento elementoLista, char *identificador)) {

    StInfoLista list = (StInfoLista) l;

    for(int i = list->primeiroElemento; i != -1; i = list->listaNode[i].proximo) {

        if(comparar(list->listaNode[i].elemento, identificador)) {
            return list->listaNode[i].elemento;
        }
    }
    return NULL;
}

void escreverListaSVG(Lista l, void(*escreverSVG)(Elemento elemento,FILE *saida), FILE *saida) {
    StInfoLista list = (StInfoLista) l;
    int d = 0;
    for(int i = list->primeiroElemento; i != -1; i = list->listaNode[i].proximo) {
        escreverSVG(list->listaNode[i].elemento, saida);
        //printf("quantidade de vezes q entra no for: %i \n",d);
        //d++;
    }
}

Elemento getElementoeTipo(Lista l, char *tipo, char *id) {
    StInfoLista list = (StInfoLista) l;

    for(int i = list->primeiroElemento; i != -1; i = list->listaNode[i].proximo) {
        
        if(strcmp(list->listaNode[i].id, id) == 0) {
            strcpy(tipo, list->listaNode[i].tipo);
            return list->listaNode[i].elemento;
        }
    }
    return NULL;
}

Elemento getElementoListaPosicao(Lista l, int i) {
    StInfoLista list = (StInfoLista) l;
    return list->listaNode[i].elemento;
}
//usado no boudingbox
void getTipoElemento(Lista l, int i, char *tipo) {
    StInfoLista list = (StInfoLista) l;
    strcpy(tipo, list->listaNode[i].tipo);
}



bool excluirElementoPosicaoX(Lista l, int i, void(*apagarElemento)(Elemento elemento)) {

    StInfoLista lista = (StInfoLista) l;
    if(i == lista->primeiroElemento) {
        lista->primeiroElemento = lista->listaNode[i].proximo;

    } else if(lista->listaNode[i].proximo == -1) {
        lista->listaNode[lista->listaNode[i].anterior].proximo = -1;
        lista->ultimoElemento = lista->listaNode[i].anterior;

    } else {
        lista->listaNode[lista->listaNode[i].anterior].proximo = lista->listaNode[i].proximo;
        lista->listaNode[lista->listaNode[i].proximo].anterior = lista->listaNode[i].anterior;
    }
    lista->tamanhoAtual--;
    apagarElemento(lista->listaNode[i].elemento);
    lista->listaNode[i].proximo = lista->proximoLivre;
    lista->proximoLivre = i;
    return true;
}