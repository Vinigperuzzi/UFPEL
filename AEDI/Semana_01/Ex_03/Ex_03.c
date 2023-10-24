#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void * AddInfo(void *start);
void * RemInfo(void *start);
void BuscaInfo(void *start);
void ListaInfo(void *start);

typedef struct agen{
char nome[10];
int idade;
int telefone;
} agenda;

int nPessoas=0;

int main(){

    void *pBuffer=NULL;
    int op;

    for (;;){
        printf("Informe uma operação:\n\n\t1. Adicionar nome à lista\n\t2. Remover nome da lista\n\t3. Buscar nome na lista\n\t4. Listar nomes\n\t5. Sair\n");
        scanf("%d", &op);

        switch (op){
            case 1:     pBuffer = AddInfo(pBuffer);
                        break;
            case 2:     pBuffer = RemInfo(pBuffer);
                        break;
            case 3:     BuscaInfo(pBuffer);
                        break;
            case 4:     ListaInfo(pBuffer);
                        break;
            case 5:     free(pBuffer);
                        exit(0);
            
            default:    printf("Valor inválido para seleção, tente outro.\n\n");
                        break;
        }
    }

    return 0;
}

void * AddInfo(void *start){

    void *ind = start;
    agenda temp;
    nPessoas++;

    printf("Informe o nome: \n");
    setbuf(stdin,NULL);
    fgets(temp.nome, 10, stdin);
    printf("Informe a idade: \n");
    setbuf(stdin,NULL);
    scanf("%d", &temp.idade);
    printf("Informe o telefone: \n");
    scanf("%d", &temp.telefone);

    if(start == NULL){
        if ((start = (void *) malloc((sizeof(agenda)) + sizeof(int))) == NULL){
            printf("Não foi possível alocar a memória.\n");
            nPessoas--;
            return start;
        }
        *(int *)start = nPessoas;

    } else {
        if ((start = (void *) realloc(start, ((sizeof(agenda) * nPessoas) + sizeof(int)))) == NULL){
			printf("Não foi possível alocar a memória.\n");
            nPessoas--;
			return start;
        }
    }

    ind = start;
    *(int *)ind = nPessoas;
    ind = ind + (sizeof(int)) + (sizeof(agenda) * (nPessoas-1));
    *(agenda *)ind = temp;

    return start;
}


void * RemInfo(void *start){
    int position, cont;
    void *ini = start, *fim = start;
    agenda temp;

    if (nPessoas != 0){
        nPessoas--;
        do{
            printf("Informe a posição que deseja remover, começando por 0: \n");
            scanf("%d", &position);
            if (position < 0 || position > nPessoas)
                printf("Índice inválido para operação.\n");
        }while (position < 0 || position > nPessoas);
        ini = ini +(sizeof(int)) + (sizeof(agenda) * (position));
        fim = ini + sizeof(agenda);

        for (cont=position; cont < nPessoas; cont++){
            *(agenda *)ini = *(agenda *)fim;
            ini = ini + sizeof(agenda);
            fim = fim + sizeof(agenda);
        }   
        
        *(int *)start = nPessoas;

        if ((start = (void *) realloc(start, ((sizeof(agenda) * nPessoas) + sizeof(int)))) == NULL){
			printf("Não foi possível alocar a memória.\n");
			return start;
        }
    } else
        printf("Não há mais contatos a serem removidos.\n");
    
    return start;
}


void BuscaInfo(void *start){

    void *ini = start + sizeof(int);
    int cont, op, telefone, ocorre=0;
    agenda temp;
    char nome[10];

    if(start != NULL){
        do{
        printf("Por qual paramêtro deseja buscar: \n1. Nome\n2. Telefone\n");
        scanf("%d", &op);
        if (op != 1 && op != 2)
            printf("Digite um dos dois valores válidos.\n");
        } while (op != 1 && op != 2);

        switch (op){
            case 1: printf("Informe o nome que deseja buscar: \n");
                    setbuf(stdin, NULL);
                    fgets(nome, 10, stdin);

                    printf("Contatos encontrados: \n");
                    for (cont=0; cont < nPessoas; cont++){
                        temp = *(agenda *)ini;
                        if (strcmp (temp.nome, nome) == 0){
                            printf("\n\t\t%dº Contato:\n\tNome: %s", cont+1, temp.nome);
                            if (strlen(temp.nome) == 9 && temp.nome[8] != '\n')
                                printf("\n");
                            printf("\tIdade: %d.\n\tTelefone: %d.\n\n", temp.idade, temp.telefone);
                            ocorre++;
                        }
                        ini = ini + sizeof(agenda);
                    }
                    if (ocorre == 0)
                        printf("Nenhuma ocorrência encontrada");
                    break;
            case 2: printf("Informe o número de telefone que deseja encontrar: \n");
                    scanf("%d", &telefone);
                    
                    printf("Contatos encontrados: \n");
                    for (cont=0; cont < nPessoas; cont++){
                        temp = *(agenda *)ini;
                        if (temp.telefone == telefone){
                            printf("\n\t\t%dº Contato:\n\tNome: %s", cont+1, temp.nome);
                            if (strlen(temp.nome) == 9 && temp.nome[8] != '\n')
                                printf("\n");
                            printf("\tIdade: %d.\n\tTelefone: %d.\n\n", temp.idade, temp.telefone);
                            ocorre++;
                        }
                        ini = ini + sizeof(agenda);
                    }
                    if (ocorre == 0)
                        printf("Nenhuma ocorrência encontrada");
                    break;
        }
    } else{
        printf("Não há dados a serem buscados");
    }
}

void ListaInfo(void *start){
    
    void *ini = start;
    int cont;
    agenda temp;
    ini = ini + sizeof(int);

    for(cont=0; cont < nPessoas; cont++){
        temp = *(agenda *)ini;
        printf("\n\t\t%dº Contato:\n\tNome: %s", cont+1, temp.nome);
        if (strlen(temp.nome) == 9 && temp.nome[8] != '\n')
            printf("\n");
        printf("\tIdade: %d.\n\tTelefone: %d.\n\n", temp.idade, temp.telefone);
        ini = ini + sizeof(agenda);
    }
}