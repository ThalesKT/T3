#include "arquivoQry.h"

void arquivoQry(char *pesquisageo, char *pesquisaconsulta,
char *saidaconsultatxt, char *saidaconsultasvg, char *boundingbox,
Lista listaFormas, Lista listaQuadras, Lista listaHidrantes, Lista listaSemaforo,
Lista listaRadioBase, FILE *consultaSVG) {
    FILE *arquivoTXT;
    FILE *consulta;
    arquivoTXT = fopen(saidaconsultatxt, "w");
    consulta = fopen(pesquisaconsulta, "r");
    char linha[100], instrucao[15];
    int test=0;
    while(true) {

        fgets(linha, 99, consulta);
        sscanf(linha, "%s", instrucao);
		if(feof(consulta))
			break;

        printf("qnts vezes %d\n", test);
        if(strcmp(instrucao, "o?") == 0) {
            char id1[15], id2[15], tipo1[15], tipo2[15];
            sscanf(linha, "%*s %s %s", id1, id2);

            Elemento elemento1 = getElementoeTipo(listaFormas, tipo1, id1);
            Elemento elemento2 = getElementoeTipo(listaFormas, tipo2, id2);

            if(elemento1 == NULL || elemento2 == NULL) {
                printf("ID %s/%s não encontrado.\n", id1, id2);
                continue;
            }

            if(elementosColidem(elemento1, elemento2, tipo1, tipo2)) {
                fprintf(arquivoTXT,"%s %s %s SIM\n", instrucao, id1, id2);
                escreverRetanguloQRY(consultaSVG, elemento1, elemento2, true, tipo1, tipo2);
            } else {
                fprintf(arquivoTXT,"%s %s %s NAO\n", instrucao,id1, id2);
                escreverRetanguloQRY(consultaSVG, elemento1, elemento2, true, tipo1, tipo2);
            }

        } else if(strcmp(instrucao, "i?") == 0) {
            char id1[15], tipo1[15];
            double x,y;
            sscanf(linha, "%*s %s %lf %lf", id1, &x, &y);

            Elemento elemento = getElementoeTipo(listaFormas, tipo1, id1);
            if(elemento == NULL) {
                printf("ID %s não encontrado.\n",id1);
                continue;
            }

            if(pontoInterno(x, y, elemento, tipo1)) {
                fprintf(arquivoTXT,"%s %s %lf %lf INTERNO \n", instrucao, id1, x, y);
                escreverPontoInternoQRY(consultaSVG, elemento, x, y, true, tipo1);
            } else {
                fprintf(arquivoTXT,"%s %s %lf %lf NAO INTERNO \n", instrucao, id1, x, y);
                escreverPontoInternoQRY(consultaSVG, elemento, x, y, false, tipo1);
            }

        } else if(strcmp(instrucao, "d?") == 0) {
            char id1[15], id2[15], tipo1[15], tipo2[15];
            double distancia;
            sscanf(linha, "%*s %s %s", id1, id2);

            Elemento elemento1 = getElementoeTipo(listaFormas, tipo1, id1);
            Elemento elemento2 = getElementoeTipo(listaFormas, tipo2, id2);

            if(elemento1 == NULL || elemento2 == NULL) {
                printf("ID %s/%s não encontrado.\n",id1, id2);
                continue;
            }
            
            distancia = distanciaL2Centro(elemento1, elemento2, tipo1, tipo2);
            fprintf(arquivoTXT,"%s %s %s DISTANCIA: %lf \n", instrucao, id1, id2, distancia);
            escreverRetaQRY(consultaSVG, elemento1, elemento2, tipo1, tipo2);
            escreverDistanciaPMassaQRY(consultaSVG, elemento1, elemento2, distancia, tipo1, tipo2);
            

        } else if(strcmp(instrucao, "bb") == 0) {
            //FAZER BOUNDING BOX
            continue;
        } else if(strcmp(instrucao, "dq") == 0) {
            char metrica[15], id1[35];
            double distancia, px, py;
            sscanf(linha, "%*s %s %s %lf", metrica, id1, &distancia);

            Hidrante h;
            radioBase rb;
            Semaforo s;

            if((h = getElementoLista(listaHidrantes, id1, compararIDHidrante)) != NULL) {
                px = getXHidrante(h);
                py = getYHidrante(h);

                Circulo c = criarCirculo("dq", 7, px, py, "yellow", "blue", "3px");
                escreverCirculoSVG(c, consultaSVG);
                desalocarCirculo(c);

                Circulo c1 = criarCirculo("dq", 9, px, py, "yellow", "blue", "3px");
                escreverCirculoSVG(c1, consultaSVG);
                desalocarCirculo(c1);
                fprintf(arquivoTXT, "Equipamento BASE: HIDRANTE\nID HIDRANTE:%s", id1);
                removerQuadrasDQ(listaQuadras, px, py, distancia, metrica, arquivoTXT);

            } else if( (rb = getElementoLista(listaRadioBase, id1, compararIDRadioBase)) != NULL) {
                px = getXRadioBase(rb);
                py = getYRadioBase(rb);

                Circulo c = criarCirculo("dq", 7, px, py, "yellow", "blue", "3px");
                escreverCirculoSVG(c, consultaSVG);
                desalocarCirculo(c);

                Circulo c1 = criarCirculo("dq", 9, px, py, "yellow", "blue", "3px");
                escreverCirculoSVG(c1, consultaSVG);
                desalocarCirculo(c1);

                fprintf(arquivoTXT, "Equipamento BASE: TORRE\nID TORRE:%s", id1);
                removerQuadrasDQ(listaQuadras, px, py, distancia, metrica, arquivoTXT);
                
            } else if( (s = getElementoLista(listaSemaforo, id1, compararIDSemaforo)) != NULL) {
                px = getXSemaforo(s);
                py = getYSemaforo(s);

                Circulo c = criarCirculo("dq", 7, px, py, "yellow", "blue", "3px");
                escreverCirculoSVG(c, consultaSVG);
                desalocarCirculo(c);

                Circulo c1 = criarCirculo("dq", 9, px, py, "yellow", "blue", "3px");
                escreverCirculoSVG(c1, consultaSVG);
                desalocarCirculo(c1);
                
                fprintf(arquivoTXT, "Equipamento BASE: SEMAFORO\nID SEMAFORO:%s", id1);
                removerQuadrasDQ(listaQuadras, px, py, distancia, metrica, arquivoTXT);
            } else {
                fprintf(arquivoTXT,"Elemento com ID %s não encontrado.\n", id1);
            }
            

        } else if(strcmp(instrucao, "del") == 0) {
            char id1[20];
            sscanf(linha, "%*s %s", id1);
            printf("ID> %s\n", id1);
            Quadra q;
            Hidrante h;
            radioBase rb;
            Semaforo s;

            if( (q = getElementoLista(listaQuadras, id1, compararIDQuadra)) != NULL) {
                fprintf(arquivoTXT, "Quadra removida. CEP: %s Localizacao: %.2lf %.2lf\n",
                id1, getXQuadra(q), getYQuadra(q));
                excluirElementoLista(listaQuadras, id1, compararIDQuadra, desalocarQuadra);

            } else if( (h = getElementoLista(listaHidrantes, id1, compararIDHidrante)) != NULL) {
                fprintf(arquivoTXT, "Hidrante removido. ID: %s Localizacao: %.2lf %.2lf\n",
                id1, getXHidrante(h), getYHidrante(h));
                excluirElementoLista(listaHidrantes, id1, compararIDHidrante, desalocarHidrante);

            } else if( (rb = getElementoLista(listaRadioBase, id1, compararIDRadioBase)) != NULL) {
                fprintf(arquivoTXT, "Torre removida. ID: %s Localizacao: %.2lf %.2lf\n",
                id1, getXRadioBase(h), getYRadioBase(h));
                excluirElementoLista(listaRadioBase, id1, compararIDRadioBase, desalocarRadioBase);

            } else if( (s = getElementoLista(listaSemaforo, id1, compararIDSemaforo)) != NULL) {
                fprintf(arquivoTXT, "Semaforo removido. ID: %s Localizacao: %.2lf %.2lf\n",
                id1, getXSemaforo(h), getYSemaforo(h));
                excluirElementoLista(listaSemaforo, id1, compararIDSemaforo, desalocarSemaforo);
                
            } else {
                fprintf(arquivoTXT, "ID/CEP %s não encontrado.\n", id1);
            }
        }
        test++;
    }

}
