#include "arquivoGeo.h"

void arquivoGeo(char *pesquisageo, char *pesquisaconsulta,char *saidageosvg,
char *saidaconsultatxt, char *saidaconsultasvg, char *boundingbox) {
    
    char tipoElemento[5], linhaGeo[150], id[150];
    char corBorda[35], corDentro[35];
    double x,y, altura, largura, raio;

    char espessuraBordaCirculo[15] = "2px", espessuraBordaRetangulo[15] = "2px",
    espessuraBordaQuadra[15] = "2px", espessuraBordaHidrante[15] = "2px",
    espessuraBordaSemaforo[15] = "2px", espessuraBordaRadioBase[15] = "2px";

    char corDentroQuadra[35] = "orange", corDentroHidrante[35] = "red",
    corDentroSemaforo[35] = "yellow", corDentroRadioBase[35] = "grey";

    char corBordaQuadra[35] = "black", corBordaHidrante[35] = "black",
    corBordaSemaforo[35] = "black", corBordaRadioBase[35] = "black";

    Lista listaFormas;
    Lista listaQuadras;
    Lista listaHidrantes;
    Lista listaSemaforo;
    Lista listaRadioBase;
    Lista listaPredios;
    Lista listaMuros;

    FILE *geo;
    geo = fopen(pesquisageo, "r");
    FILE *consultaSVG;
    FILE *saidaGeoSVG;
    saidaGeoSVG = fopen(saidageosvg, "w");
    fprintf(saidaGeoSVG,"<svg> \n");
    if(pesquisaconsulta != NULL) {
        printf("Haverá uma saida svg/txt referente ao arquivo de pesquisa. \n");        
        consultaSVG = fopen(saidaconsultasvg, "w");
        fprintf(consultaSVG,"<svg> \n");
    } else {
        printf("Não há arquivo de consulta!\n");
    }
  
    int numeroFormas, numeroQuadras, numeroHidrantes, numeroSemaforos, numeroRadioBase, numeroPredios, numeroMuros;
    fgets(linhaGeo, 149, geo);
    sscanf(linhaGeo,"%s", tipoElemento);
    if(strcmp(tipoElemento, "nx") == 0) {           
        sscanf(linhaGeo,"%*s %d %d %d %d %d %d %d",&numeroFormas, &numeroQuadras, &numeroHidrantes,
        &numeroSemaforos, &numeroRadioBase, &numeroPredios, &numeroMuros);
        listaFormas = inicializarLista(numeroFormas);
        listaQuadras = inicializarLista(numeroQuadras);
        listaHidrantes = inicializarLista(numeroHidrantes);
        listaSemaforo = inicializarLista(numeroSemaforos);
        listaRadioBase = inicializarLista(numeroRadioBase);
        listaPredios = inicializarLista(numeroPredios);
        listaMuros = inicializarLista(numeroMuros);

    } else {
        listaFormas = inicializarLista(1000);
        listaQuadras = inicializarLista(1000);
        listaHidrantes = inicializarLista(1000);
        listaSemaforo = inicializarLista(1000);
        listaRadioBase = inicializarLista(1000);
        listaPredios = inicializarLista(1000);
        listaMuros = inicializarLista(1000);
        rewind(geo);
    }
    

    
    while(true) {
        fscanf(geo,"%s",tipoElemento);
        if(feof(geo)) {
            break;
        }        

        if(strcmp(tipoElemento, "c") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo,"%s %lf %lf %lf %s %s", id, &raio, &x, &y, corBorda, corDentro);
            Circulo c = criarCirculo(id, raio, x, y, corBorda, corDentro, espessuraBordaCirculo);
            inserirFinalLista(listaFormas, c, "c", id);
            escreverCirculoSVG(c, saidaGeoSVG);
            if(pesquisaconsulta != NULL) {
                //printf("interrompido \n");
                escreverCirculoSVG(c, consultaSVG);
            }
            
            
        } else if(strcmp(tipoElemento, "r") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo,"%s %lf %lf %lf %lf %s %s", id, &largura, &altura, &x, &y, corBorda, corDentro);
            Retangulo r = criarRetangulo(id, altura, largura, x, y, corBorda, corDentro, espessuraBordaRetangulo);
            inserirFinalLista(listaFormas, r, "r", id);
            escreverRetanguloSVG(r, saidaGeoSVG);
            if(pesquisaconsulta != NULL) {
               escreverRetanguloSVG(r, consultaSVG);
            }

        } else if(strcmp(tipoElemento, "t") == 0) {
            char texto[200];
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo, "%lf %lf %s", &x, &y, texto);
            continue;
            //inserrir para escrever no svg
        } else if(strcmp(tipoElemento, "q") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo, "%s %lf %lf %lf %lf", id, &x, &y, &largura, &altura);
            Quadra q = criarQuadra(id, x, y, altura, largura, corBordaQuadra, corDentroQuadra, espessuraBordaQuadra);
            inserirFinalLista(listaQuadras, q, "q", id);
            
        } else if(strcmp(tipoElemento, "h") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo, "%s %lf %lf", id, &x, &y);
            Hidrante h = criarHidrante(id, x, y, corBordaHidrante, corDentroHidrante, espessuraBordaHidrante);
            inserirFinalLista(listaHidrantes, h, "h", id);
            
        } else if(strcmp(tipoElemento, "s") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo, "%s %lf %lf", id, &x, &y);
            Semaforo s = criarSemaforo(id, x, y, corBordaSemaforo, corDentroSemaforo, espessuraBordaSemaforo);
            inserirFinalLista(listaSemaforo, s, "s", id);
            
        } else if(strcmp(tipoElemento, "rb") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo, "%s %lf %lf", id, &x, &y);
            radioBase rb = criarRadioBase(id, x, y, corBordaRadioBase, corDentroRadioBase, espessuraBordaRadioBase);
            inserirFinalLista(listaRadioBase, rb, "rb", id);
            //escrever no .svg
        } else if(strcmp(tipoElemento, "cq") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo, "%s %s %s", corDentroQuadra, corBordaQuadra, espessuraBordaQuadra);

        } else if(strcmp(tipoElemento, "ch") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo, "%s %s %s", corDentroHidrante, corBordaHidrante, espessuraBordaHidrante);

        } else if(strcmp(tipoElemento, "cr") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo, "%s %s %s", corDentroRadioBase, corBordaRadioBase, espessuraBordaRadioBase);

        } else if(strcmp(tipoElemento, "cs") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo, "%s %s %s", corDentroSemaforo, corBordaSemaforo, espessuraBordaSemaforo);

        } else if(strcmp(tipoElemento, "sw") == 0) {
            fgets(linhaGeo, 149, geo);
            sscanf(linhaGeo, "%s %s", espessuraBordaCirculo, espessuraBordaRetangulo);

        } else if(strcmp(tipoElemento, "prd") == 0) {
            char cep[30], face, gambiarra[15];
            double numero, f, profundidade, mrg;
            sscanf(linhaGeo, "%*s %s %c %lf %lf %lf %lf", cep, &face, &numero, &f, &profundidade, &mrg);
            Predio prd = criarPredio(cep, face, numero, f, profundidade, mrg);
            //fprintf(gambiarra, "%c",numero);
            printf("predio criado\n");
            inserirFinalLista(listaPredios, prd, "prd", "gambiarra");

        } else if(strcmp(tipoElemento, "mur") == 0) {
            double x1, y1, x2, y2;

            sscanf(linhaGeo, "%*s %lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            Muro m = criarMuro(x1, y1, x2, y2);
            inserirFinalLista(listaMuros, m, "m", "toatrasado");
        }
    }
    
    escreverListaSVG(listaQuadras, escreverQuadraSVG, saidaGeoSVG);
    escreverListaSVG(listaHidrantes, escreverHidranteSVG, saidaGeoSVG);
    escreverListaSVG(listaSemaforo, escreverSemaforoSVG, saidaGeoSVG);
    escreverListaSVG(listaRadioBase, escreverRadioBaseSVG, saidaGeoSVG);
    int i;
    i = getPrimeiroElementoLista(listaPredios);
    for(i; i!= -1; i = getProximoElemento(listaPredios, i)) {
        char cep[35];
        Predio prd = getElementoListaPosicao(listaPredios, i);
        strcpy(cep, getCepPredio(prd));
        Quadra q;
        printf("entrou aqui \n");
        if( (q = getElementoLista(listaQuadras, cep, compararIDQuadra)) != NULL){
            printf("vamos ver se entrou aqui\n");
            escreverPredioSVG(prd, getXQuadra(q), getYQuadra(q),
             getLarguraQuadra(q), getAlturaQuadra(q), saidaGeoSVG);
        }

           
    }

    i = getPrimeiroElementoLista(listaMuros);
    for(i; i!= -1; i = getProximoElemento(listaMuros, i)) {
        Muro m = getElementoListaPosicao(listaMuros, i);
        escreverMuroSVG(m, saidaGeoSVG);
    }




    fprintf(saidaGeoSVG,"</svg> \n");
    fclose(saidaGeoSVG);
    fclose(geo);
    if(pesquisaconsulta != NULL) {
        printf("Iniciando arquivo .qry \n");
        arquivoQry(pesquisageo, pesquisaconsulta, saidaconsultatxt, saidaconsultasvg, boundingbox,
        listaFormas, listaQuadras, listaHidrantes, listaSemaforo, listaRadioBase, consultaSVG);
        escreverListaSVG(listaQuadras, escreverQuadraSVG, consultaSVG);
        escreverListaSVG(listaHidrantes, escreverHidranteSVG, consultaSVG);
        escreverListaSVG(listaSemaforo, escreverSemaforoSVG, consultaSVG);
        escreverListaSVG(listaRadioBase, escreverRadioBaseSVG, consultaSVG);
        fprintf(consultaSVG,"</svg> \n");
        fclose(consultaSVG);          
    }
    
     
}