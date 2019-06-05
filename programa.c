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
	int id;//numero da thread
	int N; //numero de linhas
	int M; //numero de colunas
	int linhaStart; //posição inicial da linha
	int colunaStart;//posição inicial da coluna
	int leituras;	//numero de elementos que cada thread le
	double **m;	//matriz original
	double **minv;	//matriz rotacionada
	FILE *fw;	//cria o arquivo de saida
}INFO;

INFO information[16];

void *inverte(void *arg){ //funçao que rotaciona com o uso das threads
	INFO *information = (INFO*)arg;
	int cont = 0; //inicializa o contador de leituras
	int contm = information->colunaStart;//o contador de colunas inicial na posicao inicial de leitura da thread
	for(int contn = information->linhaStart; contn < information->N; contn++) {
		for(contm; contm < information->M; contm++) {
			if(information->N!=information->M){ //caso a matriz nao seja quadrada
				information->minv[contm][contn] = information->m[information->N-contn-1][contm];//rotaciona os elementos da matriz
				cont++;
				if(cont==information->leituras) break;//a thread para de ler quando o contador de leituras alcançar o valor requerido
			}
			else {//caso a matriz seja quadrada

				information->minv[contn][contm] = information->m[information->N-contm-1][contn];//rotaciona os elementos da matriz
				cont++;
				if(cont==information->leituras) break;//a thread para de ler quando o contador de leituras alcançar o valor requerido
			}
			
		}
		
		contm = 0;//a partir da segunda passagem, o contador de colunas é zerado para continuar a leitura
		if(cont==information->leituras) break;//a thread para de ler quando o contador de leituras alcançar o valor requerido
	}
	
}

int main(int argc, char *argv[]) {

	FILE *fr;
	int N = atoi(argv[1]);//recebe do terminal o numero de linhas
	int M = atoi(argv[2]);//recebe do terminal o numero de colunas
	int T = atoi(argv[3]);//recebe do terminal o numero de threads                                                                  
	
	fr = fopen(argv[4], "r");//recebe do terminal o arquivo de entrada
	
	if (fr == NULL){
		printf("Erro de abertura\n");
	}
	


	if(T!=2){
		if(T!=4){
			if(T!=8){
				if(T!=16){
					printf("O programa trabalha apenas com 2, 4, 8 ou 16 threads\n");
					return 0;
				}
			}
		}
	}



	clock_t tI; //marcador de tempo inicial
	clock_t tF;//marcador de tempo final
	double tExec;//tempo de execucao

	int i,j;
	int Linhas=N;
	int Colunas=M;

	//aloca a matriz original
	double **m = (double**)malloc(Linhas * sizeof(double*));   
	for (i = 0; i < Linhas; i++){ 
		m[i] = (double*) malloc(Colunas * sizeof(double));  
		for (j = 0; j < Colunas; j++){ 
			fscanf(fr,"%lf",&m[i][j]);
		}
	}


	//aloca a matriz rotacionada
	double **minv = (double**)malloc(Colunas * sizeof(double*)); 
	for (i = 0; i < Colunas; i++){ 
		minv[i] = (double*) malloc(Linhas * sizeof(double));
	}
	
	//declaracao das threads
	pthread_t id_threads[T]; 

	//criação das threads
	int leitura, sobra;
	leitura=N*M/T;//calcula o valor da leitura
	sobra=N*M%T;//calcula o valor da sobra, ou seja, o resto do numero de elementos
	tI = clock();//marca o tempo inicial
	for(i=0;i<T;i++){//define os valores dos dados de cada thread
		information[i].id = i; //para saber qual thread ela é

		information[i].leituras = leitura;//recebe o valor de elementos que precisa ler
		if(i==T-1){
			information[i].leituras += sobra;//adiciona o valor de sobra na ultima thread
		}
		information[i].linhaStart = ((N*M/T)*i)/M;//calcula em que linha a thread começa a ler
		information[i].colunaStart = ((N*M/T)*i)%M;//calcula em que linha a thread começa a ler
		information[i].N = Linhas;
		information[i].M = Colunas;
		information[i].m = m;
		information[i].minv = minv;
		information[i].fw = fopen(argv[5], "w");
		pthread_create(&id_threads[i],NULL,inverte,(void *)&information[i]);
	}
	

	for(i=0;i<T;i++){
		pthread_join(id_threads[i], NULL);
	}
	tF = clock();//marca o tempo final

	//escreve a matriz rotacionada no arquivo
	for(int contn = 0; contn < information->M; contn++) {
		for(int contm = 0; contm < information->N; contm++) {
			fprintf(information->fw,"%lf\t", minv [contn][contm]);		
		}
		fprintf(information->fw,"\n");
	}
	
	tExec = (tF - tI) * 1000.0 / CLOCKS_PER_SEC; //calcula o tempo de execuçao
	
	printf("Tempo: %lf\n", tExec);

	return 0;
}
