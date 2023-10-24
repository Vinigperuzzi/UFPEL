#include<stdio.h>
#include<stdlib.h>
#define qtdQuest 50

typedef struct questao{//deve ter nome para poder usar fread, lembrar disso nas anotações
	int indice;//nesse campo da variavel 0 que ficará o indice daquele arquivo.
	char pergunta[200];
	float resposta;
	} questao;
	
questao perguntas[qtdQuest];

void insere(void);
void adiciona(void);
void reescreve(void);
void lista(void);

int main(void) {
	
	system("cls || clear");
   
   int controle;
   
   for(;;){
	printf("\n\n\t\t\tO que gostaria de fazer: \n\n\t\t\t[1.] Inserir novas informações.\n\t\t\t[2.] Adicionar informações a arquivo existente.\n\t\t\t[3.] Reescrever alguma informação em arquivo.\n\t\t\t[4.] Carregar e Listar informações de algum arquivo.\n\t\t\t[5.] Sair do programa de inserção.\n");
	scanf("%d", &controle);
	setbuf(stdin,NULL);
	
	switch (controle){
		case 1: 
					insere();
					break;
		case 2:
					adiciona();
					break;
		case 3: 
					reescreve();
					break;
		case 4: 
					lista();
					break;
		case 5:
					exit(0);
		}
	
	}
    return 0;
}


void insere(void){
	 
	FILE *arquivo;
	char nome[50], c;
	int cont1, i=0, teste=1;
   
	printf("Informe o nome do arquivo: (Arquivos pré-existentes com o mesmo nome que o informado serão excluídos)\n");
	c = getchar();
	while ((c != '\n') && (i < 200)) {
		nome[i++] = c;
		c = getchar();
	}
	nome[i] = '\0';
   
   if ((arquivo = fopen(nome, "w")) == NULL){
	   printf("Não foi possível criar o arquivo.\n");
	   return;
	  }
	  
	cont1=0;
	while (teste == 1){
		printf("Informe a pergunta que deseja adicionar: \n");
		setbuf(stdin, NULL);
		fgets(perguntas[cont1].pergunta, 200, stdin);
		printf("Informe a resposta dessa pergunta: \n");
		setbuf(stdin, NULL);
		scanf("%f", &perguntas[cont1].resposta);
		perguntas[0].indice = cont1++;
		printf("Deseja informar outra pergunta: \n[1.] Sim\n[2.] Não\n");
		scanf("%d", &teste);
	}
		 
		 fwrite(perguntas, sizeof(struct questao), qtdQuest, arquivo);
		 
		 fclose(arquivo);
}


void adiciona(void){
	 
	FILE *arquivo;
	char nome[50], c;
	int cont1, i=0, teste=1;
   
	printf("Informe o nome do arquivo para abrir: \n");
	c = getchar();
	while ((c != '\n') && (i < 200)) {
		nome[i++] = c;
		c = getchar();
	}
	nome[i] = '\0';
   
	if ((arquivo = fopen(nome, "r")) == NULL){
		printf("Não foi possível abrir o arquivo.\n");
		return;
	}
	  
	fread(perguntas, sizeof(struct questao), qtdQuest, arquivo);
	fclose(arquivo);
	
	if ((arquivo = fopen(nome, "w")) == NULL){
		printf("Não foi possível abrir o arquivo.\n");
		return;
	}
	
	  cont1=perguntas[0].indice+1;
	while (teste == 1){
		printf("Informe a pergunta que deseja adicionar: \n");
		setbuf(stdin, NULL);
		fgets(perguntas[cont1].pergunta, 200, stdin);
		printf("Informe a resposta dessa pergunta: \n");
		setbuf(stdin, NULL);
		scanf("%f", &perguntas[cont1].resposta);
		perguntas[0].indice = cont1++;
		printf("Deseja informar outra pergunta: \n[1.] Sim\n[2.] Não\n");
		scanf("%d", &teste);
	} 
	fwrite(perguntas, sizeof(struct questao), qtdQuest, arquivo);
	fclose(arquivo);
}
	


void reescreve(void){

	FILE *arquivo;
	char nome[50], c;
	int cont1, i=0, teste=1;
   
	printf("Informe o nome do arquivo para abrir: \n");
	c = getchar();
	while ((c != '\n') && (i < 200)) {
		nome[i++] = c;
		c = getchar();
	}
	nome[i] = '\0';
   
   if ((arquivo = fopen(nome, "r")) == NULL){
	   printf("Não foi possível criar o arquivo.\n");
	   return;
	 }
	  
	fread(perguntas, sizeof(struct questao), qtdQuest, arquivo);
	fclose(arquivo);
	
	if ((arquivo = fopen(nome, "w")) == NULL){
		printf("Não foi possível abrir o arquivo.\n");
		return;
	}
	
	while (teste == 1){
		printf("Informe qual o índice da pergunta que deseja mudar: \n\n");
		scanf("%d", &cont1);
		printf("Informe a pergunta que deseja adicionar: \n");
		setbuf(stdin, NULL);
		fgets(perguntas[cont1].pergunta, 200, stdin);
		printf("Informe a resposta dessa pergunta: \n");
		setbuf(stdin, NULL);
		scanf("%f", &perguntas[cont1].resposta);
		printf("Deseja informar outra pergunta: \n[1.] Sim\n[2.] Não\n");
		scanf("%d", &teste);
	} 
	fwrite(perguntas, sizeof(struct questao), qtdQuest, arquivo);
	fclose(arquivo);	
	
	return;
}

void lista(void){
	
	FILE *arquivo;
	char nome[50], c;
	int cont1, i=0;
   
	printf("Informe o nome do arquivo para abrir: \n");
	c = getchar();
	while ((c != '\n') && (i < 200)) {
		nome[i++] = c;
		c = getchar();
	}
	nome[i] = '\0';
   
	if ((arquivo = fopen(nome, "r")) == NULL){
		printf("Não foi possível abrir o arquivo.\n");
		return;
	}
	  
	fread(perguntas, sizeof(struct questao), qtdQuest, arquivo);
	fclose(arquivo);
	
	for (cont1=0; cont1<=perguntas[0].indice; cont1++){
		printf("Informação de índice %d: \n\nEnunciado: %sResposta: %.2f\n\n", cont1, perguntas[cont1].pergunta, perguntas[cont1].resposta);
	}
	
	return;	
	}
