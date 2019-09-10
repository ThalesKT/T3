#ifndef _parametro_h
#define _parametro_h

//Esta função recebe os arquivos que serão utilizados para leitura,escrita
void trataParametro(int argc, char *argv[], char **pesquisageo, char **pesquisaconsulta,char **saidageosvg,
char **saidaconsultatxt, char **saidaconsultasvg, char **boundingbox);

//insere barra no diretório caso não tenha, se tiver mantém como está
void trataBarra(char *diretorio);

//junta primeiro e segundo parametro no terceiro
void uneDiretorioArquivo(char *diretorio, char *arquivo ,char *saida);

//retira o ultimo ponto, a extensão. Por exemplo teste.svg --> retorna teste
void tiraPonto(char *ponto);

//retira a primeira barra para que mantenha um padrao na hora de concatenar
void trataPrimeiraBarra(char *palavra);

//tira a ultima barra e deixa conteudo apos a barra. Por exemplo ~/Documents/siguel ->> retorna siguel
char* separaArquivo(char *ponto);

#endif 
