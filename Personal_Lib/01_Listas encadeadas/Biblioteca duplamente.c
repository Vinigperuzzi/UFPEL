#include<stdio.h>
#include<stdlib.h>

struct cel  {
	int conteudo;
	struct cel* prox;//Ponteiro para a próxima célula
	struct cel* ant;//Ponteiro para a célula anterior
};
typedef struct cel celula;
celula* ini; // ponteiro para a célula da cabeça, trabalhando a escopo global.

/*Protótipo das funções*/
celula* cria(int x);
void insereIni(int x);
void insereFim(int x);
void remova(int y);
void imprime(void);
void imprimeCont(void);
void liberaLista(void);
int descobreTam(void);

int main() {
	ini = NULL; //Iniciando o ponteiro que será a cabeça. Lembrando que a escopo global.
	int escolha, valor;

	for(;;){
		printf("\n\n\t\t===>Menu<===\n\n\t\tInforme qual operação deseja fazer: \n\t\t[1] Criar uma nova célula no início da lista\n\t\t[2] Criar uma nova célula no final da lista\n\t\t[3] Imprimir a lista em ordem avante\n\t\t[4] Imprimir a lista em ordem regressiva\n\t\t[5] Excluir algum elemento da lista\n\t\t[6] Sair\n");
		scanf("%d", &escolha);
		
		switch (escolha)
		{
			case 1:
				printf("Informe o valor que deseja adicionar ao início da lista:\n");
				scanf("%d", &valor);
				insereIni(valor);
				break;
			case 2:
				printf("Informe o valor que deseja adicionar ao final da lista:\n");
				scanf("%d", &valor);
				insereFim(valor);
				break;
			case 3:
				imprime();
				break;
			case 4:
				imprimeCont();
				break;
			case 5:
				printf("Informe o índice do valor que deseja remover, começando por 0:\n");
				scanf("%d", &valor);
				while (valor < 0){
					printf("O índice deve ser um valor positivo! Informe novamente: \n");
					scanf("%d", &valor);
				}
				remova(valor);
				break;
			case 6:
				liberaLista();
				exit(0);
				break;
			default:
				printf("Número digitado inválido para a seleção de menu, tente novamente.\n");
			
			}

	}
	liberaLista();
	return 0;
}


/*Essas funções não são passadas com o índice da cabeça pois nesses casos foram trabalhadas com a cabeça a escopo global
Porém, caso seja trabalhado com escopo local, cada função deve receber o ponteiro que aponta para a célula da cabeça*/


//Função que cria uma nova célula e retorna um ponteiro para ela. 
celula* cria(int x) //Deve-se passar um ou mais valores para serem indexados em seus campos. Retorna o endereço da célula criada: agora a cabeça.
{
	celula* start;
	start = (celula*)malloc(sizeof(celula));
	start->conteudo = x;
	start->ant = NULL;
	start->prox = NULL;
	return start;
}

//Função que insere uma célula no início da lista, tornando-se a cabeça.
void insereIni(int x)//Deve-se passar um ou mais valores para serem indexados em seus campos, valor o qual será passado para a cria.
{
	celula* start = cria(x);
	if(ini == NULL) {
		ini = start;
		return;
	}
	ini->ant = start;
	start->prox = ini;
	ini = start;
}

//Insere uma célula no final da lista, tornando-se a última.
void insereFim(int x) //Deve-se passar um ou mais valores para serem indexados em seus campos, valor o qual será passado para a cria.
{
	celula* temp = ini;
	celula* start = cria(x);
	if(ini == NULL) {
		ini = start;
		return;
	}
	while(temp->prox != NULL) temp = temp->prox;
	temp->prox = start;
	start->ant = temp;
}

//Remove a célula cujo índice foi passado.
void remova(int y) //Deve-se passar o índice da célula que se deseja remover.
{
	int i=0, tam;
	celula *o, *p, *q;
	tam = descobreTam();//Descobre o tamanho da lista, para o caso especial de o elemento ser o único.
	if (tam == 0){
		printf("Não há elementos para serem excluídos \n");//Caso não haja elementos para serem excluídos, apenas volta para a função principal.
		return;
	}
	p = ini;
	o = p->ant;
	q = p->prox;
	while (i<y && p != NULL) {
		i++;
		o = p;
		p = p->prox;
		if(q != NULL)
			q = q->prox;
	}
	if (p != NULL) {
		if(i==0 && tam != 1){
			ini = q;
			q->ant = p->ant;
			free(p);
		} else if(q == NULL && tam != 1){
			o->prox = p->prox;
			free(p);
		} else if (tam == 1){
			free(p);
			ini=NULL;
		}else{
			o->prox = p->prox;
			q->ant = p->ant;
			free(p);
		}
	} else
		printf("Índice inválido para remoção");
}


//Imprime todos os elementos em ordem avante.
void imprime(void)
{
	celula* temp = ini;
	printf("\n\nLista em ordem avante: ");
	while(temp != NULL) {
		printf("%d ",temp->conteudo);
		temp = temp->prox;
	}
	printf("\n");
}

//Imprime todos os elementos em ordem reversa. 
void imprimeCont(void) 
{
	celula* temp = ini;
	if(temp == NULL) return;
	while(temp->prox != NULL) {
		temp = temp->prox;
	}
	printf("\n\nLista em ordem reversa: ");
	while(temp != NULL) {
		printf("%d ",temp->conteudo);
		temp = temp->ant;
	}
	printf("\n");
}


//Libera todos os elementos da lista
void liberaLista(void)
{
	celula *temp;
	
	while (ini != NULL){
		temp = ini;
		ini = ini->prox;
		free(temp);
	}
}

//Descobre o tamanho da lista
int descobreTam(void)//Retorna o tamanho da lista
{

	int i=0;
	celula *temp = ini;
	while(temp != NULL) {
		i++;
		temp = temp->prox;
	}
	return i;
}