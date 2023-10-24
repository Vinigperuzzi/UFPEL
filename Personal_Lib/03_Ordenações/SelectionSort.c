#include<stdio.h>

void selectionSort(int vetor[], int n);

void selectionSort(int vetor[], int n)//Recebe o vetor e o tamanho. O vetor passado fica ordenado.
{
    int cont1, cont2, indiceMin, temp;
 
    for (cont1 = 0; cont1 < n-1; cont1++)
    {
        indiceMin = cont1;
        for (cont2 = cont1 + 1; cont2 < n; cont2++)
          if (vetor[cont2] < vetor[indiceMin])
            indiceMin = cont2;
 
        temp = vetor[indiceMin];
        vetor[indiceMin] = vetor[cont1];
        vetor[cont1] = temp;
    }
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
    selectionSort(vetor, n);//Mandando o nome do vetor sem [], não é necessário passar por pontiero, e não é necessária a linha de cima.

    for (i=0; i<n; i++){
        printf("%d ", vetor[i]);
    }
}
 
