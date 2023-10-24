#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node{
	int chave;
	struct node *dir;
	struct node *esq;
} node;

node *raiz=NULL;

node * push(node *no, int chave);
node *criaNo(void);
node * balanceamento1(node * no, int chave);
int FB (node * no);
int altura(node * no);
node *rotaSimpDir(node *no);
node *rotaSimpEsq(node *no);
void listaCentral(node *no);
void listaPO(node *no);
int EhArvoreArvl(node * no);
void clear(node *raiz);


node * push(node *no, int chave)
{
	if(no == NULL){
		no = criaNo();
    if(no == NULL){
    	printf("Não foi possível alocar memória.\n");
    	return no;
	}
    no->chave = chave;
	}

	if(no->chave > chave){
    	no->esq = push(no->esq, chave);
	}
  	else if(no->chave < chave){
    	no->dir = push(no->dir, chave);
	}
	no = balanceamento1(no, chave);
	return no;
}

node *criaNo(void)
{
  node *novo = (node *)malloc(sizeof(node));
  if (novo == NULL){
	  printf("Não foi possível alocar memória.\n");
	  return novo;
  }
  novo->dir = NULL;
  novo->esq = NULL;

  return novo;
}

node * balanceamento1(node * no, int chave)
{
    int fator = FB(no);

    if (fator < -1 && chave > no->dir->chave)
        return rotaSimpEsq(no);
    if (fator > 1 && chave < no->esq->chave)
        return rotaSimpDir(no);
    if (fator > 1 && chave > no->esq->chave){
        no->esq =  rotaSimpEsq(no->esq);
        return rotaSimpDir(no);
    }
    if (fator < -1 && chave < no->dir->chave){
        no->dir = rotaSimpDir(no->dir);
        return rotaSimpEsq(no);
    }
    return no;
}

int FB (node * no)
{
	if (no == NULL)
		return 0;
	return altura(no->esq) - altura(no->dir);
}

int altura(node * no)
{
	int iEsq,iDir;
	if (no == NULL)
		return 0;
	iDir = altura(no->dir);	
	iEsq = altura(no->esq);
	if ( iEsq > iDir )
		return iEsq + 1;
	else
		return iDir + 1;
}

node *rotaSimpDir(node *no)
{
	node *filhoEsq = no->esq;
	node *netoDir = filhoEsq->dir;

	filhoEsq->dir = no;
	no->esq = netoDir;

	return filhoEsq;
}
 
node *rotaSimpEsq(node *no)
{
	node *filhoDir = no->dir;
	node *netoEsq = filhoDir->esq;

    filhoDir->esq = no;
    no->dir = netoEsq;

    return filhoDir;
}

void listaCentral(node *no)
{
    if (no == NULL)
        return;
    listaCentral(no->esq);
	printf("%d ", no->chave);
    listaCentral(no->dir);
}

void listaPO(node *no)
{
    if (no == NULL)
        return;
    printf("%d ", no->chave);
    listaPO(no->esq);
    listaPO(no->dir);
}

int EhArvoreArvl(node * no)
{
    int fator;

    if(no == NULL)
        return 1;

    if(!EhArvoreArvl(no->esq))
        return 0;
    if(!EhArvoreArvl(no->esq))
        return 0;
  
    fator = FB(no);
    if((fator > 1) || (fator < -1))
        return 0;
    else
        return 1;
}

void clear(node *raiz)
{
	node *noAtual = raiz;

	if(noAtual != NULL){
		clear(noAtual->esq);
    	clear(noAtual->dir);
	}
	free(noAtual);

	return;
}

int main (void)
{
    int valor, contador, chave;
    srand(time(0));

    printf("Informe a quantidade de nós para colocar na árvore: \n");
    scanf("%d", &valor);

    for (contador=0; contador<valor; contador++){
        chave = rand() %200;
        raiz = push(raiz, chave);
    }
    printf("\n\n\t\tImprimindo a árvore com os valores em ordem crescente de valores(inorder):\n\n\t\t");
    listaCentral(raiz);
    printf("\n\n\t\tImprimindo a árvore com os valores a partir da raiz (pre-order):\n\n\t\t");
    listaPO(raiz);
    printf("\n\n\t\tApós verificar na função concedida: ");
    if (EhArvoreArvl(raiz) == 1)
        printf("\n\n\t\tA árvore é AVL\n");
    else
        printf("\n\n\t\tOpa! A árvore não é AVL\n");

    clear(raiz);
    return 0;
}