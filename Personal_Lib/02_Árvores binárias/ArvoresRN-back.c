#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int chave;
    int cor;//0 para preto, 1 para vermelho
    struct node *esq;
    struct node *dir;
    struct node *pai;
}node;

node *achaVo(node *no);
node *achaTio(node *no);
node *criaNo(void);
node * push(node *novo, int chave, node *pai);
void pushCase1(node *no);
void pushCase2(node *no);
void pushCase3(node *no);
void pushCase4(node *no);
void pushCase5(node *no);
void rotaSimpDir(node *no);
void rotaSimpEsq(node *no);
int empty(node *raiz);
void clear(node *raiz);
void listaPO(node *no);
void listaPosO(node *no);
void listaCentral(node *no);
void print(node *raiz, int nivel);

node *raiz = NULL;

node *achaTio(node *no)
{
    node *vo = achaVo(no);
    if (vo == NULL)
        return NULL;//Sem vô significa sem tio.
    if (no->pai == vo->esq)
        return vo->dir;
    else   
        return vo->esq;
}

node *achaVo(node *no)
{
    if ((no != NULL) && (no->pai != NULL))
        return no->pai->pai;
    else
        return NULL;
}

node *criaNo(void)//Cria um novo elemento para ser inserido. (Usada pela função push)
{
    node *novo = (node *)malloc(sizeof(node));
    if (novo == NULL){
	  printf("Não foi possível alocar memória.\n");
	  return novo;
    }
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;

    return novo;
}

node *push(node *no, int chave, node *pai)//Insere um novo nó na árvore. (deve ser chamada passando o ponteiro da raiz e o valor da chave)
{
	if(no == NULL){
		no = criaNo();
    if(no == NULL){
    	printf("Não foi possível alocar memória.\n");
    	return no;
	}
    no->chave = chave;
    no->cor = 1;
    no->pai = pai;
	}
	if (raiz == NULL)//First insertion
		raiz = no;

	if(no->chave > chave){
    	no->esq = push(no->esq, chave, no);
		pushCase1(no->esq);
		if (no->esq == NULL)
			return NULL;
	}
  	else if(no->chave < chave){
    	no->dir = push(no->dir, chave, no);
		pushCase1(no->dir);
		if (no->dir == NULL)
			return NULL;
	}
	if (no->pai == NULL)
		pushCase1(no);
	return no;
}

void pushCase1(node *no)
{
	if (no == NULL)
		return;
    if (no->pai == NULL)//Não precisa corrigir: é raiz.
        no->cor = 0;
    else                //Talvez precise corrigir.
        pushCase2(no);
}

void pushCase2(node *no)
{
    if (no->pai->cor == 0)  //Ainda não precisa corrigir, a árvore está balanceada, pois o pai é preto
        return;             //e todos os seus filho devem ser vermelhos.
    else
        pushCase3(no);
}

void pushCase3(node *no)
{
    node *tio = achaTio(no), *vo;
    if ((tio != NULL) && (tio->cor == 1)){
        no->pai->cor = 0;
        tio->cor = 0;
        vo = achaVo(no);
        vo->cor = 1;
        pushCase1(vo);
    } else 
        pushCase4(no);
}

void pushCase4(node *no)
{
    node *vo = achaVo(no);
    if ((no == no->pai->dir) && (no->pai == vo->esq)){
        rotaSimpEsq(no);
        no = no->esq;
    } else if ((no == no->pai->esq) && (no->pai == vo->dir)){
        rotaSimpDir(no);
        no = no->dir;
    }
    pushCase5(no);
}

void pushCase5(node *no)
{
    node *vo = achaVo(no);
    if((no == no->pai->esq) && (no->pai == vo->esq))
        rotaSimpDir(no);
    else//((no == no->pai->dir) && (no->pai == vo->dir))
        rotaSimpEsq(no);
    no->pai->cor = 0;
    vo->cor = 1;
}

void rotaSimpDir(node *no)
{
    node *vo = achaVo(no);
	if (no->pai == vo->dir){//Case that needs a twice rotation. 2º Case
		no->pai->pai = no;
		no->pai->esq = no->dir;
		no->esq = no->pai;
		no->pai = vo;
		vo->esq = no;
	}
	else if (no->pai == vo->esq){//Case that needs just a simple rotation. 3º Case
		no->pai->pai = vo->pai;
		vo->pai = no->pai;
		vo->esq = no->pai->dir;
		no->pai->dir = vo;
		if (no->pai->pai == NULL)
			raiz = no->pai;
	}
}
 
void rotaSimpEsq(node *no)
{
    node *vo = achaVo(no);
	if (no->pai == vo->esq){//Case that needs a twice rotation. 1º Case
		no->pai->pai = no;
		no->pai->dir = no->esq;
		no->esq = no->pai;
		no->pai = vo;
		vo->esq = no;
	}
	else if (no->pai == vo->dir){//Case that needs a simple rotation. 4º Case
		no->pai->pai = vo->pai;
		vo->pai = no->pai;
		vo->dir = no->pai->esq;
		no->pai->esq = vo;
		if (no->pai->pai == NULL)
			raiz = no->pai;
	}
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
				push(raiz, chave, NULL);
				break;
		/*case 2:	if (empty(raiz) == 1){
					printf("Não há dados a serem removidos.\n");
					break;
					}
				printf("Informe o valor da chave do nó a ser removido: \n");
				scanf("%d", &chave);
				raiz = pop(raiz, chave);
				break;*/
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
		/*case 8:	if (EhArvoreArvl(raiz) == 1)
					printf("É árvore AVL!\n");
				else
					printf("Opa! Não é árvore AVL!");
				break;*/
		case 9: clear(raiz);
				exit(0);
		default:
				printf("Informe um valor entre 1 e 9!\n");
		}
	}
}