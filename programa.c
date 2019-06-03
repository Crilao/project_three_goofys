/*Um exemplo do comando para a execução correta do programa é:

./rodaMatriz 4 4 2 entrada.txt saida.txt
- De forma que rodaMatriz é o nome do executavel;
- O primeiro 4 é o número de linhas;
- O segundo 4 é o número de colunas;
- 2 é o número de threads;
- entrada.txt é o arquivo de texto com a matriz original;
- saida.txt é o arquivo de texto que receberá a matriz rotacionada.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
typedef struct Infos
{
	int N; //numero de linhas
	int M; //numero de colunas
	int linhaStart; //posição inicial da linha
	int linhaEnd;	//posição final da linha
	double **m;	//matriz original
	double **minv;	//matriz rotacionada
	FILE *fw;	//cria o arquivo de saida
}INFO;

INFO information[16];

void *inverte(void *arg){ //funçao que rotaciona com o uso das threads
	INFO *information = (INFO*)arg;
	
	
	for(int contn = 0; contn < information->M; contn++) {
		for(int contm = information->linhaStart; contm < information->linhaEnd; contm++) {
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
	
	//clock_t tI;
	//clock_t tF;
	//double tExec;

	int i,j;
	int Linhas=N;
	int Colunas=M;

	//Aloca a matriz original
	double **m = (double**)malloc(Linhas * sizeof(double*));   
	for (i = 0; i < Linhas; i++){ 
		m[i] = (double*) malloc(Colunas * sizeof(double));  
		for (j = 0; j < Colunas; j++){ 
			fscanf(fr,"%lf",&m[i][j]);
		}
	}

	//Aloca a matriz rotacionada
	double **minv = (double**)malloc(Colunas * sizeof(double*)); 
	for (i = 0; i < Colunas; i++){ 
		minv[i] = (double*) malloc(Linhas * sizeof(double));
	}


	
	//declaração das threads
	pthread_t id_threads[T]; 

	//Criação das threads
	//tI = clock();
	for(i=0;i<T;i++){
		information[i].linhaStart = (N/T) * i;
		information[i].linhaEnd = (N/T) * (i + 1) + (N%T);
		information[i].N = Linhas;
		information[i].M = Colunas;
		information[i].m =m;
		information[i].minv = minv;
		information[i].fw=fopen(argv[5], "w");
		pthread_create(&id_threads[i],NULL,inverte,(void *)&information[i]);
	}
	

	for(i=0;i<T;i++){
		pthread_join(id_threads[i], NULL);
	}
	//tempoFinal = clock();


	for(int contn = 0; contn < information->M; contn++) {
		for(int contm = 0; contm < information->N; contm++) {
			fprintf(information->fw,"%lf\t", minv[contn][contm]);		
		}
		fprintf(information->fw,"\n");
	}
	
	//tExec = (tF - tI) * 1000.0 / CLOCKS_PER_SEC;
	

	return 0;
}
