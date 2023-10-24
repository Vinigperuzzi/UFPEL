#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int chave;
	struct node *dir;
	struct node *esq;
} node;

node *raiz=NULL;

node *criaNo(void);
void push(node *novo, int chave);
void listaPO(node *no);
void listaPosO(node *no);
void listaCentral(node *no);
node * pop(node *no, int chave);
node * menorValorEsq(struct node* node);
int empty(node *raiz);
void clear(node *raiz);
void full(void);

node *criaNo(void)//Cria um novo elemento para ser inserido.
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

void push(node *no, int chave)
{
	node *novo = NULL;

	if (no == NULL){
		novo = criaNo();
		if (novo == NULL)
			return;
		novo->chave = chave;
		raiz = novo;
	} else{
		if (chave < no->chave && no->esq != NULL){
			push(no->esq, chave);
		} else if (chave > no->chave && no->dir != NULL){
			push(no->dir, chave);
		} else if (chave < no->chave && no->esq == NULL){
			novo = criaNo();
			no->esq = novo;
			novo->chave = chave;
		} else if (chave > no->chave && no->dir == NULL){
			novo = criaNo();
			no->dir = novo;
			novo->chave = chave;
		} else if(chave == no->chave){
			printf("\n\tValor já existe na árvore, informe outro.\n");
		}
	}
}

void listaPO(node *no)//Pré ordem
{
    if (no == NULL)
        return;
    printf("%d ", no->chave);
    listaPO(no->esq);
    listaPO(no->dir);
}


void listaPosO(node *no)//Pós ordem
{
    if (no == NULL)
        return;
    listaPosO(no->esq);
    listaPosO(no->dir);
    printf("%d ", no->chave);
}

void listaCentral(node *no)
{
    if (no == NULL)
        return;
    listaCentral(no->esq);
	printf("%d ", no->chave);
    listaCentral(no->dir);
}

void clear(node *raiz){
	node *noAtual = raiz;

	if(noAtual != NULL){
		clear(noAtual->esq);
    	clear(noAtual->dir);
	}
	free(noAtual);

	return;
}

int empty(node *raiz)
{
	if (raiz == NULL){
		return 1;
	}
	return 0;
}

node * pop(node *no, int chave)
{
  if (empty(no) == 1){
	  printf("Não há dados a serem removidos.\n");
      return no;
  } else{
		if (chave < no->chave)
			no->esq = pop(no->esq, chave);
		else if (chave > no->chave)
			no->dir = pop(no->dir, chave);//Seleções que buscam o valor a ser removido.
	
		else if(chave == no->chave){//Achou o valor a ser removido
			if (no->esq == NULL) {
				node *temp = no->dir;
				free(no);
				return temp;
			}
			else if (no->dir == NULL) {
				node* temp = no->esq;
				free(no);
				return temp;
			}//Bloco de instruções para apagar nós sem filhos(folhas), ou com apenas um filho.
	
			node *temp = menorValorEsq(no->dir);/*Caso chegue até aqui, significa que a árvore possui
												dois filhos, e o menor valor da subárvore da direita
												deve ser achado, o que acontece através da função menorValorEsq
												passando o nó da direita como parâmetro.*/
			no->chave = temp->chave;
			no->dir = pop(no->dir, temp->chave);//Deleta o sucessor
		}
		return no;
	}
}

node * menorValorEsq(node* no)//Recebe o próximo nó a direita
{ 
    struct node* atual = no;
 
    while (atual && atual->esq != NULL)//Busca a folha mais a esquerda
        atual = atual->esq;
 
    return atual;
}


int main (void){
	int swOp, chave;

	for (;;){
		printf("Informe a operação que deseja fazer: \n\t[1] Inserir um novo valor.\n\t[2] Excluir algum valor da árvore.\n\t[3] Excluir toda a árvore.\n\t[4] Lista por pré-ordem\n\t[5] Lista por pós-ordem\n\t[6] Lista por ordem central\n\t[7] Sair\n");
		scanf("%d", &swOp);

		switch (swOp){
		case 1: printf("Informe o valor da chave: \n");
				scanf("%d", &chave);
				push(raiz, chave);
				break;
		case 2:	if (empty(raiz) == 1){
					printf("Não há dados a serem removidos.\n");
					break;
					}
				printf("Informe o valor da chave do nó a ser removido: \n");
				scanf("%d", &chave);
				pop(raiz, chave);
				break;
		case 3:	if (empty(raiz) == 1){
					printf("Não há dados a serem removidos.\n");
					break;
					}
				clear(raiz);
				raiz = NULL;
				break;
		case 4: if (empty(raiz) == 1){
					printf("Não há dados a serem listados: \n");
				} 
				printf("\n\t\tListando a árvore: \n\n\t");
				listaPO(raiz);
				printf("\n\n");
				break;
		case 5: if (empty(raiz) == 1){
					printf("Não há dados a serem listados: \n");
				} 
				printf("\n\t\tListando a árvore: \n\n\t");
				listaPosO(raiz);
				printf("\n\n");
				break;
		case 6: if (empty(raiz) == 1){
					printf("Não há dados a serem listados: \n");
				} 
				printf("\n\t\tListando a árvore: \n\n\t");
				listaCentral(raiz);
				printf("\n\n");
				break;
		case 7: clear(raiz);
				exit(0);
		default:
				printf("Informe um valor entre 1 e 5!\n");
		}

	}
}