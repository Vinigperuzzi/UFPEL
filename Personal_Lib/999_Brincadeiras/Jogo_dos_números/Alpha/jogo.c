#include<stdio.h>

int main()
{
int x, y, z, op;

printf("escolha um nível de dificuldade\n(1): Fácil\n(2): Médio\n(3): Difícil:\n");
scanf("%d",&op);
switch (op) {

case 1 :
y=10;
while (y!=0 & x!=11){ y--;
    z=y+1;
    printf("Escolha um número de 1 a 20\n%d chances restante(s)\n",z);
    scanf("%d",&x);
    if(x==11){
    printf("Acertou!");
    }
    if(x>11){
    printf("O número secreto é menor\n");
    }
    if(x<11){
    printf("O número secreto é maior\n");
    }
    }
    if(y==0){
    printf("Perdeu, fim de jogo");
    }
    break;
    
    
    case 2 :
    y=5;
    while (y!=0 & x!=11){ y--;
    z=y+1;
    printf("Escolha um número de 1 a 20\n%d chances restante(s)\n",z);
    scanf("%d",&x);
    if(x==11){
    printf("Acertou!");
    }
    if(x>11){
    printf("O número secreto é menor\n");
    }
    if(x<11){
    printf("O número secreto é maior\n");
    }
    }
    if(y==0){
    printf("Perdeu, fim de jogo");
    }
    break;
    
    
    case 3 :
    y=5;
    while (y!=0 & x!=11){ y--;
    z=y+1;
    printf("Escolha um número de 1 a 100\n%d chances restante(s)\n",z);
    scanf("%d",&x);
    if(x==11){
    printf("Acertou!");
    }
    if(x>11){
    printf("O número secreto é menor\n");
    }
    if(x<11){
    printf("O número secreto é maior\n");
    }
    }
    if(y==0){
    printf("Perdeu, fim de jogo");
    }
    break;
    }
    return 0;
}