#include "colisao.h"

bool elementosColidem(Elemento elemento1, Elemento elemento2,
char *tipo1, char *tipo2) {
    if(strcmp(tipo1, "c") == 0 && strcmp(tipo2, "r") == 0) 
        return colisaoCirculoRetangulo(elemento1, elemento2);
    else if (strcmp(tipo1, "r") == 0 && strcmp(tipo2, "c") == 0)
        return colisaoCirculoRetangulo(elemento2, elemento1);
    else if(strcmp(tipo1, "r") == 0 && strcmp(tipo2, "r") == 0)
        return colisao2Retangulo(elemento1, elemento2);
    else if(strcmp(tipo1, "c") == 0 && strcmp(tipo2, "c") == 0)
        return colisao2Circulo(elemento1, elemento2);
    
}

bool colisaoCirculoRetangulo(Circulo c, Retangulo r) {
    double xMaisProximo = clamp(getXCirculo(c), getXRetangulo(r), getMaximoXRetangulo(r));
    double yMaisProximo = clamp (getYCirculo(c), getYRetangulo(r), getMaximoYRetangulo(r));

    if(distanciaL2(getXCirculo(c), getYCirculo(c), xMaisProximo, yMaisProximo) < getRaioCirculo(c)) {
        return true;
    }
    return false;
}

bool colisao2Retangulo(Retangulo r1, Retangulo r2) {
    return(getXRetangulo(r1) < getMaximoXRetangulo(r2)) && (getMaximoXRetangulo(r1) > getXRetangulo(r2)) &&
    (getYRetangulo(r1) < getMaximoYRetangulo(r2)) && (getMaximoYRetangulo(r1) > getYRetangulo(r2));
}


bool colisao2Circulo(Circulo c1, Circulo c2) {
    return distanciaL2(getXCirculo(c1), getYCirculo(c1), getXCirculo(c2), getYCirculo(c2)) 
    < getRaioCirculo(c1) + getRaioCirculo(c2);
}


