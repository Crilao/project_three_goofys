#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

double** alocarMatriz(int N,int M){ //Recebe a quantidade de Linhas e Colunas como Parâmetro

	int contn, contm;

	double **matriz = (double**)malloc(N * sizeof(double*)); //Aloca um Vetor de Ponteiros
	 
  	for (contn = 0; contn < N; contn++){ //Percorre as linhas do Vetor de Ponteiros
       		matriz[contn] = (double*) malloc(M * sizeof(double)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		for (contm = 0; contm < M; contm++){ //Percorre o Vetor de Inteiros atual.
	   	 	matriz[contn][contm] = 0; //Inicializa com 0.
       		}
	}
	return matriz;
}


typedef struct descricao{
	int num_linhas;
	int num_colunas;
	int threads;
	int meu_id;

}desc;


void *inv (void *arg){
	desc *argumento = arg;

	printf("Meu id é: %d\n", argumento->meu_id);

}

int main(int argc, char *argv[]) {
	
	FILE *fr, *fw;//Criação dos arquivos de entrada/saída
	
	int N, M, T;//N=Linha; M=Coluna; T=nºThreads

	int contn, contm;

	double **matriz = alocarMatriz(N,M);

	double matInv[M][N]; //Matriz invertida
	
	N = atoi(argv[1]);
	M = atoi(argv[2]);
	T = atoi(argv[3]);
	pthread_t id_threads[T];

	fr = fopen(argv[4], "r");//Abre arquivo de leitura
	if (fr == NULL){
		printf("Erro de abertura\n");
	}
	//==========Leitura da Matriz============================
	for(contn = 0 ; contn < N ; contn++){
	 	
		for(contm = 0 ; contm < M ; contm++) {
               		fscanf(fr,"%lf", &matriz[contn][contm]);
			printf("%lf\t", matriz[contn][contm]);
      		}
  	 printf("\n");
  	}
	fclose(fr);
	//=======================================================
	fw = fopen(argv[5], "w");//Abre arquivo para escrita




	//==========Invertendo a Matriz==========================
	for(contn = 0; contn < M; contn++) {
		for(contm = 0; contm < N; contm++) {
			matInv[contn][contm] = matriz[N-contm-1][contn];
		}
	}
	desc argumento[T];

	for(int i=0;i<T;i++){
		argumento[i].num_linhas = N;
		argumento[i].num_colunas = M;
                argumento[i].threads = T;
		argumento[i].meu_id = i;
		pthread_create(&id_threads[i],NULL,inv,(void *)&argumento[i]);
	}

	for(int i=0;i<T;i++){
		pthread_join(id_threads[i],NULL);
	}

	//=======================================================




	//==========Imprimindo a Matriz invertida================
	for(contn = 0; contn < M; contn++) {
		for(contm = 0; contm < N; contm++) {
			fprintf(fw,"%lf\t", matInv[contn][contm]);
		}
		fprintf(fw,"\n");
	}
	fclose(fw);
	//=======================================================
	free(matriz);
	return 0;

	/*
	Todos os direitos autorais para Cristiano Furlan e Igor Gouvea
	*/

}
