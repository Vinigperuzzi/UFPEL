#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int chave;
	int cor; // 1-red, 0-black
	struct node* pai; // parent
	struct node* dir; // right-child
	struct node* esq; // left child
} node ;

// global root for the entire tree
node *root = NULL;

node *reset(int chave);
node *push(node *trav, node *temp);
void leftrotate(node *temp);
void rightrotate(node *temp);
int empty(node *raiz);
void clear(node *raiz);
void listaPO(node *no);
void listaPosO(node *no);
void listaCentral(node *no);
void print(node *raiz, int nivel);


node *reset(int chave)//Cria um novo elemento para ser inserido. (Usada pela função push)
{
    node *novo = (node *)malloc(sizeof(node));
    if (novo == NULL){
	  printf("Não foi possível alocar memória.\n");
	  return novo;
    }
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;
	novo->chave = chave;
	novo->cor = 1;

    return novo;
}

// function to perform BST insertion of a node
node *push(node *trav, node *temp)
{
    // If the tree is empty,
    // return a new node
    if (trav == NULL)
        return temp;
 
    // Otherwise recur down the tree
    if (temp->chave < trav->chave)
    {
        trav->esq = push(trav->esq, temp);
        trav->esq->pai = trav;
    }
    else if (temp->chave > trav->chave)
    {
        trav->dir = push(trav->dir, temp);
        trav->dir->pai = trav;
    }
 
    // Return the (unchanged) node pointer
    return trav;
}

// Function performing right rotation
// of the passed node
void rightrotate(node *temp)
{
	node *esq = temp->esq;
	temp->esq = esq->dir;
	if (temp->esq)
		temp->esq->pai = temp;
	esq->pai = temp->pai;
	if (!temp->pai)
		root = esq;
	else if (temp == temp->pai->esq)
		temp->pai->esq = esq;
	else
		temp->pai->dir = esq;
	esq->dir = temp;
	temp->pai = esq;
}

// Function performing left rotation
// of the passed node
void leftrotate(node *temp)
{
	struct node* dir = temp->dir;
	temp->dir = dir->esq;
	if (temp->dir)
		temp->dir->pai = temp;
	dir->pai = temp->pai;
	if (!temp->pai)
		root = dir;
	else if (temp == temp->pai->esq)
		temp->pai->esq = dir;
	else
		temp->pai->dir = dir;
	dir->esq = temp;
	temp->pai = dir;
}

// This function fixes violations
// caused by BST insertion
void fixup(node *root, struct node *pt)
{
	node *pai = NULL;
	node *vo = NULL;

	while ((pt != root) && (pt->cor != 0) && (pt->pai->cor == 1))
	{
		pai = pt->pai;
		vo = pt->pai->pai;

		/* Case : A
			Parent of pt is left child
			of Grand-parent of
		pt */
		if (pai == vo->esq)
		{

			node *tio = vo->dir;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if (tio != NULL && tio->cor == 1)
			{
				vo->cor = 1;
				pai->cor = 0;
				tio->cor = 0;
				pt = vo;
			}

			else {

				/* Case : 2
					pt is right child of its parent
					Left-rotation required */
				if (pt == pai->dir) {
					leftrotate(pai);
					pt = pai;
					pai = pt->pai;
				}

				/* Case : 3
					pt is left child of its parent
					Right-rotation required */
				rightrotate(vo);
				int t = pai->cor;
				pai->cor = vo->cor;
				vo->cor = t;
				pt = pai;
			}
		}

		/* Case : B
			Parent of pt is right
			child of Grand-parent of
		pt */
		else {
			node *tio = pai->esq;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((tio != NULL) && (tio->cor == 1))
			{
				vo->cor = 1;
				pai->cor = 0;
				tio->cor = 0;
				pt = vo;
			}
			else {
				/* Case : 2
				pt is left child of its parent
				Right-rotation required */
				if (pt == pai->esq) {
					rightrotate(pai);
					pt = pai;
					pai = pt->pai;
				}

				/* Case : 3
					pt is right child of its parent
					Left-rotation required */
				leftrotate(vo);
				int t = pai->cor;
				pai->cor = vo->cor;
				vo->cor = t;
				pt = pai;
			}
		}
	}

	root->cor = 0;
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

void listaPO(node *no)//Pré ordem
{
    if (no == NULL)
        return;
    printf("%d(%d) ", no->chave, no->cor);
    listaPO(no->esq);
    listaPO(no->dir);
}


void listaPosO(node *no)//Pós ordem
{
    if (no == NULL)
        return;
    listaPosO(no->esq);
    listaPosO(no->dir);
    printf("%d(%d) ", no->chave, no->cor);
}

void listaCentral(node *no)//Ordem central
{
    if (no == NULL)
        return;
    listaCentral(no->esq);
	printf("%d(%d) ", no->chave, no->cor);
    listaCentral(no->dir);
}

void print(node *raiz, int nivel)//Imprime mostrando os níveis
{
  	node *no = raiz;

  	if(no != NULL){
    	printf("\nLEVEL: %d - %d(%d)", nivel, no->chave, no->cor);
    	print(no->esq, nivel + 1);
    	print(no->dir, nivel + 1);
  	}
  return;
}

int main (void){
	int swOp, chave;

	for (;;){
		printf("Informe a operação que deseja fazer: \n\t[1] Inserir um novo valor.\n\t[2] Excluir algum valor da árvore.\n\t[3] Excluir toda a árvore.\n\t[4] Lista por pré-ordem.\n\t[5] Lista por pós-ordem.\n\t[6] Lista por ordem central.\n\t[7] Lista por níveis\n\t[8] Verifica se é árvore AVL\n\t[9] Sair.\n");
		scanf("%d", &swOp);

		switch (swOp){
		case 1: printf("Informe o valor da chave: \n");
				scanf("%d", &chave);
				node *temp = reset(chave);
				root = push(root, temp);
				fixup(root, temp);
				break;
		/*case 2:	if (empty(raiz) == 1){
					printf("Não há dados a serem removidos.\n");
					break;
					}
				printf("Informe o valor da chave do nó a ser removido: \n");
				scanf("%d", &chave);
				raiz = pop(raiz, chave);
				break;*/
		case 3:	if (empty(root) == 1){
					printf("Não há dados a serem removidos.\n");
					break;
					}
				clear(root);
				root = NULL;
				break;
		case 4: if (empty(root) == 1){
					printf("Não há dados a serem listados: \n");
					break;
				} 
				printf("\n\t\tListando a árvore: \n\n\t");
				listaPO(root);
				printf("\n\n");
				break;
		case 5: if (empty(root) == 1){
					printf("Não há dados a serem listados: \n");
					break;
				} 
				printf("\n\t\tListando a árvore: \n\n\t");
				listaPosO(root);
				printf("\n\n");
				break;
		case 6: if (empty(root) == 1){
					printf("Não há dados a serem listados: \n");
					break;
				} 
				printf("\n\t\tListando a árvore: \n\n\t");
				listaCentral(root);
				printf("\n\n");
				break;
		case 7:	if (empty(root) == 1){
					printf("Não há dados a serem listados: \n");
					break;
				}
				printf("\n\t\tListando a árvore: \n\n\t");
				print(root, 1);
				printf("\n\n");
				break;
		/*case 8:	if (EhArvoreArvl(raiz) == 1)
					printf("É árvore AVL!\n");
				else
					printf("Opa! Não é árvore AVL!");
				break;*/
		case 9: clear(root);
				exit(0);
		default:
				printf("Informe um valor entre 1 e 9!\n");
		}
	}
}
