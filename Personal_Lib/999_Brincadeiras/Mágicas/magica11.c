#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int main(){
	
	system ("cls || clear");
	
	printf("\n\n\n\t\t\tPermita-me mostrar como o mundo da computação pode ser mágico.\n\n\n\t\t\tE para isso, vou fazer uma mágica para você.\n\n\n\t\t\tVamos lá!!!");
	
    srand(time(NULL)); //Função srand para gerar um número aleatório, time para usar a data como semente
	int numero, numeros[33], grade[11][3], cont1, cont2, cont3, contCase, repete, escolha, numeroCerto, mentira;
	
	for(cont1=0; cont1<33; cont1++)
		numeros[cont1] = -1;

    for(cont1=0; cont1<33; cont1++){
		repete=0;
        numero=rand() %100;
        for(cont2=0; cont2<33; cont2++){
			if (numero == numeros[cont2])
				repete++;
		}
		if(repete == 0)
			numeros[cont1] = numero;
		else
			cont1--;
     }
     

    for (contCase=0; contCase<4; contCase++){
		cont3=0;
		for(cont1=0; cont1<11; cont1++){
			for(cont2=0; cont2<3; cont2++){
			grade[cont1][cont2] = numeros[cont3];
			cont3++;
			}
		}
     
		if(contCase==0)
			printf("\n\tEscolha um número e informe em qual coluna ele está.\n\n");
		else if (contCase==1)
			printf("\n\n\n\tE agora? Em qual coluna seu número está?\n\n");
		else if (contCase==2)
			printf("\n\n\n\tMais uma vez. Em qual coluna seu número está?\n\n");
		else if (contCase==3)
			printf("\n\n\n\tAgora pela última vez.\n\n");
			
			    printf("\n\n\t\tColuna 1\tColuna 2\tColuna 3\n\n");
     
		cont3=0;
		for(cont1=0; cont1<11; cont1++){
			for(cont2=0; cont2<3; cont2++){
				printf("\t\t   %d", numeros[cont3]);
				cont3++;
			}
			printf("\n\n");
		}
		
		do{
		scanf("%d", &escolha);
		if (escolha < 1 || escolha > 3)
			printf("Não. Você não entendeu, é para digitar o número da coluna em que seu número está.\n");
		}while (escolha < 1 || escolha > 3);
		
		switch (escolha){
			case 1: cont3=0;
						for (cont1=0; cont1<11; cont1++){
							numeros[cont3] = grade[cont1][1];
							cont3++;
						}
						for (cont1=0; cont1<11; cont1++){
							numeros[cont3] = grade[cont1][0];
							cont3++;
						}
						for (cont1=0; cont1<11; cont1++){
							numeros[cont3] = grade[cont1][2];
							cont3++;
						}
						break;
			case 2: cont3=0;
						for (cont1=0; cont1<11; cont1++){
							numeros[cont3] = grade[cont1][0];
							cont3++;
						}
						for (cont1=0; cont1<11; cont1++){
							numeros[cont3] = grade[cont1][1];
							cont3++;
						}
						for (cont1=0; cont1<11; cont1++){
							numeros[cont3] = grade[cont1][2];
							cont3++;
						}
						break;
			case 3: cont3=0;
						for (cont1=0; cont1<11; cont1++){
							numeros[cont3] = grade[cont1][0];
							cont3++;
						}
						for (cont1=0; cont1<11; cont1++){
							numeros[cont3] = grade[cont1][2];
							cont3++;
						}
						for (cont1=0; cont1<11; cont1++){
							numeros[cont3] = grade[cont1][1];
							cont3++;
						}
						break;
			default: break;
		}
	}
	
	numeroCerto = numeros[16];
	
	printf("\n\n\n\t\t\t\tHummmm. Interessante! Eu já sei o seu número, mas vamos deixar isso ainda mais legal?\n\n\t\t\t\tEscolha seu número, mas sem vê-lo.\n\n\t\t\t\tVamos dividir esses números em 11 grupos de 3.\n\n\t\t\t\tVamos descartar alguns, você gostaria de manter. (1.) Os 5 primeiros ou (2.) Os 5 últimos:  \n\n");
	
	for(cont1=0; cont1<11; cont1++)
			printf("\n\n\t\t\tGrupo: %d\t\t\tX X X ", cont1+1);
	printf("\n");
	
	do{
		scanf("%d", &mentira);
	}while (mentira != 1 && mentira != 2);
	printf("\n\n\t\t\tNúmeros descartados: \n\t\t\t");
	for(cont1=0; cont1<15; cont1++)
		printf("%d ", numeros[cont1]);
	printf("\n");
	
	printf("\n\n\n\t\t\t\tNossa, que arriscado! Creio que o seu número não foi descartado, né? Vamos seguir.\n\n\t\t\t\tAinda temos 6 grupos com 3 números cada. Escolha 2 dos 6 para ser descartado. (1.) Os 2 primeiros, (2.) Os 2 intermediários ou (3.) Os dois últimos: \n\n");
	
	for(cont1=0; cont1<6; cont1++)
			printf("\n\n\t\t\tGrupo: %d\t\t\tX X X ", cont1+1);
	printf("\n");
	
	do{
		scanf("%d", &mentira);
	}while(mentira < 1 || mentira > 3);
	printf("\n\n\t\t\tNúmeros descartados: \n\t\t\t");
	for(cont1=18; cont1<24; cont1++)
		printf("%d ", numeros[cont1]);
	printf("\n");
	
	printf("\n\n\n\t\t\tFala sério! Isso tá cada vez ficando mais emocionante, tá sentinto o mesmo?.Vamos mais uma vez.\n\t\t\tAgora restam 2 grupos de 6 números cada. Dessa vez, escolha um deles para ser mantido: \n\n");		
		
		for(cont1=0; cont1<2; cont1++)
			printf("\n\n\t\t\tGrupo: %d\t\t\tX X X X X X X", cont1+1);
		printf("\n");
		
		do{
			scanf("%d", &mentira);
		}while(mentira != 1 && mentira != 2);
		printf("\n\n\t\t\tNúmeros descartados, obviamente os que não estavam no grupo escolhido: \n\t\t\t");
		for(cont1=24; cont1<30; cont1++)
			printf("%d ", numeros[cont1]);
		printf("\n");
		
	printf("\n\n\n\t\t\tChegou a hora da verdade!!! Escolha uma entre os 6 números restantes: \n");
	
	printf("\n\n\t\tX X X X X X ");
	printf("\n");
	
	do{
		scanf("%d", &mentira);
	}while(mentira < 1 || mentira > 6);
	printf("\n\n\t\t\tNúmeros descartados, os que não são o escolhido: \n\t\t\t");
	printf("%d %d %d %d e %d", numeros[9], numeros[11], numeros[30], numeros[31], numeros[32]);
	
	printf("\n\n\n\t\t\t\tE por fim...\n\n\t\t\t\tSeu número é........\n\n\n\t\t\t\t\t%d.\n\n\n", numeroCerto);
    return 0;
}
