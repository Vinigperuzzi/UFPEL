#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int vetor[], int n);
void selectionSort(int vetor[], int n);
void quicksort (int vetor[], int left, int right);
void mergeSort(int vetor[], int left, int right);
void merge(int vetor[], int left, int mid, int right);
void testaVetor(int vetor[], int tam);

double ETSelec, ETInser, ETQuick, ETMerge;

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

void testaVetor(int vetor[], int tam)
{
    int i, erro=0;
    for(i=0; i<tam-1; i++){
        if(vetor[i] > vetor[i+1]){
            erro++;
        }
    }
    if (erro > 0)
        printf("O vetor passado não está ordenado em ordem crescente.\n");
    else
        printf("O vetor está perfeitamente ordenado em ordem crescente.\n");
}

int main (void)
{
    int tam, i, j;
    clock_t start, end;
    srand(time(0));
    printf("Informe o tamanho do vetor a ser ordenado: ");
    scanf("%d", &tam);
    int vetor[tam], vetorResul[4][tam];

    for(i = 0; i < tam; i++)
        vetor[i] = rand()%1000000;
    
    for(i = 0; i < 4; i++)
        for(j = 0; j < tam; j++)
            vetorResul[i][j] = vetor[j];
    
    start = clock();
    insertionSort(vetorResul[0], tam);
    end = clock();
    ETInser = (double)(end - start)/CLOCKS_PER_SEC;

    start = clock();
    selectionSort(vetorResul[1], tam);
    end = clock();
    ETSelec = (double)(end - start)/CLOCKS_PER_SEC;

    start = clock();
    quicksort (vetorResul[2], 0, tam-1);
    end = clock();
    ETQuick = (double)(end - start)/CLOCKS_PER_SEC;

    start = clock();
    mergeSort(vetorResul[3], 0, tam-1);
    end = clock();
    ETMerge = (double)(end - start)/CLOCKS_PER_SEC;

    for (i=0; i<4; i++){
        if (i == 0){
            printf("Imprimindo o vetor do insertion sort: \n");
        }
        if (i == 1){
            printf("Imprimindo o vetor do selection sort: \n");
        }
        if (i == 2){
            printf("Imprimindo o vetor do quick sort: \n");
        }
        if (i == 3){
            printf("Imprimindo o vetor do merge sort: \n");
        }
        for(j=0; j<tam; j++){
            printf("%d ", vetorResul[i][j]);
        }
        printf("\n\n\n");
    }

    for (i=0; i<4; i++){
        if (i == 0){
            printf("\nSobre o vetor do insertion sort: \n");
        }
        if (i == 1){
            printf("\nSobre o vetor do selection sort: \n");
        }
        if (i == 2){
            printf("\nSobre o vetor do quick sort: \n");
        }
        if (i == 3){
            printf("\nSobre o vetor do merge sort: \n");
        }
        testaVetor(vetorResul[i], tam);
    }

    printf("\n\nPor fim, os tempos de execução: \n");
    printf("O insertion levou: %lf\n", ETInser);
    printf("O selection levou: %lf\n", ETSelec);
    printf("O quick levou: %lf\n", ETQuick);
    printf("O merge levou: %lf\n", ETMerge);
}