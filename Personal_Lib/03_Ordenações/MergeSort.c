#include <stdio.h>
#include <stdlib.h>

void mergeSort(int vetor[], int left, int right);
void merge(int vetor[], int left, int mid, int right);


void mergeSort(int vetor[], int left, int right)//Recebe o vetor a ser ordenado e as posições inicial e final (índice) do vetor.
{
	if (left < right) {
		int mid = left + (right - left) / 2;

		mergeSort(vetor, left, mid);
		mergeSort(vetor, mid + 1, right);

		merge(vetor, left, mid, right);
	}
}


void merge(int vetor[], int left, int mid, int right)//Chamada automática do mergesort, recebe o vetor e os índices da primeira, última posições e central
{
	int cont1, cont2, cont3;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int L[n1], R[n2];

	for (cont1 = 0; cont1 < n1; cont1++)
		L[cont1] = vetor[left + cont1];
	for (cont2 = 0; cont2 < n2; cont2++)
		R[cont2] = vetor[mid + 1 + cont2];

	cont1 = 0; // índice inicial do primeiro sub vetor
	cont2 = 0; // índice inicial do segundo sub vetor
	cont3 = left; // índice inicial do vetor resultado.

	while (cont1 < n1 && cont2 < n2) {
		if (L[cont1] <= R[cont2]) {
			vetor[cont3] = L[cont1];
			cont1++;
		}
		else {
			vetor[cont3] = R[cont2];
			cont2++;
		}
		cont3++;
	}

	while (cont1 < n1) {//Resto do sub vetor da esquerda, se houver
		vetor[cont3] = L[cont1];
		cont1++;
		cont3++;
	}

	while (cont2 < n2) {//Resto do sub vetor da direita, se houver
		vetor[cont3] = R[cont2];
		cont2++;
		cont3++;
	}
}


int main (void)
{
    int n;
    printf("Informe o tamanho do vetor :\n");
    scanf("%d", &n);
    int vetor[n], cont1;

    for (cont1=0; cont1<n; cont1++){
        printf("\nInforme o valor: ");
        scanf("%d", &vetor[cont1]);
    }
    //p = &vetor[0];
    mergeSort(vetor, 0, n-1);//Mandando o nome do vetor sem [], não é necessário passar por pontiero, e não é necessária a linha de cima.


    for (cont1=0; cont1<n; cont1++){
        printf("%d ", vetor[cont1]);
    }
}