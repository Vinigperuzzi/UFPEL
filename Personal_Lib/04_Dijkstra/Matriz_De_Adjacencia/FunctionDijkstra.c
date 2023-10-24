/*
Essa função abaixo implementa o algoritmo Dijkstra, para isso são necessárias algumas estruturas de dados
Dentre elas uma estrutura, nesse caso etiq:

typedef struct etiqueta {
    int vert;
    float acumulado;
    int precedente;
    int visitado;
} etiq;

Além disso, nesse caso é importante ter uma matriz com os valores das arestas, definidas a partir do 0
para os vértices, o tamanho não importa, podendo inclusive ser variável.

Nesse caso a função pede que seja passado como parametro o vértice de origem, o vértice de destino (em números inteiros correspondentes à matriz de valores)
e essa matriz de adjacência com os valores das arestas.
Caso a matriz seja global, o valor não precisa ser passado, mas o parâmetro da função deve ser apagado.
Caso seja local, ela deve ser declarada nos parametros da função com um tamanho "maximo" que contém a quantidade total de vértices.

Além disso, o programa imprime o valor do acumulado e os nomes dos vértices pelo caminho. Caso não haja essa
matriz de nomes, a parte final do código deve ser apagada. Nesse caso, o vetor caminhoMinimo[maximo] pode ser
retornado, ele possui o caminho da origem até o destino, vértice por vértice.

Outras variáveis necessárias, supõe-se que sejam globais, caso contrario devem ser passadas ou definidas:

maximo: vamor maximo de vértices aceitados, caso não seja global deve ser passada por parâmetro e criada como int maximo.
Além de ser necessária para a declaração da matriz nos parâmetros. Se receber um tamanho, já é possível usá-lo no
próximo atributo. Ex: function(int tamanho, int vetor[tamanho]).
Mas esse valor geralmente é definido no inicio do programa.

quant: quantidade de vértices atual no grafo, é usado para otimização dos for's.
Caso não seja global, deve ser passada por parâmetro e criada como int quant.
Caso o algoritmo não compreenda essa informação, ela pode ser criada como variável e assumir o valor de máximo.
(Executará os for's para todas as possibilidades de vértices existam ou não)

infinito: Valor imenso a ser considerado infinito para que possa ser feita a comparação de valores mínimos.
*/

void dijkstra(int vert1, int vert2, float vertices[maximo][maximo]){

    int i, vertAtual, fim, menor, menorVert, caminhoMinimo[maximo];
    etiq caminho[maximo];

    for (i=0; i<quant; i++){                            
        caminho[i].vert = i;
        caminho[i].precedente = -1;
        caminho[i].visitado = 0;
    }

    caminho[vert1].acumulado = 0;                        
    caminho[vert1].visitado = 1;

    for (i=0; i<quant; i++){                            
        if (vertices[vert1][i] != -1){
            caminho[i].acumulado = vertices[vert1][i];
            caminho[i].precedente = vert1;
        }
        else if (vert1 != i) {
            caminho[i].acumulado = infinito;
        }
    }

    vertAtual = vert1;
    fim = 1;                            

    while (fim != 0){
        menor = infinito;
        for (i=0; i<quant; i++){        
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
    
    int cont=0;
    caminhoMinimo[cont] = vert2;
    for (i=vert2; i!=vert1;){                   
        if (caminho[i].precedente == -1){
            printf("\n\nNão há caminhos entre esses dois vértices.");
            return;
        }
        cont++;
        caminhoMinimo[cont] = caminho[i].precedente;
        i = caminho[i].precedente;
    }

    printf("\n\nMenor caminho encontado com a distância de %.2f pelo seguinte caminho:\n\n", caminho[vert2].acumulado);
    for (cont; cont >= 0; cont--){    
        for(int j=0; nomes[caminhoMinimo[cont]][j] != '\n' && nomes [caminhoMinimo[cont]][j] != '\0'; j++){
            putchar(nomes[caminhoMinimo[cont]][j]);
        }
        if (cont > 0)
            printf("  -->  ");
    }
}