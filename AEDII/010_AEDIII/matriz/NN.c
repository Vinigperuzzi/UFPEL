#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int quant = 0;


int **lerMatriz(char *nome_arquivo, int *vertices, int *cols)
{
    FILE *fp;
    char ch;
    int i, j;

    // abrir arquivo
    fp = fopen(nome_arquivo, "r");
    if (fp == NULL){
        printf("\nArquivo não existe\n");
        exit(-1);
    }

    // determinar o número de linhas e colunas
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            (*vertices)++;
            quant++;
        }
    }

    (*vertices)++;
    quant++;
    *cols = *vertices; // valor de colunas + 1 == linhas

    // voltar para o início do arquivo
    rewind(fp);

    // alocar matriz
    int **matriz = (int **)malloc((*vertices) * sizeof(int *));
    for (i = 0; i < (*vertices); i++)
    {
        matriz[i] = (int *)malloc((*cols) * sizeof(int));
    }

    // preencher matriz com valores do arquivo
    for (i = 0; i < (*vertices); i++)
    {
        for (j = 0; j < (*cols); j++)
        {
            fscanf(fp, "%d", &matriz[i][j]);
            if (j < (*cols) - 1)
            {
                // descartar tabulação
                fgetc(fp);
            }
        }
    }

    // fechar arquivo
    fclose(fp);

    return matriz;
}


void imprimirMatriz(int **matriz, int vertices, int cols)
{
    int i, j;
    for (i = 0; i < vertices; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void ler_string(char palavra[20], int tamanho)//Deve-se passar o nome da string e o tamanho a ser lido.
{
	int i = 0;
	char c;

	c = getchar();
	while ((c != '\n') && (i < tamanho)) {
		palavra[i++] = c;
		c = getchar();
	}
	palavra[i] = '\0';

	//Consome o restante do buffer caso a palavra tenha sido encerrada por tamanho.
	if (c != '\n') {
		c = getchar();
		while ((c != '\n') && (c != EOF)) {
			c = getchar();
		}
	}
}


int main (void){
    int **matriz;
    int vert = 0, cols = 0;

    printf("\n\nInform the name of the files to read the matrix: (If it is in the folder, just informe the name, no need for path):\n");
    char fileName[20];
    ler_string(fileName, 20);

    matriz = lerMatriz(fileName, &vert, &cols);
    imprimirMatriz(matriz, vert, cols);
    printf("\nquanidade de vértices = %d\n", quant);
    int visitado[quant], caminho[quant+1];
    for (int i = 0; i < quant; i++){
        visitado[i] = 0;
    }

    srand(time(NULL));

    int menor = 999999, atual = rand()%quant-1, soma = 0;
    caminho[0] = atual; caminho[quant] = atual; visitado[atual] = 1;

    clock_t start, end;
    double ETime;
    start = clock();

    for (int i = 0; i< quant; i++){
        menor = 999999;
        for (int j = 0; j < quant; j++){
            if (atual != j && visitado[j] == 0){
                if (matriz[atual][j] < menor){
                    menor = matriz[atual][j];
                    caminho[i+1] = j;
                }
            }
        }
        if (menor < 999999){
            soma += menor;
            visitado[atual] = 1;
            atual = caminho[i+1];
        }
    }

    soma += matriz[caminho[quant-1]][caminho[0]];

    end = clock();

    printf("\n\n\n\t\tO caminho resultou em %d!\n\n\t\tSeguindo o seguinte caminho:\n\n", soma);
    for (int i = 0; i <= quant; i++){
        printf("%d", caminho[i]);
        if (i != quant){
            printf(" --> ");
        }
    }
    printf("\n\n\t\tThe total time of execution was: %f\n\n\n", ETime);
}