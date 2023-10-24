#include<stdio.h>

void insertionSort(int vetor[], int n);

void insertionSort(int vetor[], int n)//Recebe o vetor e o tamanho. O vetor passado fica ordenado.
{
    int cont1, key, cont2;
    for (cont1 = 1; cont1 < n; cont1++) {
        key = vetor[cont1];
        cont2 = cont1 - 1;
 
        while (cont2 >= 0 && vetor[cont2] > key) {
            vetor[cont2 + 1] = vetor[cont2];
            cont2 = cont2 - 1;
        }
        vetor[cont2 + 1] = key;
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
    insertionSort(vetor, n);//Mandando o nome do vetor sem [], não é necessário passar por pontiero, e não é necessária a linha de cima.


    for (i=0; i<n; i++){
        printf("%d ", vetor[i]);
    }
}