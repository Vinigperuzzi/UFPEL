#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void){

    int meses, cont;
    float valorIni, juros;

    printf("Informe a quantidade de meses: \n");
    scanf("%d", &meses);

    float indIGP[meses], abatimento[meses];

    for (cont = 0; cont < meses; cont++){
        printf("Informe o índice IGP do %dº mês: \n", cont+1);
        scanf("%f", &indIGP[cont]);
        printf("Informe o abatimento: \n");
        scanf("%f", &abatimento[cont]);
    }

    printf("Informe o valor inicial: \n");
    scanf("%f", &valorIni);

    printf("Informe o juros: \n");
    scanf("%f", &juros);

    for (cont = 0; cont < meses; cont++){
        valorIni = (valorIni - abatimento[cont]) + (valorIni*(juros/100)) + (valorIni*(indIGP[cont]/100));
    }

    printf("O valor ao final de %d meses é: %.2f\n\n", meses, valorIni);
    return 0;
}