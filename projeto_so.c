#include <stdio.h>
#include <stdlib.h>




int main(int argc, char *argv[]) {
	
	FILE *fr, *fw;
	
	int N, M, T;
	
	int contn, contm;
	
	int matriz [N][M], matInv [N][M];
	
	N = atoi(argv[1]);
	M = atoi(argv[2]);
	T = atoi(argv[3]);

	if (N>1000 || M>1000) {
	
		return 1;
	}


	fr = fopen (argv[4], "r");
	

	
	 for(contn=0;contn<N;contn++){
	 	
            for(contm=0;contm<M;contm++) {
            
                fscanf(fr,"%d",&matriz[contn][contm]);
      		}
            
     }
    
	 for(contn=0;contn<N;contn++){
	 	
            for(contm=0;contm<N;contm++) {
            
                printf("%d", matriz[contn] [contm]);
            }
            
    }


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
