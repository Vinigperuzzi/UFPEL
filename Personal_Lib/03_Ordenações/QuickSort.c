#include <stdio.h>
#include<time.h>

void quicksort (int vetor[], int left, int right);

void quicksort (int vetor[], int left, int right)//Recebe o vetor e o primeira e última posição(índice) do vetor.
{
    srand(time(0));

    int mid, tmp, cont1, cont2, chave; 

    cont1 = left; 
    cont2 = right; 

    /*mid = vetor[(left + right)/2];/Para pegar o elemento central como pivô*/
    /*mid = vetor[cont2]//Para pegar o elemento mais à direita como pivô*/

    chave = rand() %(right-left);
    mid = vetor[left + chave];//Para pegar um pivô aleatório toda vez.

    do { 
        while(vetor[cont1] < mid) 
            cont1++; 
        while(mid < vetor[cont2]) 
            cont2--; 
        if (cont1 <= cont2) { 
            tmp = vetor[cont1]; 
            vetor[cont1] = vetor[cont2]; 
            vetor[cont2] = tmp; 
            cont1++; 
            cont2--; 
        }
    } while (cont1 <= cont2); 
    if (left < cont2) 
        quicksort(vetor, left, cont2); 
    if (cont1 < right) 
        quicksort(vetor, cont1, right); 
}

int main (void)
{
    int n;
    printf("Informe o tamanho do vetor :\n");
    scanf("%d", &n);
    int vetor[n], i;

    for (i=0; i<n; i++){
        printf("\nInforme o valor: ");
        scanf("%d", &vetor[i]);
    }
    //p = &vetor[0];
    quicksort(vetor, 0, n-1);//Mandando o nome do vetor sem [], não é necessário passar por pontiero, e não é necessária a linha de cima.


    for (i=0; i<n; i++){
        printf("%d ", vetor[i]);
    }
}