#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
pthread_mutex_t mutex;
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

INFO information[16];

void *inverte(void *arg){
	INFO *information = (INFO*)arg;
	pthread_mutex_lock(&mutex);
	
	
	for(int contn = 0; contn < information->M; contn++) {
		for(int contm = information->linhaStart; contm < information->linhaEnd; contm++) {			
			information->minv[contn][contm] = information->m[information->N-contm-1][contn];
			printf("%lf ",information->minv[contn][contm]);	
			
		}
	}
	pthread_mutex_unlock (&mutex);	
		
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
	
	//clock_t tI;
	//clock_t tF;
	//double tExec;
///ALOCA A MATRIZ DINAMICAMENTE

	int i,j;
	int Linhas=N;
	int Colunas=M;

	double **m = (double**)malloc(Linhas * sizeof(double*)); 
	for (i = 0; i < Linhas; i++){ 
		m[i] = (double*) malloc(Colunas * sizeof(double));  
		for (j = 0; j < Colunas; j++){ 
			fscanf(fr,"%lf",&m[i][j]);
		}
	}
	double **minv = (double**)malloc(Colunas * sizeof(double*)); 
	for (i = 0; i < Colunas; i++){ 
		minv[i] = (double*) malloc(Linhas * sizeof(double));
	}


	

pthread_t id_threads[T];

//Criação das threads
	//tI = clock();
	for(i=0;i<T;i++){
		//information[i].colunaStart= (M/T) * i;
		information[i].linhaStart = (N/T) * i;
		if(N%T!=0){
			information[T-1].linhaEnd = (N/T) * (i + 1) + (N%T);
		}
		else{
			information[i].linhaEnd =  (N/T) * (i + 1);
		}
		
		//information[i].colunaEnd = (M/T) * (i + 1)+ (M%T);
		information[i].N = Linhas;
		information[i].M = Colunas;
		information[i].m =m;
		information[i].minv = minv;
		information[i].fw=fopen(argv[5], "w");
		//information[i].qtdElementos=N*M;
		printf("\nThread [%d]\n",i);
		pthread_create(&id_threads[i],NULL,inverte,(void *)&information[i]);
		
	}
	

	for(i=0;i<T;i++){
		pthread_join(id_threads[i], NULL);
	}
	//tempoFinal = clock();

	inverte(information);
	for(int contn = 0; contn < information->M; contn++) {
		for(int contm = 0; contm < information->N; contm++) {
			fprintf(information->fw,"%lf\t", minv[contn][contm]);		
		}
		fprintf(information->fw,"\n");
	}
	
	//tExec = (tF - tI) * 1000.0 / CLOCKS_PER_SEC;
	
	printf("INVERTEU COM SUCESSO, OLHE O ARQUIVO\n");

	return 0;
}




