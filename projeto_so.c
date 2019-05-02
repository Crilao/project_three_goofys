#include <stdio.h>
#include <stdlib.h>



int main() {
	
	int N, M; //N eh o numero de linhas e M eh o numero de colunas da matriz
	

	printf("Insira o numero de linhas e de colunas da matriz, respectivamente\n");
	scanf("%d %d", &N, &M);
	
	int mat[N][M];

	printf("Insira os arquivos de entrada e saida do programa\n");
	//Fazer a leitura do arquivo, eu nao sei como faz

	//----------------area de teste dos arquivos-----------------//
	// -------------------CUIDADO---PERIGO-----------------------//
	/*
	int arq; //eh a variavel que vai trazer os numeros lidos do arquivo para a matriz
	FILE *arq_entrada;
	arq_entrada = fopen("matriz.dat", "r");

	for(contn = 0; contn < N; contn++) {
		
		for(contm = 0; contm < M; contm++) {
			
			if (arq != EOF)
				arq = mat[N][M];
			else
				break;
		}
	}


	*/
	//-----------------------------------------------------------//
	
	int contn, contm; //Sao os auxiliares contadores de linha e coluna da matriz

	for(contn = 0; contn < N; contn++) {
		
		for(contm = 0; contm < M; contm++) {

			mat[contn][contm] = mat[M-contm][contn];
		}
	}
	for(contn = 0; contn < N; contn++) {
		
		for(contm = 0; contm < M; contm++) {

			printf("%d\n", mat[contn][contm]);

		}
	}




	return 0;
}
