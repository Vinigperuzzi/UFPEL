#include<stdio.h>

int mergeSort(int vetor[]);

int mergeSort(int vetor[]){
    int tam = ( sizeof(vetor) / sizeof(vetor[0]) ), cont;
    int tamEsq = tam/2, tamDir = tam/2;
    if (tam <= 1)
        return vetor;
    if (tam%2 != 0)
        tamDir++;
    int vetorEsq[tamEsq], vetorDir[tamDir], resultado[tam];
    int *e = &vetorEsq[0], *d = &vetorDir[0], *r = &resultado[0];
    
    for(cont = 0; cont < tamEsq; cont++)
        vetorEsq[cont] = vetor[cont];
    for(cont = tamEsq; cont < tamDir; cont++)
        vetorDir[cont] = vetor[cont];

    *e = mergeSort(vetorEsq);
    *d = mergeSort(vetorDir);
    *r = merge(vetorEsq, vetorDir);
}

int merge(int vetorEsq[], int vetorDir[])
{
    int tamEsq = sizeof(vetorEsq)/sizeof(vetorEsq[0]), tamDir = sizeof(vetorDir)/sizeof(vetorDir[0]), resultado[tamEsq + tamDir];
    while (tamEsq > 0 || tamDir > 0){
        if (tamEsq > 0 && tamDir > 0){
            if (vetorEsq[0] <= vetorDir[0]){
                resultado[0] = vetorEsq[0];
            }
        }
        else if (tamEsq > 0){

        }
        else if (tamDir > 0){

        }
    }
}