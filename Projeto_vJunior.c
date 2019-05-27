#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Infos
{
	int N;
	int M;
	FILE *fw;
	FILE *fr;
	double **m;
}INFO, *info;
void inverte(INFO information){

	double matInv[information.M][information.N]; //Eh a mat2 invertida
	for(int contn = 0; contn < information.M; contn++) {
		for(int contm = 0; contm < information.N; contm++) {
			matInv[contn][contm] = information.m[information.N-contm-1][contn];
		}
	}
	for(int contn = 0; contn < information.M; contn++) {
		for(int contm = 0; contm < information.N; contm++) {
			fprintf(information.fw,"%lf\t", matInv[contn][contm]);
		}
		fprintf(information.fw,"\n");
	}
	fclose(information.fw);
}
int main(int argc, char *argv[]) {
	
	FILE *fr;
	INFO information;
	int T;
	int contm,contn;
	
	
	information.N = atoi(argv[1]);
	information.M = atoi(argv[2]);
	T = atoi(argv[3]);

	information.fr = fopen(argv[4], "r");
	information.fw = fopen(argv[5], "w");
if (information.fr == NULL){
		printf("Erro de abertura\n");
}
	

///ALOCA A MATRIZ DINAMICAMENTE

int i,j; //Variaveis Auxiliares
int Linhas = information.N;
int Colunas = information.M;

  double **m = (double**)malloc(Linhas * sizeof(double*)); //Aloca um Vetor de Ponteiros
  for (i = 0; i < Linhas; i++){ //Percorre as linhas do Vetor de Ponteiros
       m[i] = (double*) malloc(Colunas * sizeof(double)); //Aloca um Vetor de Inteiros para cada posiÃ§Ã£o do Vetor de Ponteiros.
       for (j = 0; j < Colunas; j++){ //Percorre o Vetor de Inteiros atual.
     	  fscanf(information.fr,"%lf",&m[i][j]);
       }
  }

  information.m = m;

//ALOCA A MATRIZ DINAMICAMENTE



	fclose(information.fr);
	inverte(information);

	printf("INVERTEU COM SUCESSO, OLHE O ARQUIVO\n");

	return 0;
}
