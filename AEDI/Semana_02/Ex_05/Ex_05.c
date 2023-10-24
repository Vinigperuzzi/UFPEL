#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char nome[30];
    int idade;
    int altura;
} pessoa;

typedef struct cell{
    pessoa dados;
    struct cell *prox;
} cell;

cell *cria(void);
cell *insere(cell * p);
void imprime(cell * p);
void liberaLista(cell * p);

int main (void)
{
    char teste='n';
    cell *start;

    start = cria();

    while (teste == 'n' || teste == 'N'){
        start = insere(start);
        printf("Deseja encerrar o programa? S/N: ");
        setbuf(stdin,NULL);
        teste = getchar();
        getchar();
    }

    imprime(start);
    liberaLista(start);
    return 0;
}

cell *cria(void)
{
	cell *start;

    
	start = (cell *) malloc(sizeof(cell));
    if (start == NULL){
        printf("Não foi possível alocar memória.\n");
        return start;
    }
	start->prox = NULL;
	return start;
}

cell * insere(cell * p)
{
	cell *nova = p;
    pessoa info;

    printf("\nInforme o nome da pessoa: ");
    setbuf(stdin, NULL);
    fgets(info.nome, 30, stdin);
    printf("\nInforme a idade: ");
    scanf("%d", &info.idade);
    printf("\nInforme a altura: ");
    scanf("%d", &info.altura);

	nova = (cell *) malloc(sizeof(cell));
    if (nova == NULL){
        printf("Não foi possível alocar memória.\n");
        return p;
    }
	
    strcpy(nova->dados.nome, info.nome);
    nova->dados.idade = info.idade;
    nova->dados.altura = info.altura;
	nova->prox = p->prox;
	p->prox = nova;

    return p;
}

void imprime(cell * p)
{
	cell *p1;
    int numero=1;
    printf("\n\nApresentando os dados: ");
	for (p1 = p->prox; p1 != NULL; p1 = p1->prox){
        printf("\nDados do %dº registro:\n", numero);
        numero++;
		printf("\n\tNome: %s\tIdade: %d\n\tAltura: %d\n\n", p1->dados.nome, p1->dados.idade, p1->dados.altura);
    }
}

void liberaLista(cell * p)
{
		cell *temp;
		
		while (p != NULL){
			temp = p;
			p = p->prox;
			free(temp);
		}
}