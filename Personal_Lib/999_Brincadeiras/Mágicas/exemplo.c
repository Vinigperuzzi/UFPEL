#include <stdio.h>
#include <stdlib.h>

int main (void){

int var1;

printf("Informe um número: \n");
scanf("%d", &var1);
if (var1 > 10)
printf("O número digitado é: %d\n\n", var1);
else
printf("O número é menor que 10\n\n");

return 0;
}