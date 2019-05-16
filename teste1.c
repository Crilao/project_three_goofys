#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
	FILE *fr, *fw;
	int res = 0, n = 0, m = 0, t=0, num=0, x=0, y=0, i=0, matriz [1000][1000], j=0;
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	t = atoi(argv[3]);
	res = n+m;
	printf("exemplo inutil: %d\n", res);
	printf("Numero de threads: %d \n", t);

	fr = fopen (argv[4], "r");
	fscanf(fr,"%d", &num);

	
	 for(i=0;i<n;i++){
            for(j=0;j<m;j++)
                fscanf(fr,"%d",&matriz[i][j]);
            
        }
    
	 for(i=0;i<n;i++){
            for(j=0;j<m;j++)
                printf("%d", matriz[i] [j]);
            
        }
    

	//x=num*n;
	//y=num*m;
	//fw= fopen (argv[5], "w");
	//fprintf(fw,"%d %d\n", x, y);


	return 0;
}
