#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <limits.h> // para usar INT_MAX
#define INFINITY __INT_MAX__
int **lerMatriz(char *nome_arquivo, int *vertices, int *cols);
void imprimirMatriz(int **matriz, int vertices, int cols);
void dijkstra(int **matriz, int vertices);

int main()
{
    SetConsoleOutputCP(65001);
    int **matriz;
    int vertices = 0, cols = 0, i;
    matriz = lerMatriz("C://Users//EDUARDO//Desktop//aed3//tsp1_253.txt", &vertices, &cols);
    imprimirMatriz(matriz, vertices, cols);

    // desalocar matriz
    for (i = 0; i < vertices; i++)
    {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}

int **lerMatriz(char *nome_arquivo, int *vertices, int *cols)
{
    FILE *fp;
    char ch;
    int i, j;

    // abrir arquivo
    fp = fopen(nome_arquivo, "r");

    // determinar o número de linhas e colunas
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            (*vertices)++;
        }
    }

    (*vertices)++;
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