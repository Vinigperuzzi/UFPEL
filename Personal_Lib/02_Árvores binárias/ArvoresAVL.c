#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int chave;
	struct node *dir;
	struct node *esq;
} node;

node *raiz=NULL;

node *criaNo(void);
node * push(node *novo, int chave);
void listaPO(node *no);
void listaPosO(node *no);
void listaCentral(node *no);
void print(node *raiz, int nivel);
node * pop(node *no, int chave);
node * menorValorEsq(struct node* node);
int FB (node * no);
int altura(node * no);
int empty(node *raiz);
void clear(node *raiz);
void full(void);
node * rotaSimpEsq(node *no);
node * rotaSimpDir(node *no);
node * balanceamento1(node * no, int chave);
node * balanceamento2(node * currentNode);
int EhArvoreArvl(node * no);

node *criaNo(void)//Cria um novo elemento para ser inserido. (Usada pela função push)
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

node * push(node *no, int chave)//Insere um novo nó na árvore. (deve ser chamada passando o ponteiro da raiz e o valor da chave)
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

void listaCentral(node *no)//Ordem central
{
    if (no == NULL)
        return;
    listaCentral(no->esq);
	printf("%d ", no->chave);
    listaCentral(no->dir);
}

void print(node *raiz, int nivel)//Imprime mostrando os níveis
{
  	node *no = raiz;

  	if(no != NULL){
    	printf("\nLEVEL: %d - %d", nivel, no->chave);
    	print(no->esq, nivel + 1);
    	print(no->dir, nivel + 1);
  	}
  return;
}

void clear(node *raiz)//Apaga toda a árvore, lembre-se de fazer um raiz = NULL após chamar essa função, lá na função principal.
{
	node *noAtual = raiz;

	if(noAtual != NULL){
		clear(noAtual->esq);
    	clear(noAtual->dir);
	}
	free(noAtual);
	return;
}

int empty(node *raiz)//Testa se a árvore está vazia
{
	if (raiz == NULL){
		return 1;
	}
	return 0;
}

node * pop(node *no, int chave)//remove um valor da árvore. (Deve-se passar o ponteiro da cabeça e o valor da chave a ser removida)
{
	node *temp;
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
				temp = no->dir;
				free(no);
				return temp;
			}
			else if (no->dir == NULL) {
				temp = no->esq;
				free(no);
				return temp;
			}//Bloco de instruções para apagar nós sem filhos(folhas), ou com apenas um filho.
	
			temp = menorValorEsq(no->dir);	/*Caso chegue até aqui, significa que a árvore possui
											dois filhos, e o menor valor da subárvore da direita
											deve ser achado, o que acontece através da função menorValorEsq
											passando o nó da direita como parâmetro.*/
			no->chave = temp->chave;
			no->dir = pop(no->dir, temp->chave);//Deleta o sucessor
		}
		no = balanceamento2(no);
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

int FB (node * no)//Calcula o fator de balanceamento.
{
	if (no == NULL)
		return 0;
	return altura(no->esq) - altura(no->dir);
}

int altura(node * no)//Calcula a altura da árvore para ser usado no fator de balanceamento.
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

node * balanceamento1(node * no, int chave)//Balanceamento para usar após uma inserção
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

node * balanceamento2(node * no)//Para usar deletar um nó
{
    int fator = FB(no);

    if (fator > 1 && FB(no->esq) >= 0)
        no = rotaSimpDir(no);
    if (fator > 1 && FB(no->esq) < 0){
        no->esq =  rotaSimpEsq(no->esq);
        no = rotaSimpDir(no);
    }

    if (fator < -1 && FB(no->dir) <= 0)
        no = rotaSimpEsq(no);
    if (fator < -1 && FB(no->dir) > 0){
        no->dir = rotaSimpDir(no->dir);
        no = rotaSimpEsq(no);
    }
    return no;
}

int EhArvoreArvl(node * no)//Testa se é nó
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

int main (void){
	int swOp, chave;

	for (;;){
		printf("Informe a operação que deseja fazer: \n\t[1] Inserir um novo valor.\n\t[2] Excluir algum valor da árvore.\n\t[3] Excluir toda a árvore.\n\t[4] Lista por pré-ordem.\n\t[5] Lista por pós-ordem.\n\t[6] Lista por ordem central.\n\t[7] Lista por níveis\n\t[8] Verifica se é árvore AVL\n\t[9] Sair.\n");
		scanf("%d", &swOp);

		switch (swOp){
		case 1: printf("Informe o valor da chave: \n");
				scanf("%d", &chave);
				raiz = push(raiz, chave);
				break;
		case 2:	if (empty(raiz) == 1){
					printf("Não há dados a serem removidos.\n");
					break;
					}
				printf("Informe o valor da chave do nó a ser removido: \n");
				scanf("%d", &chave);
				raiz = pop(raiz, chave);
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
					break;
				} 
				printf("\n\t\tListando a árvore: \n\n\t");
				listaPO(raiz);
				printf("\n\n");
				break;
		case 5: if (empty(raiz) == 1){
					printf("Não há dados a serem listados: \n");
					break;
				} 
				printf("\n\t\tListando a árvore: \n\n\t");
				listaPosO(raiz);
				printf("\n\n");
				break;
		case 6: if (empty(raiz) == 1){
					printf("Não há dados a serem listados: \n");
					break;
				} 
				printf("\n\t\tListando a árvore: \n\n\t");
				listaCentral(raiz);
				printf("\n\n");
				break;
		case 7:	if (empty(raiz) == 1){
					printf("Não há dados a serem listados: \n");
					break;
				}
				printf("\n\t\tListando a árvore: \n\n\t");
				print(raiz, 1);
				printf("\n\n");
				break;
		case 8:	if (EhArvoreArvl(raiz) == 1)
					printf("É árvore AVL!\n");
				else
					printf("Opa! Não é árvore AVL!");
				break;	
		case 9: clear(raiz);
				exit(0);
		default:
				printf("Informe um valor entre 1 e 5!\n");
		}
	}
}