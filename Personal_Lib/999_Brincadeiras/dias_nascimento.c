#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
 time_t mytime; // função time
 mytime=time(NULL);
 struct tm tm = *localtime(&mytime);


 int dianas, mesnas, anonas, diasbi, dimenas, ditonas, op, diasho, anosho, diasbiho, ditoho, r;
    
    diasho = tm.tm_yday;
    anosho = tm.tm_year+1900;
    diasbiho = anosho/4;
    ditoho = (anosho*365) + diasho + diasbiho;
    
    
    
    printf("Esse programa tem a função de \ndetectar quantos dias o \nusuário viveu até hoje\n");
    printf("\nDigite o dia de nascimento:\n");
    scanf("%d",&dianas);
    printf("\nDigite o mês do nascimento:\n");
    scanf("%d",&mesnas);
    printf("\nDigite o ano do nascimento:\n");
    scanf("%d",&anonas);
    
    diasbi = anonas/4;
    
    if(mesnas == 01 | mesnas == 02 | mesnas == 03 | mesnas == 04 | mesnas == 05 | mesnas == 06 | mesnas == 07){
    op = mesnas;}
    else
    op = mesnas + 2;
    
    switch (op){
    
    case 01:
    dimenas = 0;
    break;
    
    case 02:
    dimenas = 31;
    break;
    
    case 03:
    dimenas = 59;
    break;
    
    case 04:
    dimenas = 90;
    break;
    
    case 05:
    dimenas = 120;
    break;
    
    case 06:
    dimenas = 151;
    break;
    
    case 07:
    dimenas = 181;
    break;
    
    case 10:
    dimenas = 212;
    break;
    
    case 11:
    dimenas = 243;
    break;
    
    case 12:
    dimenas = 273;
    break;
    
    case 13:
    dimenas = 304;
    break;
    
    case 14:
    dimenas = 334;
    break;
    
    default :
            printf("Programa encerrado");
            break;
            
    }
            
    ditonas = (anonas * 365) + dimenas + diasbi + dianas;
   
   r = ditoho - ditonas;
   if(r >= 0){
   printf("\nVocê está a %d dias vivendo \nnesse maravilhoso mundo cheio de \nprogramação\n\n",r);
   } else {
   r = r*(-1);
   printf("\nIsso é impossível! ainda faltam %d dias para você nascer\n\n",r);
}
    return 0;
}