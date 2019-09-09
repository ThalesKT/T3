#include "calculos.h"


double distanciaL2(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

double distanciaL1(double x1, double y1, double x2, double y2) {
	return fabs(x1-x2)+fabs(y1-y2);
}

double clamp(double valor, double a, double b) {
    double clamp = valor < a ? a : valor;
    clamp = valor > b ? b : clamp;
    return clamp;
}

bool pontoInterno(double x, double y, Elemento elemento, char *tipo) {

    if(strcmp(tipo,"c") == 0) {
        return pontoInternoCirculo(x, y, elemento);
    } else if(strcmp(tipo, "r") == 0) {
        return pontoInternoRetangulo(x, y, elemento);
    }
}

bool pontoInternoCirculo(double pontoX, double pontoY, Elemento c) {
	double cx = getXCirculo(c), cy = getYCirculo(c), r = getRaioCirculo(c);
    return distanciaL2(pontoX, pontoY, cx, cy) <= r;
}

bool pontoInternoRetangulo(double pontoX, double pontoY, Elemento r) {
	double rx = getXRetangulo(r), ry = getYRetangulo(r), w = getLarguraRetangulo(r), h = getAlturaRetangulo(r);
    return pontoX >= rx && pontoX <= rx+w && pontoY >= ry && pontoY <= ry+h;
}


void centroDeMassa(Elemento elemento, char *tipo, double *ponto) {
	if(strcmp(tipo, "c") == 0) {
		ponto[0] = getXCirculo(elemento);
		ponto[1] = getYCirculo(elemento);

	} else if(strcmp(tipo, "r") == 0) {

		ponto[0] = getXRetangulo(elemento) + getLarguraRetangulo(elemento)/2;
		ponto[1] = getYRetangulo(elemento) + getAlturaRetangulo(elemento)/2;
	}
}


double distanciaL2Centro(Elemento elemento1, Elemento elemento2, char *tipo1, char *tipo2) {
	double *centro1 = malloc(2*sizeof(double));
	double *centro2 = malloc(2*sizeof(double));
	centroDeMassa(elemento1, tipo1, centro1);
	centroDeMassa(elemento2, tipo2, centro2);
	double x1 = centro1[0], y1 = centro1[1], x2 = centro2[0], y2 = centro2[1];
	free(centro1);
	free(centro2);
	return distanciaL2(x1, y1, x2, y2);
}

bool retanguloInternoL1(double x, double y, Retangulo r, double dist) {
	return distanciaL1(x, y, getXRetangulo(r), getYRetangulo(r)) <= dist &&
	distanciaL1(x, y, getMaximoXRetangulo(r), getYRetangulo(r)) <= dist &&
	distanciaL1(x, y, getXRetangulo(r), getMaximoYRetangulo(r)) <= dist &&
	distanciaL1(x, y, getMaximoXRetangulo(r), getMaximoYRetangulo(r)) <= dist;	
}


bool retanguloInternoCirculo(Retangulo r, Circulo c) {
	return pontoInternoCirculo(getXRetangulo(r), getYRetangulo(r), c) &&
	pontoInternoCirculo(getMaximoXRetangulo(r), getYRetangulo(r), c) &&
	pontoInternoCirculo(getXRetangulo(r), getMaximoYRetangulo(r), c) &&
	pontoInternoCirculo(getMaximoXRetangulo(r), getMaximoYRetangulo(r), c);
	
}

bool retanguloInternoRetangulo(Retangulo r1, Retangulo r2) {
	return getXRetangulo(r1) > getXRetangulo(r2) && getMaximoXRetangulo(r1) < getMaximoXRetangulo(r2)
	&& getYRetangulo(r1) > getYRetangulo(r2) && getMaximoYRetangulo(r1) < getMaximoYRetangulo(r2);
	
}