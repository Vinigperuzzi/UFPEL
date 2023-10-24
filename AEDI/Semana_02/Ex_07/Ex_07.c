#include<stdio.h>
#include<stdlib.h>

void addInfo(void *start);
void remInfo(void *start);
void listaInfo(void *start);

typedef struct{
    char nome[10];
    int idade;
    int telefone;
} Pessoa;

Pessoa pessoas[10];

void *qtd;//Quantidade de pessoas informadas. 4ªposição do pBuffer. int

int main (void)
{
    void *pBuffer, *opSw;

    pBuffer = (Pessoa *) malloc((sizeof(int)*3) + sizeof(char));
    if (pBuffer == NULL){
        printf("Não foi possível alocar memória");
        exit(0);
    }
    qtd = pBuffer + (sizeof(int) *2) + sizeof(char);
    *(int *)qtd = 0;

    opSw = pBuffer + sizeof(int) + sizeof(char);//Operador do switch. 3ªPosição. int.
    
    for(;;){
        printf("Informe uma operação:\n\n\t1. Adicionar nome à lista\n\t2. Remover nome da lista\n\t3. Listar nomes\n\t4. Sair\n");
        scanf("%d", &(*(int *)opSw));

        switch (*(int *)opSw){
            case 1:     addInfo(pBuffer);
                        break;
            case 2:     remInfo(pBuffer);
                        break;
            case 3:     listaInfo(pBuffer);
                        break;
            case 4:     free(pBuffer);
                        exit(0);
            
            default:    printf("\nValor inválido para seleção, tente outro.\n\n");
                        break;
        }
    }
    
    return 0;
}

void addInfo(void *start)
{
    void *op, *teste;

    op = start;//operador do for. 1ªposição do pBuffer. int
    teste = op + sizeof(int);//teste do while. 2ªposição do pBuffer. char

    if(*(int *)qtd == 10)
        printf("Estrutura de dados cheia, apague alguma informação com a função 2 para inserir novas.\n");

    for (*(int *)op = *(int *)qtd; *(int *)op < 10; *(int *)op = *(int *)op + 1){
        printf("\nInforme o nome: ");
        setbuf(stdin, NULL);
        fgets(pessoas[*(int *)op].nome, 10, stdin);
        printf("\nInforme a idade: ");
        scanf("%d", &pessoas[*(int *)op].idade);
        printf("\nInforme o telefone: ");
        scanf("%d", &pessoas[*(int *)op].telefone);
        *(int *)qtd = *(int *)qtd + 1;
        printf("Deseja informar outro nome? S/N:");
        setbuf(stdin,NULL);
        scanf("%c", &(*(char *)teste));
        getchar();
        if(*(int *)qtd == 10)
            printf("Estrutura de dados cheia, apague alguma informação com a função 2 para inserir novas.\n");
        if (*(char *)teste == 'n' || *(char *)teste == 'N')
            *(int *)op = 10;
    }
}

void remInfo(void *start)
{
    if (*(int *)qtd == 0){
        printf("Não há nomes para remover\n");
    } else {
        void *ind = start + (sizeof(int) *3) + sizeof(char);//Índice para a remoção. 5ªposição do pBuffer. int.
        void *op = start;
        do{
            printf("\nInforme o índice que deseja remover, começando por 0: ");
            scanf("%d", &(*(int *)ind));
        }while (*(int *)ind < 0 || *(int *)ind > *(int *)qtd);

        for (*(int *)op = *(int *)ind; *(int *)op < *(int *)qtd; *(int *)op = *(int *)op +1){
            pessoas[*(int *)op] = pessoas[*(int *)op + 1];
        }
        *(int *)qtd = *(int *)qtd - 1;
    }
}

void listaInfo(void *start)
{
    void *op = start;

    if (*(int *)qtd == 0){
        printf("Não há dados para listar\n");
    } else{
        printf("Apresentando os dados: ");
        for (*(int *)op = 0; *(int *)op < *(int *)qtd; *(int *)op = *(int *)op + 1){
            printf("\n\n\tNome: %s\n\tIdade: %d\n\n\tTelefone: %d\n\n", pessoas[*(int *)op].nome, pessoas[*(int *)op].idade, pessoas[*(int *)op].telefone);
        }
    }
}
