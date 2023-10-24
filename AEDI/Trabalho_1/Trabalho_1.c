#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void* criaHead(void);
void addInfo(void *pBuffer);
void addDados(void *nova);
void remInfo(void *pBuffer);
void buscaInfo(void *pBuffer);
void listaInfo(void *pBuffer);
void liberaLista(void *pBuffer);

int main(){

    void *pBuffer=NULL;

    pBuffer = criaHead();

    for (;;){
        printf("\n\nInforme uma operação:\n\n\t1. Adicionar nome à lista\n\t2. Remover nome da lista\n\t3. Buscar nome na lista\n\t4. Listar nomes\n\t5. Sair\n");
        scanf("%d", &(*(int *)(pBuffer + (sizeof(void *) * 2) + (sizeof(int)))));

        switch (*(int *)(pBuffer + (sizeof(void *) * 2) + (sizeof(int)))){
            case 1:     addInfo(pBuffer);
                        break;
            case 2:     remInfo(pBuffer);
                        break;
            case 3:     buscaInfo(pBuffer);
                        break;
            case 4:     listaInfo(pBuffer);
                        break;
            case 5:     liberaLista(pBuffer);
                        free(pBuffer);
                        exit(0);
            
            default:    printf("Valor inválido para seleção, tente outro.\n\n");
                        break;
        }
    }

    return 0;
}

void* criaHead(void)
{
    void *pBuffer;

	pBuffer = (void *)malloc((sizeof(int)*2) + (sizeof(void *) * 2) + (sizeof(char) * 10));
    if (pBuffer == NULL){
        printf("\nNão foi possível alocar memória. Reinicie o programa.\n");
        exit(0);
    }
    *(int *)(pBuffer + (sizeof(void *) * 2)) = 0;//Iniciando o qtd como 0
    *(void **)(pBuffer) = NULL;
    *(void **)(pBuffer + sizeof(void *)) = NULL;

    return pBuffer;
}


void addInfo(void *pBuffer)
{
    void *nova, *novaPessoa, *novaPessoaAnt;//nova cria a nova célula e novaPessoa percorrerá as células.

    nova = (void *)malloc((sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *) * 2));
    if(nova == NULL){
        printf("Impossível alocar memória.\n");
        return;
    }

    *(void **)(pBuffer + (sizeof(void *) * 2)) = *(void **)(pBuffer + (sizeof(void *) * 2)) + (int)1;//Incrementa a quantidade
    addDados(nova);//Chama a função que faz a alocação dos dados no buffer das informações

    if (*(int *)(pBuffer + (sizeof(void *) * 2)) == 1){//Caso seja a primeira célula inserida(1ªimg)
        *(void **)(pBuffer) = nova;
        *(void **)(pBuffer + sizeof(void *)) = nova;//Aponta os endereços da primeira e da última para a célula criada
        *(void **)(nova + (sizeof(char) * 10) + (sizeof(int) * 2)) = NULL;
        *(void **)(nova + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))) = NULL;//Anterior e posterior NULL
    } else{//Caso seja as demais
        novaPessoa = *(void **)(pBuffer);//Começa na primeira célula com valor.
        while ((strcasecmp((char *)(nova), (char *)(novaPessoa)) >= 0) && (*(void **)(novaPessoa + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))) != NULL)){//Avança enquanto o nome for maior(dic.) que o da célula do banco de dados OU até o final da lista.
            novaPessoa = *(void **)(novaPessoa + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *)));
        }
        if ((*(void **)(novaPessoa + (sizeof(char) * 10) + (sizeof(int) * 2)) == NULL) && (strcasecmp((char *)(nova), (char *)(novaPessoa)) <= 0)){//Caso seja a posição 1 com outras incluídas(2ªimg), if anterior é NULL
            *(void **)(pBuffer) = nova;//head.primeira aponta para essa célula criada
            *(void **)(nova + (sizeof(char) * 10) + (sizeof(int) * 2)) = NULL;//CélulaCriada.ant aponta para NULL.
            *(void **)(nova + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))) = novaPessoa;//CélulaCriada.prox aponta para a que era a primeira até então.
            *(void **)(novaPessoa + (sizeof(char) * 10) + (sizeof(int) * 2)) = nova;//A que era a primeira aponta para a que foi criada.
        } else if((strcasecmp((char *)(nova), (char *)(novaPessoa)) >= 0) && (*(void **)(novaPessoa + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))) == NULL)){//Percorreu toda a lista, ou seja é maior(dic.) que todos(img3).
            novaPessoa = *(void **)(pBuffer + sizeof(void *));//Posicionando o novaPessoa na última célula.
            *(void **)(pBuffer + sizeof(void *)) = nova;//head.último aponta para essa célula criada
            *(void **)(nova + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))) = NULL;//CélulaCriada.prox aponta para NULL.
            *(void **)(nova + (sizeof(char) * 10) + (sizeof(int) * 2)) = novaPessoa;//CélulaCriada.ant aponta para a que era última.
            *(void **)(novaPessoa + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))) = nova;//A que era última aponta para a que foi criada
        } else {//Qualquer outro caso que não vá ocupar o primeiro ou o último lugar da fila(img4).
            novaPessoaAnt = *(void **)(novaPessoa + (sizeof(char) * 10) + (sizeof(int) * 2));//Colocando um ponteiro para apontar para a célula anterior e outra para o posterior da célula que se quer ordenar.
            *(void **)(nova + (sizeof(char) * 10) + (sizeof(int) * 2)) = novaPessoaAnt;//CélulaCriada.ant recebe a célula anterior na ordem
            *(void **)(nova + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))) = novaPessoa;//CélulaCriada.Prox recebe a célula posterior na ordem.
            *(void **)(novaPessoaAnt + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *))) = nova;//O endereço próx da célula anterior recebe a célula nova.
            *(void **)(novaPessoa + (sizeof(char) * 10) + (sizeof(int) * 2)) = nova;//O endereço ant da célula posterior recebe a célula nova.
        }
    }
    
}

void addDados(void *nova)//Indexa cada informação de cada pessoa no seu respectivo buffer.
{
    printf("Informe o nome da pessoa: \n");
    setbuf(stdin,NULL);
    scanf("%10s", &(*(char *)nova));
    printf("Informe a idade: \n");
    scanf("%d", &(*(int *)(nova + (sizeof(char) * 10))));
    printf("Informe o telefone: \n");
    scanf("%d", &(*(int *)(nova + (sizeof(char) * 10) + sizeof(int))));

}


void remInfo(void *pBuffer)
{

    void *temp, *prox;

    if (*(int *)(pBuffer + (sizeof(void *) * 2)) == 0){
        printf("\nNão há mais dados a serem removidos.\n\n");
    } else if (*(int *)(pBuffer + (sizeof(void *) * 2)) == 1){
        *(void **)(pBuffer + (sizeof(void *) * 2)) = *(void **)(pBuffer + (sizeof(void *) * 2)) - (int)1;
        temp = *(void **)(pBuffer);
        free(temp);
        printf("\nPrimeira célula de dados da fila removida com sucesso!\n\n");
    } else {
        *(void **)(pBuffer + (sizeof(void *) * 2)) = *(void **)(pBuffer + (sizeof(void *) * 2)) - (int)1;
        temp = *(void **)(pBuffer);
        prox = *(void **)(temp + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *)));
        *(void **)(pBuffer) = prox;
        *(void **)(prox + (sizeof(char) * 10) + (sizeof(int) * 2)) = NULL;
        free(temp);
        printf("\nPrimeira célula de dados da fila removida com sucesso!\n\n");
    }
    return;
}
void buscaInfo(void *pBuffer)
{
    void *buscaPessoa = *(void **)(pBuffer), *prnt;

    if (*(void **)(pBuffer + (sizeof(void *) * 2)) == 0){
        printf("\nNão há informações para serem buscadas.\n");
    } else {
        printf("\nInforme o nome para buscar: \n");
        setbuf(stdin,NULL);
        scanf("%10s", &(*(char *)(pBuffer + (sizeof(void *) * 2) + (sizeof(int) * 2))));

        printf("\n\n\t\tDados encontrados: \n");
        while (buscaPessoa != NULL){
            if (strcasecmp((char *)(pBuffer + (sizeof(void *) * 2) + (sizeof(int) * 2)) , (char *)(buscaPessoa)) == 0){
                prnt = buscaPessoa;
                printf("\n\t\tNome: ");
                while (*(char *)prnt != '\0'){
                    putchar(*(char *)prnt);
                    prnt = prnt + sizeof(char);
                }
                printf("\n\t\tIdade: %d", *(int *)(buscaPessoa + (sizeof(char) * 10)));
                printf("\n\t\tTelefone: %d\n", *(int *)(buscaPessoa + (sizeof(char) * 10) + sizeof(int)));
            }
            buscaPessoa = *(void **)(buscaPessoa + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *)));
        }
    }
    return;
}


void listaInfo(void *pBuffer)
{
    if (*(int *)(pBuffer + (sizeof(void *) * 2)) == 0){
        printf("\nNão há informações a serem mostradas.\n");
    } else{
        void *novaPessoa, *prnt;
        novaPessoa = *(void **)(pBuffer);
        printf("\n\t\tExibindo o banco de dados: \n");
        while (novaPessoa != NULL){
            prnt = novaPessoa;
            printf("\n\t\tNome: ");
            while (*(char *)prnt != '\0'){
                putchar(*(char *)prnt);
                prnt = prnt + sizeof(char);
            }
            printf("\n\t\tIdade: %d", *(int *)(novaPessoa + (sizeof(char) * 10)));
            printf("\n\t\tTelefone: %d\n", *(int *)(novaPessoa + (sizeof(char) * 10) + sizeof(int)));
            novaPessoa = *(void **)(novaPessoa + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *)));
        }
        printf("\n\n\t\tFim dos dados.\n");
    }
}

void liberaLista(void *pBuffer)
{
	void *temp, *node = *(void **)(pBuffer);
    while (node != NULL){
        temp = node;
        node = *(void **)(node + (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void *)));
        free(temp);
    }
}