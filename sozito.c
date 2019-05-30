#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
typedef struct Infos
{
	int N;
	int M;
	int linhaStart;
	int colunaStart;
	int linhaEnd;
	int colunaEnd;
	int qtdElementos;
	double **m;
	double **minv;
	FILE *fw;
}INFO;
int contn, contm;


INFO information[16];

void *inverte(void *arg){
INFO *information = arg;






for(int contn = 0; contn < information->M; contn++) {
		for(int contm = 0; contm < information->N; contm++) {
			information->minv[contn][contm] = information->m[information->N-contm-1][contn];
		}
	}
	
}
int main(int argc, char *argv[]) {

	FILE *fr;
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	int T = atoi(argv[3]);
	
	fr = fopen(argv[4], "r");
	
if (fr == NULL){
		printf("Erro de abertura\n");
}
	

///ALOCA A MATRIZ DINAMICAMENTE

int i,j; //Variaveis Auxiliares
int Linhas=N;
int Colunas=M;

  double **m = (double**)malloc(Linhas * sizeof(double*)); //Aloca um Vetor de Ponteiros
  for (i = 0; i < Linhas; i++){ //Percorre as linhas do Vetor de Ponteiros
       m[i] = (double*) malloc(Colunas * sizeof(double)); //Aloca um Vetor de Inteiros para cada 
       for (j = 0; j < Colunas; j++){ //Percorre o Vetor de Inteiros atual.
     	  fscanf(fr,"%lf",&m[i][j]);
		
       }
  }
	 double **minv = (double**)malloc(Colunas * sizeof(double*)); //Aloca um Vetor de Ponteiros
  for (i = 0; i < Colunas; i++){ //Percorre as linhas do Vetor de Ponteiros
       minv[i] = (double*) malloc(Linhas * sizeof(double));
	}
 void pegaLinha (int linha, int coluna, int posicao){
int res=posicao/coluna;

}
void pegaColuna (int linha, int coluna, int posicao){
int res=posicao/linha;



}

	

pthread_t id_threads[T];

//Criação das threads
	for(i=0;i<T;i++){
	int posicaoinicio = (N*M/T) * i;
	int posicaoFinal =  (N*M/T) * (i + 1);
	information[i].N = Linhas;
	information[i].M = Colunas;
	information[i].m =m;
	information[i].minv = minv;

	information[i].fw=fopen(argv[5], "w");
	//N*M%T!=0;
	information[i].qtdElementos=N*M;
	pthread_create(&id_threads[i],NULL,inverte,(void *)&information[i]);
	}
	/*if(i==(T-1)){ 	
		information[i].qtdElementos = (N*M/T)*(N*M%T);
	}
	else
		information[i].qtdElementos = N*M/T;
	pthread_create(&id_threads[i],NULL,inverte,(void *)&information[i]);
	}

	for(i=0;i<T;i++){

	pthread_join(id_threads[i], NULL);
	}*/

	

	
	inverte(information);
	for(int contn = 0; contn < information->M; contn++) {
		for(int contm = 0; contm < information->N; contm++) {
			fprintf(information->fw,"%lf\t", minv[contn][contm]);
					
}
		fprintf(information->fw,"\n");
	}

	printf("INVERTEU COM SUCESSO, OLHE O ARQUIVO\n");

	return 0;
}
