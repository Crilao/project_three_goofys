#include <stdio.h>
#include <stdlib.h>



int main() {
	
	int N, M; //N = linhas e M = colunas nas matrizes
	
	int mat[N][M]; //Matriz que recebe a entrada

	printf("Insira o arquivo de entrada e saida do programa\n");
	//Fazer a leitura do arquivo, eu nao sei como faz

	//----------------area de teste dos arquivos-----------------//
	// -------------------CUIDADO---PERIGO-----------------------//
	/*
	int arq; //eh a variavel que vai trazer os numeros lidos do arquivo para a matriz
	FILE *arq_entrada;
	arq_entrada = fopen("matriz.dat", "r");
	
	
		}
	}
	*/
	//-----------------------------------------------------------//
	
	int contn, contm; //Sao os auxiliares contadores de linha e coluna da matriz

	int matInv[N][M]; //Eh a matriz invertida
	
	for(contn = 0; contn < N; contn++) {
		
		for(contm = 0; contm < M; contm++) {

			matInv[contn][contm] = mat[M-contm-1][contn];
		}
	}
	for(contn = 0; contn < N; contn++) {
		
		for(contm = 0; contm < M; contm++) {

			printf("%d ", matInv[contn][contm]);

		}
		printf("\n");
	}




	return 0;
}
