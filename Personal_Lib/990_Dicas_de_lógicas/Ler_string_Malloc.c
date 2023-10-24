#include<stdio.h>

char* ler_string(char *palavra);

int main (void){
    char *palavra;
    printf("Informe o nome da pessoa: ");
    palavra = ler_string(palavra);
    printf("%s\n", palavra);
}


char* ler_string(char *palavra)//Recebe apenas o ponteiro do nome que será lido e retorna o endereço do nome (Pode mudar por conta do realloc)
{
    if ((palavra = (char*)malloc(sizeof(char))) == NULL){
        printf("\nProblema na hora de alocar o espaço para ler a palavra.\n");
        return NULL;
    }
	int i = 0;
	char c;

	c = getchar();
	while (c != '\n'){
		palavra[i] = c;
        i++;
        if ((palavra = (char*)realloc(palavra, (sizeof(char) * (i+1)))) == NULL){
            printf("\nProblema na hora de realocar o espaço para ler a palavra.\n");
            return NULL;
        }
		c = getchar();
	}
	palavra[i] = '\0';

    return palavra;

}