/*A função abaixo implementa o algoritmo de Kruskal, para que ela possa ser executada são necessárias
Algumas estruturas de dados:
Dentre elas uma estrutura, que usa a variável de outra estrutura.

typedef struct Aresta{
    int vertA, vertB;
    float peso;
} Aresta;

typedef struct ArestaLista{
    Aresta dados[((maximo*maximo)-maximo)/2];//(n*n)-n/2 encontra a quantidade máxima de arestas possíveis para um grafo de n vértices. Não é possível ter mais arestas do que isso sem repetição.
    int n;
} ArestaLista;

Para isso já é necessária a declaração ou definição de uma variável int de nome "maximo" que contenha a quantidade
total de vértices.
#define maximo 20; (ou o valor necessário)

A função recebe como parâmetro duas estruturas, a matriz de adjacencia que contém os valores das arestas para os vértices.
e a quantidade de vértices no programa.
Geralmente essas duas estruturas são globais, então deve-se apagá-los dos parametros, porém caso sejam locais, é só passá-los
na chamada da função.

E por fim, esse programa imprime o caminho da árvore geradora mínima e o custo totl dessa árvore, a função imprimeMST
imprime o caminho pelos nomes dos vértices, mas para isso é necessário uma matriz de nomes global, com os nomes em ordem
de cada vértice do programa, caso não haja essa matriz no programa em questão, ao final dessa função fica comentado uma
opção de algoritmo de impressão que não use os nomes como caminhos.
*/

ArestaLista sort(ArestaLista listaIni);
void imprimeMST(void);

void Kruskal(float vertices[maximo][maximo], int quant) {
    int conjDisjunto[((maximo*maximo)-maximo)/2], i, j, vN1, vN2, testaConexo;
    ArestaLista listaIni, listaFim;
    listaIni.n = 0;

    if (quant <= 1){
        printf("\n\nSó é possível gerar uma árvore mínima com dois ou mais vértices!\n\n");
        return;
    }

    for(i=0; i<quant; i++){
        for(j=0; j<quant; j++){
            if (vertices[i][j] != -1){
                listaIni.dados[listaIni.n].vertA = i;
                listaIni.dados[listaIni.n].vertB = j;
                listaIni.dados[listaIni.n].peso = vertices[i][j];
                listaIni.n++;
            }
        }
    }
    
    listaIni = sort(listaIni);

    for (i=0; i<quant; i++)
        conjDisjunto[i] = i;
    
    listaFim.n = 0;

    for (i=0; i<listaIni.n; i++){
        vN1 = conjDisjunto[listaIni.dados[i].vertA];
        vN2 = conjDisjunto[listaIni.dados[i].vertB];

        if (vN1 != vN2) {
            listaFim.dados[listaFim.n] = listaIni.dados[i];
            listaFim.n++;
            for (j=0; j<quant; j++)
                if (conjDisjunto[j] == vN2)
                    conjDisjunto[j] = vN1;
        }
    }
    testaConexo = 0;
    for (i=0; i<quant-1; i++)
        if (conjDisjunto[i] != conjDisjunto[i+1])
            testaConexo++;
    if (testaConexo != 0){
        printf("\n\nO Grafo não é conexo! O grafo deve ser conexo para que se possa encontrar a árvore geradora mínima\n\n");
        return;
    }
    imprimeMST();
}

ArestaLista sort(ArestaLista listaIni) {
  int i, j;
  Aresta temp;

  for (i = 1; i < listaIni.n; i++)
    for (j = 0; j < listaIni.n - 1; j++)
      if (listaIni.dados[j].peso > listaIni.dados[j + 1].peso) {
        temp = listaIni.dados[j];
        listaIni.dados[j] = listaIni.dados[j + 1];
        listaIni.dados[j + 1] = temp;
      }
      return listaIni;
}


void imprimeMST(void){
    int i, j;
    float custo = 0;

    printf("\n\n\nA árvore geradora mínima desse grafo segue o seguinte caminho:\n\n");
    for (i=0; i<listaFim.n; i++){
        for(j=0; nomes[listaFim.dados[i].vertA][j] != '\n' && nomes [listaFim.dados[i].vertA][j] != '\0'; j++){
            putchar(nomes[listaFim.dados[i].vertA][j]);
        }
        printf(" <---> ");
        for(j=0; nomes[listaFim.dados[i].vertB][j] != '\n' && nomes [listaFim.dados[i].vertB][j] != '\0'; j++){
            putchar(nomes[listaFim.dados[i].vertB][j]);
        }
        printf(" : %.2f.\n", listaFim.dados[i].peso);
        custo = custo + listaFim.dados[i].peso;
    }

    printf("\nCusto total da árvore geradora mínima: %.2f", custo);
}

/* Opção de função de impressão, para o caso do programa não possuir uma matriz de nomes do vértices.

void print() {
  int i, cost = 0;

  for (i = 0; i < listaFim.n; i++) {
    printf("\n%d - %d : %.2f", listaFim.dados[i].vertA, listaFim.dados[i].vertB, listaFim.dados[i].peso);
    cost = cost + listaFim.dados[i].peso;
  }

  printf("\nSpanning tree cost: %d", cost);
}
*/