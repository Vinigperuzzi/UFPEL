#include <stdio.h>
#include <stdlib.h>

#define maximo 20
#define infinito 99999999

//float vertices[maximo][maximo];
char nomes[maximo][10];
int quant=0, caminhoMinimo[maximo];

typedef struct etiqueta {
    int vert;
    int acumulado;
    int precedente;
    int visitado;
} etiq;

etiq caminho[maximo];

int dijkstra(int vertIni, int vertFim);


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


int **vertices;
int main(void){

    int op;

    system ("cls || clear");
    
    //zeraMatriz();

    
    int vert = 0, cols = 0, i;
    vertices = lerMatriz("tsp1_253.txt", &vert, &cols);

    for (int i = 0; i<vert; i++){
        for (int j = 0; j<cols; j++){
            if (vertices[i][j] == 0){
                vertices[i][j] = -1;
            }
        }
    }
    imprimirMatriz(vertices, vert, cols);

    int final[quant], acumuladoFinal = 0, vertD, prox = 0;
    for (int i = 0; i < quant-1; i++){
        int menor = 999999;
        for (int j = 0; j<quant-1; j++){
            if (i != j && caminho[j].visitado == 0){
                vertD = dijkstra(prox, j);
                if (caminho[j].acumulado < menor){
                    menor = caminho[j].acumulado;
                    final[i-1] = j;
                    prox = j;
                }
            }
        acumuladoFinal += menor;
        }
    }

    printf("Custo total = %d\nPelo caminho:\n\n0 -> ", acumuladoFinal);
    for(int i = 0; i<quant-2; i++){
        printf("%d -> ", final[i]);
    }
    printf("0\n\n");


    return 0;
}

int dijkstra(int vert1, int vert2){

    int i, vertAtual, fim, menor, menorVert;

    for (i=0; i<quant; i++){                            //Todos os vértices com acumulado infinito, ou valor(caso adjacente de A), sem antecedentes e não visitados
        caminho[i].vert = i;
        caminho[i].precedente = -1;
        caminho[i].visitado = 0;
    }

    caminho[vert1].acumulado = 0;                        //vértice de origem marcado como visitado e com acumulado 0
    caminho[vert1].visitado = 1;

    for (i=0; i<quant; i++){                            //Inicialização
        if (vertices[vert1][i] != -1){
            caminho[i].acumulado = vertices[vert1][i];
            caminho[i].precedente = vert1;
        }
        else if (vert1 != i) {
            caminho[i].acumulado = infinito;
        }
    }

    vertAtual = vert1;
    fim = 1;                            //Variável que fará o controle dos vértices visitados

    while (fim != 0){
        menor = infinito;
        for (i=0; i<quant; i++){        //Acha o menor valor
            if (caminho[i].visitado == 0){
                if (menor > caminho[i].acumulado){
                    menor = caminho[i].acumulado;
                    menorVert = i;
                }
            }
        }
        if (menor == infinito){
            fim = 0;
        }
        else {
            caminho[menorVert].visitado = 1;
            vertAtual = menorVert;
            for (i=0; i<quant; i++){
                if (vertices[vertAtual][i] != -1 && caminho[i].visitado == 0){
                    if (caminho[i].acumulado > (caminho[vertAtual].acumulado + vertices[vertAtual][i])){
                    caminho[i].acumulado = caminho[vertAtual].acumulado + vertices[vertAtual][i];
                    caminho[i].precedente = vertAtual;
                    }
                }
            }
            fim = 0;
            for (i=0; i<quant; i++)
                if (caminho[i].visitado == 0)
                    fim++;
        }

    }

    //====================================================
    
    // int cont=0;
    // caminhoMinimo[cont] = vert2;
    // for (i=vert2; i!=vert1;){                   //Imprime os valores
    //     if (caminho[i].precedente == -1){
    //         printf("\n\nNão há caminhos entre esses dois vértices.");
    //         return;
    //     }
    //     cont++;
    //     caminhoMinimo[cont] = caminho[i].precedente;
    //     i = caminho[i].precedente;
    // }

    // printf("\n\nMenor caminho encontrado com a distância de %d pelo seguinte caminho:\n\n", caminho[vert2].acumulado);
    // for (cont; cont >= 0; cont--){    
    //     for(int j=0; nomes[caminhoMinimo[cont]][j] != '\n' && nomes [caminhoMinimo[cont]][j] != '\0'; j++){
    //         putchar(nomes[caminhoMinimo[cont]][j]);
    //     }
    //     if (cont > 0)
    //         printf("  -->  ");
    // }
    return vert2;
}