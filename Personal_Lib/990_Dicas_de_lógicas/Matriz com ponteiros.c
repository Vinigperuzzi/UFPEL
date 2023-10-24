#include <stdio.h>
#include <stdlib.h>

int main(){ 

	int **M;
	int i, j, ncols=5,nrows=6;

	M = (int **)malloc(nrows*sizeof(int *));
	for(i=0; i<nrows; i++)
	M[i] = (int *)malloc(ncols*sizeof(int)); 
	
	//Agora podemos acessar M[i][j]:
	// Matriz M na linha i, coluna j.  
	...

	return 0; }

    // imprime elementos
    for (i = 0; i < nrows; i++) {
        for(j = 0; j < ncols; j++){
            printf("[%d, %d] = %d ", i,j, matriz[i][j]);
        }
        printf("\n");
    }

 	// free
	...
	//Desaloca memória. 

	for(i=0; i<nrows; i++)
		free(M[i]); free(M);
		return 0; }





void ler_string(char palavra[100], int tamanho)
{
	int i = 0;
	char c;

	c = getchar();
	while ((c != '\n') && (i < tamanho)) {
		palavra[i++] = c;
		c = getchar();
	}
	palavra[i] = '\0';

	if (c != '\n') {
		c = getchar();
		while ((c != '\n') && (c != EOF)) {
			c = getchar();
		}
	}

}
