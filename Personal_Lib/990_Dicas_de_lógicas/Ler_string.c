#include <stdio.h>
#include <stdlib.h>

/*Para que consoma todo o buffer, basta retirar a
condição de tamanho no while e não passar valor de tamanho para a função.
Também deixa de ser necessária a parte responsável por consumir o buffer do teclado.
Está faltando o retorno da string para a principal!!
*/

void ler_string(char palavra[100], int tamanho)//Deve-se passar o nome da string e o tamanho a ser lido.
{
	int i = 0;
	char c;

	c = getchar();
	while ((c != '\n') && (i < tamanho)) {
		palavra[i++] = c;
		c = getchar();
	}
	palavra[i] = '\0';

	//Consome o restante do buffer caso a palavra tenha sido encerrada por tamanho.
	if (c != '\n') {
		c = getchar();
		while ((c != '\n') && (c != EOF)) {
			c = getchar();
		}
	}

}