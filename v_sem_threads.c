#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[]) {
	
	FILE *fr, *fw;
	
	int N, M, T;
	int contn, contm;
	
	int matriz[1000][1000];
	



	N = atoi(argv[1]);
	M = atoi(argv[2]);
	T = atoi(argv[3]);

	
	fr = fopen(argv[4], "r");
	if (fr == NULL){
		printf("Erro de abertura\n");
	}
	


	for(contn = 0 ; contn < N ; contn++){
	 	
		for(contm = 0 ; contm < M ; contm++) {
            
               		fscanf(fr,"%d",&matriz[contn][contm]);
			printf("%d\t", matriz[contn][contm]);
      		}
   printf("\n");
  	}
	fclose(fr);
	


	fw = fopen(argv[5], "w");

	

	int matInv[M][N]; //Eh a matriz invertida
	
	for(contn = 0; contn < M; contn++) {
		
		for(contm = 0; contm < N; contm++) {

			matInv[contn][contm] = matriz[N-contm-1][contn];
		}
	}
	for(contn = 0; contn < M; contn++) {
		
		for(contm = 0; contm < N; contm++) {

			fprintf(fw,"%d\t", matInv[contn][contm]);

		}
		fprintf(fw,"\n");
	}
	fclose(fw);



	return 0;
}
