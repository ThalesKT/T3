COMPILADOR = gcc 
FLAGS_COMPILADOR = -std=c99 -g
FLAGS_LIGADOR = -lm 
NOME_OBJ = siguel
OBJETOS = arquivoGeo/arquivoGeo.o Calculos/calculos.o Circulo/circulo.o Colisao/colisao.o Hidrante/hidrante.o listaEstatica/listaEstatica.o Parametros/parametro.o Parametros/parametrofunc.o Quadra/quadra.o Retangulo/retangulo.o Semaforo/semaforo.o RadioBase/radioBase.o ArquivoQry/arquivoQry.o ArquivoQry/svgQry.o ArquivoQry/auxQry.o Predio/predio.o Muro/muro.o Ponto/ponto.o ArquivoQry/sort.o main.o

siguel: $(OBJETOS)
	$(COMPILADOR) $(OBJETOS) $(FLAGS_COMPILADOR) $(FLAGS_LIGADOR) -o $(NOME_OBJ)

all: $(OBJETOS)
	$(COMPILADOR) $(OBJETOS) $(FLAGS_COMPILADOR) $(FLAGS_LIGADOR) -o $(NOME_OBJ)

clean:
	find . -name \*.o -type f -delete
