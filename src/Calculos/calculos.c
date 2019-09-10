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

Segmento buscarSegmentoFormadoComVertice(double xc, double yc, Vertice v, Ponto pontoMin, Ponto pontoMax) {
	double xv = getXVertice(v), yv = getYVertice(v);
	double a, b;
	if(xv != xc) { // reta perpendicular ver dps
		a = (yv-yc)/(xv-xc);
		b = yc - a*xc;
	}

	double xq, yq;
	// y = ax + b
	// x = (y-b)/a
	if(xc < xv && yc > yv) { 
		xq = (getYPonto(pontoMin) - 50 - b)/a;
		yq = a*(getXPonto(pontoMax) + 50) + b;
		if(distanciaL2(xc, yc, xq, getYPonto(pontoMin) - 50) > distanciaL2(xc, yc, getXPonto(pontoMax) + 50, yq)) {
			yq = getYPonto(pontoMin) - 50;
		} else {
			xq = getXPonto(pontoMax) + 50;
		}
	} else if(xc < xv && yc == yv) { // certo
		xq = getXPonto(pontoMax) + 50;
		yq = yc;
	} else if(xc < xv && yc < yv) {
		xq = (yc + 50 - b)/a;
		yq = a*(getXPonto(pontoMax) + 50) + b;
		if(distanciaL2(xc, yc, xq, yc + 50) > distanciaL2(xc, yc, getXPonto(pontoMax) + 50, yq)) {
			yq = yc + 50;
		} else {
			xq = getXPonto(pontoMax) + 50;
		}
	} else if(xc > xv && yc > yv) {
		xq = (getYPonto(pontoMin) - 50 - b)/a;
		yq = a*(getXPonto(pontoMin) - 50) + b;
		if(distanciaL2(xc, yc, xq, getYPonto(pontoMin) - 50) > distanciaL2(xc, yc, getXPonto(pontoMin) - 50, yq)) {
			yq = getYPonto(pontoMin) - 50;
		} else {
			xq = getXPonto(pontoMin) - 50;
		}
	} else if(xc > xv && yc == yv) { // certo
		xq = getXPonto(pontoMin) - 50;
		yq = yc;
	} else if(xc > xv && yc < yv) {
		xq = (getYPonto(pontoMax) + 50 - b)/a;
		yq = a*(getXPonto(pontoMin) - 50) + b;
		if(distanciaL2(xc, yc, xq, getYPonto(pontoMax) + 50) > distanciaL2(xc, yc, getXPonto(pontoMin) - 50, yq)) {
			yq = getYPonto(pontoMax) + 50;
		} else {
			xq = getXPonto(pontoMin) - 50;
		}
	} else if(xc == xv && yc > yv) { // certo
		xq = xc;
		yq = getYPonto(pontoMin) - 50;
	} else if(xc == xv && yc < yv) { // certo
		xq = xc;
		yq = getYPonto(pontoMax) + 50;
	}

	// ver como vou dar free dps
	Vertice vc = criarVertice(xc, yc, xc, yc);
	Vertice vq = criarVertice(xq, yq, xc, yc);

	return criarSegmento(vc, vq);
}

Ponto buscarPontoInterseccao(Segmento a, Segmento b) {
	// y = ax + b
	// x = (y-b)/a
	Vertice v1a = getV1Segmento(a);
	Vertice v2a = getV2Segmento(a);

	Vertice v1b = getV1Segmento(b);
	Vertice v2b = getV2Segmento(b);
	double x_intersec, y_intersec;
	if(getXVertice(v1a) == getXVertice(v2a)) {

		x_intersec = getXVertice(v1a);
		double a_b = (getYVertice(v1b)-getYVertice(v2b))/(getXVertice(v1b)-getXVertice(v2b));
		double b_b = getYVertice(v1b) - a_b*getXVertice(v1b);
		y_intersec = a_b*x_intersec + b_b;

	} else if(getXVertice(v1b) == getXVertice(v2b)) {

		x_intersec = getXVertice(v1b);
		double a_a = (getYVertice(v1a)-getYVertice(v2a))/(getXVertice(v1a)-getXVertice(v2a));
		double b_a = getYVertice(v1a) - a_a*getXVertice(v1a);
		y_intersec = (a_a*x_intersec) + b_a;

	} else {

		double a_a = (getYVertice(v1a)-getYVertice(v2a))/(getXVertice(v1a)-getXVertice(v2a));
		double b_a = getYVertice(v1a) - a_a*getXVertice(v1a);

		double a_b = (getYVertice(v1b)-getYVertice(v2b))/(getXVertice(v1b)-getXVertice(v2b));
		double b_b = getYVertice(v1b) - a_b*getXVertice(v1b);

		x_intersec = (b_b - b_a)/(a_a - a_b);
		y_intersec = a_a*x_intersec + b_a;
	}

	return criarPonto(x_intersec, y_intersec);
}

double calcularAngulo(Ponto p, double x, double y) {
	double ang = atan2(getYPonto(p) - y, getXPonto(p) - x);
	//if(ang < 0) ang+=2*M_PI;
	return ang;
}

double calcularAngulop(double xp, double yp, double x, double y) {
	double ang = atan2(yp - y, xp - x);
	//if(ang < 0) ang+=2*M_PI;
	return ang;
}

bool verficarViradoAEsquerda(Ponto a, Ponto b, Ponto c) {
	double s = (getXPonto(a)*getYPonto(b) - getYPonto(a)*getXPonto(b) +
					  getYPonto(a)*getXPonto(c) - getXPonto(a)*getYPonto(c) + 
					  getXPonto(b)*getYPonto(c) - getYPonto(b)*getXPonto(c))/2;
	return s <= 0;
}


bool verificarSegmentosInterceptam(Segmento s1, Segmento s2) {

	if(s1 == NULL || s2 == NULL) return false;

	Ponto a = getPVertice(getV1Segmento(s1));
	Ponto b = getPVertice(getV2Segmento(s1));

	Ponto c = getPVertice(getV1Segmento(s2));
	Ponto d = getPVertice(getV2Segmento(s2));

	return (verficarViradoAEsquerda(c, d, a) ^ verficarViradoAEsquerda(c, d, b)) &&
	 		(verficarViradoAEsquerda(a, b, c) ^ verficarViradoAEsquerda(a, b, d));
}

double buscarXInterseccaoSegmento(Segmento s, double y) {
	// y = ax + b
	// x = (y-b)/a
	Vertice v1 = getV1Segmento(s);
	Vertice v2 = getV2Segmento(s);

	double x1 = getXVertice(v1);
	double x2 = getXVertice(v2);
	double y1 = getYVertice(v1);
	double y2 = getYVertice(v2);

	if(x2-x1 == 0) return x1; // reta perpendicular
	double a = (y2-y1)/(x2-x1);
	double b = y1 - a*x1;

	return (y-b)/a;
}