#include <stdio.h>

int main(){
    
    int tam, i;

    printf("Informe o tamanho do vetor a ser ordenado: ");
    scanf("%d", &tam);
    float vetor[tam];
    for (i=0; i<tam; i++){
        printf("Informe o %dº valor: ", i+1);
        scanf("%f", &vetor[i]);
    }
    selectionSort(vetor, tam);

    for (i=0; i<tam; i++){
        printf("%.2f ", vetor[i]);
    }
    printf("\n\n\n");

    return 0;
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