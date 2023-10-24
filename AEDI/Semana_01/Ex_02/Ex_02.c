#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

char * AddNome(char *start);
char * RemNome(char *start);
void ListaNome(char *start);

int main()
{

    setlocale(LC_ALL, "");

    int op; 
    char *start=NULL;

    for (;;){
        printf("Informe uma operação:\n\n\t1. Adicionar nome\n\t2. Remover nome\n\t3. Listar nomes\n\t4. Sair\n");
        scanf("%d", &op);

        switch (op){
            case 1:     start = AddNome(start);
                        break;
            case 2:     start = RemNome(start);
                        break;
            case 3:     ListaNome(start);
                        break;
            case 4:     free(start);
                        exit(0);
            
            default:    printf("Valor inválido para seleção, tente outro.\n\n");
                        break;
        }
    }
    return 0;
}

char * AddNome(char *start)
{

    char *prov=NULL;
    int tam, tamstr;

    if ((prov = (char *) malloc(sizeof(char *) * 30)) == NULL){
            printf("Não foi possível alocar a memória.\n");
            return start;
        }

        printf("Informe um nome: \n");
        setbuf(stdin,NULL);
        fgets(prov, 30, stdin);
        tam = strlen(prov);

    if(start == NULL){
        if ((start = (char *) malloc((sizeof(char *) * tam) +1 )) == NULL){
            printf("Não foi possível alocar a memória.\n");
            return start;
        }

        strcpy(start, prov);
        
    } else {
        tamstr=strlen(start);

        if ((start = (char *) realloc(start, sizeof(char *) * (tamstr + tam + 1))) == NULL){
			printf("Não foi possível alocar a memória.\n");
			return start;
        }
        strcat(start, prov);
    }
    
    free(prov);
    return start;
}


char * RemNome(char *start)
{
    int ind=-1, qtdSTR=0, qtdIni=0, qtdFim=0, op, TamTot=0, TamSTR=0;
    char *ini = start, *fim = start;

    if (start != NULL){
        for(ini; *ini != '\0'; ini++)
            if (*ini == '\n')
                qtdSTR++;

        do {
            printf("Informe o índice do nome que deseja remover, começando em 0: \n");
            scanf("%d", &ind);
            if (ind < 0 || ind >= qtdSTR)
                printf("Valor inválido para o índice, tente outro valor.\n");
        } while (ind < 0 || ind >= qtdSTR);

        ini = start;

        for(op=0; op < ind; ini++){
            if (*ini == '\n')
                op++;
            qtdIni++;
        }
        
        for(op=0; op < (ind+1); fim++){
            if (*fim == '\n')
                op++;
            qtdFim++;
        }
        TamSTR = qtdFim - qtdIni;
        TamTot = strlen(start);

        for(fim; *fim != '\0';){
            *ini = *fim;
            ini++;
            fim++;
        }
        *ini = '\0';

        if (TamTot - TamSTR != 0){
            if ((start = (char *) realloc(start, sizeof(char *) * (TamTot - TamSTR))) == NULL){
                    printf("Não foi possível alocar a memória.\n");
                    return start;
                }
        }
        else{
            free(start);
            start = NULL;
        }
        return start;
    }
    else{
        printf("Não há nomes para ser removidos!\n");
        return start;
    }
}


void ListaNome(char *start)
{
 
    char *ope = start;

    printf("\n\n\t\tListando os nomes: \n\n\n");

    if (start == NULL){
        printf("Não há nomes a serem listados, você pode adicioná-los com a função 1.\n\n");
    }
    else{
        while (*ope != '\0'){
            putchar(*ope);
            ope++;
        }
    }
    printf("\n\n\n");
}