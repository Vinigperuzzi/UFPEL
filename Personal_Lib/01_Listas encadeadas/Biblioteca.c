#include<stdio.h>
#include<stdlib.h>

struct cel {
	int conteudo;
	struct cel *prox;
};

typedef struct cel celula;
void insere(int x, celula * p);
void imprime(celula * ini);
celula *busca(int x, celula * ini);
celula *cria(void);
void remova(int y, celula * ini);
void remova_end(celula * p);
void liberaLista(celula * head);
void remova_ind(int y, celula *head);

int main()//Alguns exemplos na main.
{
	celula *ini, *pos;
	ini = cria();
	insere(10, ini);
	insere(100, ini);
	insere(1000, ini);
	imprime(ini);
	pos = busca(100, ini);
	insere(99, pos);
	imprime(ini);
	remova(99, ini);
	imprime(ini);
	pos = busca(100, ini);
	remova_end(pos);
	imprime(ini);
	return 0;
}

celula *cria(void)//Retorna o endereço da cabeça que é criada pela própria função.
{
	celula *start;

	start = (celula *) malloc(sizeof(celula));
	start->prox = NULL;
	return start;
}

void insere(int x, celula * p)//Deve-se passar o(s) valor(es) do(s) conteúdo(s) a serem inseridos e a cabeça.
{
	celula *nova;

	nova = (celula *) malloc(sizeof(celula));
	nova->conteudo = x;
	nova->prox = p->prox;
	p->prox = nova;
}

void imprime(celula * ini)//Deve-se passar a cabeça.
{
	celula *p;
	for (p = ini->prox; p != NULL; p = p->prox)
		printf("%d\n", p->conteudo);
}

celula *busca(int x, celula * ini)//Retorna o endereço de determinada célula cque possui o valor informado. Deve-se informar o valor e a cabeça.
{
	celula *p;
	p = ini->prox;
	while (p != NULL && p->conteudo != x)
		p = p->prox;
	return p;
}

void remova(int y, celula * ini)//Deve-se passar o valor que está na célula que se deseja remover e a cabeça.
{
	celula *p, *q;
	p = ini;
	q = ini->prox;
	while ((q != NULL) && (q->conteudo != y)) {
		p = q;
		q = q->prox;
	}
	if (q != NULL) {
		p->prox = q->prox;
		free(q);
	}
}

void remova_end(celula * p)//Deve-se passar o endereço da célula qye se deseja remover, o que pode ser achado com a função busca
{
	celula *morta;
	morta = p->prox;
	p->prox = morta->prox;
	free(morta);
}

void liberaLista(celula * head)//Deve-se passar a cabeça da lista
{
		celula *temp;
		
		while (head != NULL){
			temp = head;
			head = head->prox;
			free(temp);
		}
}

int descobreTam(void){//Retorna o tamanho da lista

	int i=0;
	celula* temp = ini;
	while(temp != NULL) {
		i++;
		temp = temp->prox;
	}
	return i;
}


void remova_ind(int y, celula *head)//Deve-se passar o índice que se deseja remover e a cabeça da lista.
{
	int i=0;
	celula *p, *q;
	p = head;
	q = head->prox;
	while (i<y) {
		i++;
		p = q;
		q = q->prox;
	}
	if (q != NULL) {
		p->prox = q->prox;
		free(q);
	}
}