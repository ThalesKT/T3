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