#include <stdio.h>
#include <stdlib.h>

#define maximo 20
#define infinito 99999999

char nomes[maximo][10];
int quant=0;

typedef struct etiqueta {
    int vert;
    float acumulado;
    int precedente;
    int visitado;
} etiq;

void zeraMatriz(float vertices[maximo][maximo]);
void pedeVertices(float vertices[maximo][maximo]);
void pedeArestas(float vertices[maximo][maximo]);
void imprimeMatriz(float vertices[maximo][maximo]);
void buscaCaminho(float vertices[maximo][maximo]);
void dijkstra(int vertIni, int vertFim, float vertices[maximo][maximo]);


int main(void){

    int op;
    float vertices[maximo][maximo];

    system ("cls || clear");
    
    zeraMatriz(vertices);

    for(;;){
        do {
            imprimeMatriz(vertices);
            printf("\tInforme a opera��o que deseja fazer: \n\t[1] Inserir v�rtices\n\t[2] Inserir arestas\n\t[3] Buscar um caminho m�nimo entre v�rtices\n\t[4] Sair do programa\n");
            scanf("%d", &op);
            if (op < 1 || op > 4)
                printf("\n\tVoc� precisa informar um valor v�lido para sele��o!\n\n");
        } while (op < 1 || op > 4);

        switch (op)
        {
        case 1: pedeVertices(vertices);
            break;
        case 2: pedeArestas(vertices);
            break;
        case 3: buscaCaminho(vertices);
            break;
        case 4: exit(0);
        default: printf("\n\nAconteceu algum erro!\n Tente novamente.\n\n");
            break;
        }
    }

    return 0;
}


void zeraMatriz(float vertices[maximo][maximo]){

    for(int i=0; i<maximo; i++)
        for(int j=0; j<maximo; j++)
            vertices[i][j] = -1;
}

void pedeVertices(float vertices[maximo][maximo]){

    if (quant < maximo){
        printf("\n\nMatriz atual:\n\n");
        imprimeMatriz(vertices);
        printf("\n\nPor favor, informe o nome do v�rtice com at� 10 letras: ");
        getchar();
        fgets(nomes[quant], 10, stdin);
        quant++;
    } 
    else
        printf("\nM�ximo de v�rtices atingidos!\n");
    return;
}


void pedeArestas(float vertices[maximo][maximo]){

    if (quant == 0 || quant == 1){
        printf("\n\nN�o h� v�rtices suficientes para receber arestas");
        return;
    }

    int vert1 = 0, vert2 = 0;
    printf("\n\nMatriz atual:\n\n");
    imprimeMatriz(vertices);
    
    printf("\nInforme os v�rtices aos quais deseja conectar uma aresta, um de cada vez: \n");
    do { 
        for(int i=0; i<=maximo; i++)
            if (nomes[i][0] != '\0')
                printf("%d�:  %s",i + 1, nomes[i]);
        scanf("%d", &vert1);
        vert1--;
        if (vert1 > quant-1 || vert1 < 0)
            printf("\n� necess�rio informar um valor de v�rtice existente.\n\n");
    } while (vert1 > quant-1 || vert1 < 0);

    do { 
        scanf("%d", &vert2);
        vert2--;
        if (vert2 > quant-1 || vert2 < 0)
            printf("\n� necess�rio informar um valor de v�rtice existente.\n\n");
        if (vert1 == vert2){
            printf("\n\nPara fins de busca de caminhos m�nimos, n�o se considera loops");
            return;
        }
    } while (vert2 > quant-1 || vert2 < 0 || vert1 == vert2);

    
    if (vert1 == maximo || vert2 == maximo)
        return;

    printf("Por favor, informe o valor da aresta entre os v�rtices: ");
        
    for(int j=0; nomes[vert1][j] != '\n' && nomes [vert1][j] != '\0'; j++){
        putchar(nomes[vert1][j]);
    }
    printf(" e ");
    for(int j=0; nomes[vert2][j] != '\n' && nomes [vert2][j] != '\0'; j++){
        putchar(nomes[vert2][j]);
    }
    printf(": ");  //De 74 a 81 s� formata a sa�da no terminal, sem enter onde n�o deve e com espa�os que fazem sentido.


    setbuf(stdin, NULL);
    scanf("%f", &vertices[vert1][vert2]);
    vertices[vert2][vert1] = vertices[vert1][vert2];
}


void imprimeMatriz(float vertices[maximo][maximo]){

    int i, j, qtd=0;
    printf("\n\n");
    for(i=0; i<=maximo; i++){
        printf("\t");
        if (nomes[i][0] != '\0'){
            for(int j=0; nomes[i][j] != '\n' && nomes [i][j] != '\0'; j++){
                putchar(nomes[i][j]);
            }
            qtd++;
        }
    }
    for (i=0; i < qtd; i++){
        printf("\n");
        for(j=0; nomes[i][j] != '\n' && nomes [i][j] != '\0'; j++){
                putchar(nomes[i][j]);
        }
        for(j=0; j<qtd; j++){
            if(vertices[i][j] != -1)
                printf("\t%.2f", vertices[i][j]);
            else   
                printf("\t-");
        }
    }
    printf("\n\n");
}


void buscaCaminho(float vertices[maximo][maximo]){

    int vert1, vert2, i;

    if (quant == 0 || quant == 1){
        printf("\n\nN�o h� v�rtices suficientes a serem buscados");
        return;
    }

    printf("\n\n\tInforme o v�rtice inicial da busca do caminho: \n");
    do { 
        for(i=0; i<=maximo; i++)
            if (nomes[i][0] != '\0')
                printf("%d�:  %s",i + 1, nomes[i]);
        scanf("%d", &vert1);
        vert1--;
        if (vert1 > quant-1 || vert1 < 0)
            printf("\n� necess�rio informar um valor de v�rtice existente.\n\n");
    } while (vert1 > quant-1 || vert1 < 0);

    printf("\n\n\tInforme o v�rtice final da busca do caminho: ");
    do { 
        scanf("%d", &vert2);
        vert2--;
        if (vert2 > quant-1 || vert2 < 0 || vert2 == vert1)
            printf("\n� necess�rio informar um valor de v�rtice existente e diferente do primeiro informado.\nTente outro valor:\n\n");
    } while (vert2 > quant-1 || vert2 < 0 || vert2 == vert1);

    dijkstra(vert1, vert2, vertices);

}

/*
Essa fun��o abaixo implementa o algoritmo Dijkstra, para isso s�o necess�rias algumas estruturas de dados
Dentre elas uma estrutura, nesse caso etiq:

typedef struct etiqueta {
    int vert;
    float acumulado;
    int precedente;
    int visitado;
} etiq;

Al�m disso, nesse caso � importante ter uma matriz com os valores das arestas, definidas a partir do 0
para os v�rtices, o tamanho n�o importa, podendo inclusive ser vari�vel.

Nesse caso a fun��o pede que seja passado como parametro o v�rtice de origem, o v�rtice de destino
e essa matriz de adjac�ncia com os valores das arestas.
Caso a matriz seja global, o valor n�o precisa ser passado, mas o par�metro da fun��o deve ser apagado.
*/

/*
Esse algoritmo implementa a seguinte l�gica:

1. Seta o vertice passado como origem como visitado, o acumulado como 0 e o predececssor como -1 (para
indicar que ele n�o tem predecessor e n�o conflitar os valores)

2. Seta todos os demais como n�o visitados, acumulado infinito (valor muito grande) e sem predecessor (-1)

3.Para todos os adjacentes do v�rtice atual (o n� de origem em um primeiro instante e 
atualizado a cada execu��o).
Se o acumulado desse adjacente em quest�o (no teste de um por um), for maior
que o acumulado do v�rtice atual + o valor da aresta entre eles (atual---quest�o).
Ent�o muda o valor do acumulado pelo valor dessa soma (acumulado do v�rtice atual + valor da aresta entre eles).
Coloca-se o predecesor do v�rtice em quest�o como sendo o v�rtice atual (O atual passa a ser predecessor do em quest�o).

4.Procura-se o menor acumulado entre os v�rtice ainda n�o visitados.

5. Marca-se esse v�rtice como visitado, seta-se esse v�rtice como visitado, e faz-se com que ele seja o v�rtice atual.
Repete o procedimento a partir do 3.

Caso n�o seja poss�vel achar um menor valor acumulado, ou seja, todos s�o infinitos. Ent�o n�o h� mais v�rtices
adjacentes que se liguem ao caminho j� percorrido, e n�o � poss�vel chegar ao v�rtice de destino, em outras palavras,
N�o h� caminhos entre eles.

Ao final de cada execu��o, deve-se testar se ainda h� v�rtices n�o visitados, caso n�o haja, deve-se encerrar a
repeti��o e o programa deve seguir.

6. Ent�o deve-se percorrer o caminho de volta do v�rtice destino at� o v�rtice origem, atrav�s dos predecessores,
caso algum deles ainda seja -1, significa que n�o h� caminhos entre eles, e caso v� at� a origem, � s� imprimir
o caminho contr�rio ao percorrido e imprimir o acumulado no destino.
*/


void dijkstra(int vert1, int vert2, float vertices[maximo][maximo]){

    int i, vertAtual, fim, menor, menorVert, caminhoMinimo[maximo];
    etiq caminho[maximo];

    /*2. Todos n�o visitados, acumulado infinito e sem predecessores*/

    for (i=0; i<quant; i++){                            
        caminho[i].vert = i;
        caminho[i].precedente = -1;
        caminho[i].visitado = 0;
    }

    caminho[vert1].acumulado = 0;                        //1. V�rtice de origem marcado como visitado e com acumulado 0
    caminho[vert1].visitado = 1;

    for (i=0; i<quant; i++){                            //3. Faz o 3. para o v�rtice origem
        if (vertices[vert1][i] != -1){                  //Se � adjacente, tem o acumulado como a dist�ncia entre eles
            caminho[i].acumulado = vertices[vert1][i];
            caminho[i].precedente = vert1;              //E se torna predecessor
        }
        else if (vert1 != i) {                          //Caso n�o seja adjecente, se n�o � o pr�prio v�rtice segue infinito
            caminho[i].acumulado = infinito;
        }
    }

    vertAtual = vert1;
    fim = 1;                            //Variav�l que far� o controle dos v�rtices visitados e fim da repeti��o

    while (fim != 0){
        menor = infinito;
        for (i=0; i<quant; i++){                //Acha o menor valor acumulado dentre os v�rtice ainda n�o visitados
            if (caminho[i].visitado == 0){
                if (menor > caminho[i].acumulado){
                    menor = caminho[i].acumulado;
                    menorVert = i;
                }
            }
        }
        if (menor == infinito){                 //Caso n�o ache um valor menor, n�o h� mais adjacentes, ent�o deve encerrar
            fim = 0;
        }
        else {                                  //Mas caso ache deve trocar os valores
            caminho[menorVert].visitado = 1;
            vertAtual = menorVert;
            for (i=0; i<quant; i++){            //Troca os valores daqueles que s�o maiores que a dist�ncia testada
                if (vertices[vertAtual][i] != -1 && caminho[i].visitado == 0){
                    if (caminho[i].acumulado > (caminho[vertAtual].acumulado + vertices[vertAtual][i])){
                    caminho[i].acumulado = caminho[vertAtual].acumulado + vertices[vertAtual][i];
                    caminho[i].precedente = vertAtual; //Trocando o predecessor inclusive, atualiza a etiqueta por assim dizer
                    }
                }
            }
            fim = 0;
            for (i=0; i<quant; i++)         //Teste se ainda h� v�rtices n�o visitados
                if (caminho[i].visitado == 0)
                    fim++;
        }                                   //Caso haja, encerra
        
    }
    
    int cont=0;
    caminhoMinimo[cont] = vert2;
    for (i=vert2; i!=vert1;){                   //Percorre o caminho inverso
        if (caminho[i].precedente == -1){
            printf("\n\nN�o h� caminhos entre esses dois v�rtices."); //Caso n�o algum n�o tenha predecessor
            return;
        }
        cont++;
        caminhoMinimo[cont] = caminho[i].precedente;    //monta um vetor com o caminho inverso do que est� sendo percorrido
        i = caminho[i].precedente;
    }

    /*Imprime o valor acumulado e o caminho na ordem certa, que foi invertido pelo vetor do passo anterior*/

    printf("\n\nMenor caminho encontado com a dist�ncia de %.2f pelo seguinte caminho:\n\n", caminho[vert2].acumulado);
    for (cont; cont >= 0; cont--){    
        for(int j=0; nomes[caminhoMinimo[cont]][j] != '\n' && nomes [caminhoMinimo[cont]][j] != '\0'; j++){
            putchar(nomes[caminhoMinimo[cont]][j]);
        }
        if (cont > 0)
            printf("  -->  ");
    }
}