#include "svgQry.h"

void escreverRetanguloQRY(FILE *svgQRY, Elemento elemento1, Elemento elemento2, bool colidem,
char *tipo1, char *tipo2) {
	double xMin, xMax, yMin, yMax, largura, altura;
	if(strcmp(tipo1,"c") == 0 && strcmp(tipo2,"r") == 0) {
        
		xMin = getMinimoXCirculo(elemento1) < getXRetangulo(elemento2) ? getMinimoXCirculo(elemento1) : getXRetangulo(elemento2);
		xMax = getMaximoXCirculo(elemento1) > getMaximoXRetangulo(elemento2) ? getMaximoXCirculo(elemento1) : getMaximoXRetangulo(elemento2);
		yMin = getMinimoYCirculo(elemento1) < getYRetangulo(elemento2) ? getMinimoYCirculo(elemento1) : getYRetangulo(elemento2);
		yMax = getMaximoYCirculo(elemento1) > getMaximoYRetangulo(elemento2) ? getMaximoYCirculo(elemento1) : getMaximoYRetangulo(elemento2);

	} else if(strcmp(tipo1,"r") == 0 && strcmp(tipo2,"c") == 0) {

		xMin = getMinimoXCirculo(elemento2) < getXRetangulo(elemento1) ? getMinimoXCirculo(elemento2) : getXRetangulo(elemento1);
		xMax = getMaximoXCirculo(elemento2) > getMaximoXRetangulo(elemento1) ? getMaximoXCirculo(elemento2) : getMaximoXRetangulo(elemento1);
		yMin = getMinimoYCirculo(elemento2) < getYRetangulo(elemento1) ? getMinimoYCirculo(elemento2) : getYRetangulo(elemento1);
		yMax = getMaximoYCirculo(elemento2) > getMaximoYRetangulo(elemento1) ? getMaximoYCirculo(elemento2) : getMaximoYRetangulo(elemento1);

	} else if(strcmp(tipo1,"r") == 0 && strcmp(tipo2,"r") == 0) {

		xMin = getXRetangulo(elemento1) < getXRetangulo(elemento2) ? getXRetangulo(elemento1) : getXRetangulo(elemento2);
		xMax = getMaximoXRetangulo(elemento1) > getMaximoXRetangulo(elemento2) ? getMaximoXRetangulo(elemento1) : getMaximoXRetangulo(elemento2);
		yMin = getYRetangulo(elemento1) < getYRetangulo(elemento2) ? getYRetangulo(elemento1) : getYRetangulo(elemento2);
		yMax = getMaximoYRetangulo(elemento1) > getMaximoYRetangulo(elemento2) ? getMaximoYRetangulo(elemento1) : getMaximoYRetangulo(elemento2);

	} else if(strcmp(tipo1,"c") == 0 && strcmp(tipo2,"c") == 0) {
		xMin = getMinimoXCirculo(elemento1) < getMinimoXCirculo(elemento2) ? getMinimoXCirculo(elemento1) : getMinimoXCirculo(elemento2);
		xMax = getMaximoXCirculo(elemento1) > getMaximoXCirculo(elemento2) ? getMaximoXCirculo(elemento1) : getMaximoXCirculo(elemento2);
		yMin = getMinimoYCirculo(elemento1) < getMinimoYCirculo(elemento2) ? getMinimoYCirculo(elemento1) : getMinimoYCirculo(elemento2);
		yMax = getMaximoYCirculo(elemento1) > getMaximoYCirculo(elemento2) ? getMaximoYCirculo(elemento1) : getMaximoYCirculo(elemento2);

	}
	
	largura = xMax-xMin;
	altura = yMax-yMin;

	if(colidem)
		fprintf(svgQRY, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill-opacity=\"0\" />\n", xMin, yMin, largura, altura);
	else
		fprintf(svgQRY, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"red\" fill-opacity=\"0\" stroke-dasharray=\"5\" />\n", xMin, yMin, largura, altura);
	
}



void escreverPontoInternoQRY(FILE *consultaSVG, Elemento elemento1,
 double x, double y, bool interno, char *tipo1) {
	double *centro = malloc(2*sizeof(double));
	centroDeMassa(elemento1, tipo1 ,centro);

	if(interno) {
		fprintf(consultaSVG, "<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"green\" fill=\"green\" />\n", x, y);
		fprintf(consultaSVG, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"green\" />\n", centro[0], centro[1], x, y);
	} else {
		fprintf(consultaSVG, "<circle cx=\"%lf\" cy=\"%lf\" r=\"1\" stroke=\"red\" fill=\"red\" />\n", x, y);
		fprintf(consultaSVG, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" />\n", centro[0], centro[1], x, y);
	}
	
	free(centro);
}


void escreverRetaQRY(FILE *consultaSVG, Elemento elemento1, Elemento elemento2,
char *tipo1, char *tipo2) {
	double *centro1 = malloc(2*sizeof(double));
	double *centro2 = malloc(2*sizeof(double));
	centroDeMassa(elemento1, tipo1, centro1);
	centroDeMassa(elemento2, tipo2, centro2);
	fprintf(consultaSVG, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" />\n", centro1[0], centro1[1], centro2[0], centro2[1]);

	free(centro1);
	free(centro2);
}

void escreverDistanciaPMassaQRY(FILE *consultaSVG, Elemento elemento1, Elemento elemento2, double distancia,
char *tipo1, char *tipo2) {
	double *centro1 = malloc(2*sizeof(double));
	double *centro2 = malloc(2*sizeof(double));
	centroDeMassa(elemento1, tipo1, centro1);
	centroDeMassa(elemento2, tipo2, centro2);

	double posX = (centro1[0] + centro2[0])/2;
	double posY = (centro1[1] + centro2[1])/2;
	fprintf(consultaSVG, "<text x=\"%lf\" y=\"%lf\">%lf</text>\n", posX, posY, distancia);

	free(centro1);
	free(centro2);
}

void escreverElipseBB(double x, double y, double raiox, double raioy, FILE *boundingbox, char*cor) {

    fprintf(boundingbox,"<ellipse cx=\"%lf\" cy=\"%lf\" rx=\"%lf\" ry=\"%lf\" stroke=\"%s\" fill-opacity=\"0\" /> \n",x, y, raiox, raioy,cor);

}

void escreverRetanguloBB(double largura, double altura, double x, double y, FILE *boundingbox, char *cor){

    fprintf(boundingbox,"<rect width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill-opacity=\"0\" /> \n",largura, altura, x, y, cor);

}

void escreverBombaRL(FILE *SVG, double x, double y) {
	fprintf(SVG, "<path stroke=\"orange\" stroke-width=\"5\" transform=\"translate(%lf %lf) scale(0.03 0.03)\" d=\"M440.5 88.5l-52 52L415 167c9.4 9.4 9.4 24.6 0 33.9l-17.4 17.4c11.8 26.1 18.4 55.1 "
        "18.4 85.6 0 114.9-93.1 208-208 208S0 418.9 0 304 93.1 96 208 96c30.5 0 59.5 6.6 85.6 18.4L311 97c9.4-9.4 "
        "24.6-9.4 33.9 0l26.5 26.5 52-52 17.1 17zM500 60h-24c-6.6 0-12 5.4-12 12s5.4 12 12 12h24c6.6 0 12-5.4 "
        "12-12s-5.4-12-12-12zM440 0c-6.6 0-12 5.4-12 12v24c0 6.6 5.4 12 12 12s12-5.4 12-12V12c0-6.6-5.4-12-12-12zm33.9 "
        "55l17-17c4.7-4.7 4.7-12.3 0-17-4.7-4.7-12.3-4.7-17 0l-17 17c-4.7 4.7-4.7 12.3 0 17 4.8 4.7 12.4 4.7 17 0zm-67.8 "
        "0c4.7 4.7 12.3 4.7 17 0 4.7-4.7 4.7-12.3 0-17l-17-17c-4.7-4.7-12.3-4.7-17 0-4.7 4.7-4.7 12.3 0 17l17 17zm67.8 "
        "34c-4.7-4.7-12.3-4.7-17 0-4.7 4.7-4.7 12.3 0 17l17 17c4.7 4.7 12.3 4.7 17 0 4.7-4.7 4.7-12.3 0-17l-17-17zM112 "
        "272c0-35.3 28.7-64 64-64 8.8 0 16-7.2 16-16s-7.2-16-16-16c-52.9 0-96 43.1-96 96 0 8.8 7.2 16 16 16s16-7.2 16-16z\"/>",
        x - 6.5, y - 8.5);
}


void escreverTrianguloBRL(FILE *SVG, double x1, double y1, Vertice v2, Vertice v3) {
	//double x1 = Vertice_get_x(v1), y1 = Vertice_get_y(v1);
	double x2 = getXVertice(v2), y2 = getYVertice(v2);
	double x3 = getXVertice(v3), y3 = getYVertice(v3);
	fprintf(SVG, "<polygon points=\"%lf,%lf %lf,%lf %lf,%lf\" style=\"fill: orange; opacity: 0.5\"/>\n", x1, y1, x2, y2, x3, y3);
}
