#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define qtdQuest 50//Aumentar conforme as perguntas.

typedef struct questao{//deve ter nome para poder usar fread, lembrar disso nas anotações
	int indice;
	char pergunta[200];
	float resposta;
	} questao;
	
questao perguntas[qtdQuest];//10 Perguntas, deve ser aumentado conforme as questões forem atualizando.
int numAleat, questAleat[qtdQuest];//Gerará a ordem aleatória de ler os índices do vetor perguntas.
	
void geraAleatorio(void);
void menuTipo(void);
void escolheTipo(char nome[50]);
void jogo(int tentativas);
void imprimeResultado(int rodadas, int vitorias);

int main(void) {
	
	int cont1, operador;
	
	system("cls || clear");
	
	printf("\n\n\n\t\tSeja bem vindo ao jogo das perguntas.\n\n\n\t\tVocê terá algumas tentativas para respondê-las, e, a cada tentativa, o jogo ajudará a chegar à resposta.");
	
	for(;;) {

		geraAleatorio();
		do{
		printf("\n\n\n\t\t\tInforme em qual modo gostaria de jogar:\n\n\t\t\t[1.] Fácil (30 tentativas)\n\t\t\t[2.] Médio (15 tentativas)\n\t\t\t[3.] Díficil (8 tentativas\n\t\t\t[4.] Estou com sorte! (Apenas 1 tentativa)\n\t\t\t[5.] Sair do jogo\n");
		scanf("%d", &operador);
		if ((operador < 1 || operador > 5) && operador != 21)
			printf("\n\n\n\t\t\tVocê deve escolher uma das modalidades do menu.");
		} while ((operador < 1 || operador > 5) && operador != 21);
		
		switch (operador){
			
			case 1:
						menuTipo();
						jogo(30);
						break;
			case 2:
						menuTipo();
						jogo(15);
						break;
			case 3:
						menuTipo();
						jogo(8);
						break;
			case 4:
						menuTipo();
						jogo(1);
						break;
			case 5:
						printf("\n\n\n\t\t\tFim da reprodução.\n\n\n");
						exit(0);
						break;
			case 21:
						printf("\n\n\n\t\t\t***Parabéns! Você descobriu o modo secreto!***\n");
						menuTipo();
						jogo(999);
						break;
			}
		}
	
    return 0;
}

void geraAleatorio(void){
	
	srand(time(NULL)); //Função srand para gerar um número aleatório, time para usar a data como semente
	int ocorre, cont1, cont2;
	
	for(cont1=0; cont1<qtdQuest; cont1++)
		questAleat[cont1]=-1;
	
	for(cont1=0; cont1<qtdQuest; cont1++){
		numAleat = rand() %qtdQuest;
		ocorre=0;
		for(cont2=0; cont2<qtdQuest; cont2++){
			if(numAleat == questAleat[cont2])
				ocorre++;
		}
			if(ocorre == 0)
				questAleat[cont1] = numAleat;
			else if (ocorre != 0)
				cont1--;	
	}
}

void menuTipo(void){
	
	int operador;
	char nome1[50] = "ImpEstMunMod.txt";

	do{
	printf("\n\n\t\tSobre qual assunto você gostaria de jogar: \n\n");
	printf("\n\n\t\t\t[1.] Importantes estruturas do mundo moderno.\n\t\t\t(Menu em progresso...)\n\n");
	scanf("%d", &operador);
	setbuf(stdin,NULL);
	if (operador < 1 || operador > 1)
		printf("\n\n\n\t\t\tVocê deve escolher uma das modalidades do menu.");
	} while (operador < 1 || operador > 1);
	
	switch (operador){
		
		case 1: 
					escolheTipo(nome1);
					break;
		}
	
	return;
}
	
void escolheTipo(char nome[50]){
	
	FILE *arquivo;
	
	if ((arquivo = fopen(nome, "r")) == NULL){
		printf("\n\n\t\tErro ao encontrar esse arquivo. Verifique se o arquivo está instalado corretamente na pasta do jogo. Pressione enter para voltar ao menu.\n");
		setbuf(stdin,NULL);
		getchar();
		return;
	}
	
	fread(perguntas, sizeof(struct questao), qtdQuest, arquivo);
	fclose(arquivo);
	
	return;
	}


void jogo(int defTentativas){
	
	int tentativas;
	float resposta=0;
	int cont1, rodadas=0, vitorias=0, continuidade=0;
	
	for (cont1=0; cont1<qtdQuest; cont1++){
		rodadas++;
		tentativas = defTentativas;
		
		
		while (resposta!=perguntas[questAleat[cont1]].resposta && tentativas!=0) {
			
			if (tentativas == 999){
				printf("\n\n\n\t\t\t***A resposta certa é %.2f***\n\n\n", perguntas[questAleat[cont1]].resposta);
				tentativas++;
			}
			
			tentativas--;
			printf("\t\t%s \t\t(Chances restantes: %d)\n\n\t\tInforme um valor: \n", perguntas[questAleat[cont1]].pergunta, tentativas+1);
			scanf("%f",&resposta);
			if(resposta==perguntas[questAleat[cont1]].resposta) {
				printf("\n\n\t\t\tAcertou!\n\n");
				vitorias++;
			}
			else if(resposta>perguntas[questAleat[cont1]].resposta && tentativas != 0)
				printf("\n\n\t\t\tO número secreto é menor\n\n");
			else if(resposta<perguntas[questAleat[cont1]].resposta && tentativas != 0)
				printf("\n\n\t\t\tO número secreto é maior\n\n");
			else if(tentativas==0) 
                printf("\n\n\t\t\tPerdeu, fim de jogo.\n\t\t\tO número secreto era: %.2f",perguntas[questAleat[cont1]].resposta);
              else{
				printf("\n\n\t\t\tOpção inválida. Tentativa não computada.");
				tentativas++;
			}
		}
	
		do{
			printf("\n\n\n\t\tO que deseja fazer:\n\n\t\t\t[1.] Jogar outra pergunta nessa mesma modalidade e dificuldade (ainda resta(m) %d perguntas distintas)\n\t\t\t[2.] Voltar para o menu principal.\n", qtdQuest-(cont1+1));
			scanf("%d", &continuidade);
		} while (continuidade != 1 && continuidade != 2);
		
		if (continuidade == 2)
			cont1 = qtdQuest+1;
	}
	
	printf("\n\n\t\tPartida encerrada.");
	imprimeResultado(rodadas, vitorias);
	
	return;
	}

void imprimeResultado(int rodadas, int vitorias){
	
	if (vitorias == rodadas)
		printf("\n\n\t\tPerfeito! Você é o melhor.\n\t\tVocê jogou %d rodada(s) e teve um total de %d acerto(s)", rodadas, vitorias);
	else if (vitorias > (rodadas/2))
		printf("\n\n\t\tMuito bem! Você jogou bem.\n\t\tVocê jogou %d rodada(s) e teve um total de %d acerto(s)", rodadas, vitorias);
	else if (vitorias <= (rodadas/2) && vitorias!= 0)
		printf("\n\n\t\tQue pena! Você não jogou muito bem, mas sempre dá para tentar novamente.\n\t\tVocê jogou %d rodada(s) e teve um total de %d acerto(s)", rodadas, vitorias);
	else if (vitorias == 0)
		printf("\n\n\t\tQue péssimo! Você não acertou nenhuma da(s) %d partida(s) que jogou.", rodadas);
	
	return;
	}
