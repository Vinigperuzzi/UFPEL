#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUMLEAO 4
#define NUMSURI 10
#define NUMAVES 7
#define NUMADESTRADORES 2
#define DIAS 10
#define TEMPODIA 24

int timesUp = 0;
int timesAnimal = 0;
int timesAdestrador = 0;

int comedouros[3] = {0, 0, 0}, estoque[3] = {5, 5, 5};
sem_t carneVazio, carneCheio, insetoVazio, insetoCheio, ervaVazio, ervaCheio;
                        /*cheio marca quantos espaços ocupados existem, vazio marca quantos espaços
                        *vazios existem (Se vazio está em zero, não há espaços vazios,
                        *ou seja está cheio e não se pode produzir.),
                        *O cheio, por óbvio, quando está em zero está vazio, não se pode consumir.
                        */

pthread_mutex_t consumidor0 = PTHREAD_MUTEX_INITIALIZER, consumidor1 = PTHREAD_MUTEX_INITIALIZER,
    consumidor2 = PTHREAD_MUTEX_INITIALIZER, produtor0 = PTHREAD_MUTEX_INITIALIZER,
        produtor1 = PTHREAD_MUTEX_INITIALIZER, produtor2 = PTHREAD_MUTEX_INITIALIZER;



typedef struct ANIMAL {
    int exibir;
    int dormir;
    int comeu;
    int fome;
    int index;
    int tipo;
} Animal;


Animal* criaBicho(int qtd, int tipo){
    Animal *bicho;
    if ((bicho = malloc(sizeof(Animal) * qtd)) == NULL){
        printf("\n\nErro ao criar os bichos");
    } else {
        for(int i = 0; i<qtd; i++){
            if (tipo == 0){
            bicho[i].dormir = ((int)(rand()%6)) + 10;   //Gera um valor aleatório entre 10 e 15.
            bicho[i].fome = ((int)(rand()%4) + 2);
            } else if (tipo == 1){
                bicho[i].dormir = ((int)(rand()%5)) + 8;   //Gera um valor aleatório entre 8 e 12.
                bicho[i].fome = ((int)(rand()%2) + 1);
            } else {
                bicho[i].dormir = ((int)(rand()%5)) + 6;   //Gera um valor aleatório entre 6 e 10.
                bicho[i].fome = ((int)(rand()%3) + 2);
            }
            bicho[i].exibir = 24 - bicho[i].dormir;
            bicho[i].comeu = 0;
            bicho[i].index = i;
            bicho[i].tipo = tipo;
        }
    }   
    return bicho;
}


void liberaAnimal(Animal* bicho){
    free(bicho);
}

void contaDias(int* totalDias){
    int dias = 0;
    while (dias <= *totalDias){
        sleep(TEMPODIA);
        dias++;
        printf("\n\n==================Eis que passa um dia=========================\a\a\a\n\n");
    }
    timesUp = 1;
    pthread_exit(NULL);
}

void come(int tipo, int fome, int index){
    for(int i = 0; i<fome; i++){
        if (tipo == 0){
            sem_wait(&carneCheio);
            printf("\n\n============================\n||  O Leão %d está comendo ||\n============================\n", index);
            pthread_mutex_lock(&consumidor0);
            comedouros[tipo]--;
            printf("\n\t\t**==Comedouro %d está com %d porções.==**\n", tipo, comedouros[tipo]);
            pthread_mutex_unlock(&consumidor0);
            sem_post(&carneVazio);
        } else if (tipo == 1){
            sem_wait(&insetoCheio);
            printf("\n\n================================\n||  O Suricato %d está comendo ||\n================================\n", index);
            pthread_mutex_lock(&consumidor1);
            comedouros[tipo]--;
            printf("\n\t\t**==Comedouro %d está com %d porções.==**\n", tipo, comedouros[tipo]);
            pthread_mutex_unlock(&consumidor1);
            sem_post(&insetoVazio);
        } else {
            sem_wait(&ervaCheio);
            printf("\n\n================================\n||  O Avestruz %d está comendo ||\n================================\n", index);
            pthread_mutex_lock(&consumidor2);
            comedouros[tipo]--;
            printf("\n\t\t**==Comedouro %d está com %d porções.==**\n", tipo, comedouros[tipo]);
            pthread_mutex_unlock(&consumidor2);
            sem_post(&ervaVazio);
        }
    }
}

void ExibeSe(int tempo){
    sleep(tempo);
}

void dorme(int tempo){
    sleep(tempo);
}

void* iniciarRotina(Animal* animal){
    Animal local = *(Animal *)animal;
    printf("Bicho %d chegou ao zoo\n", local.index);
    while (timesUp == 0){
        if (timesUp == 0){
        come(local.tipo, local.fome, local.index);
        local.comeu++;
        }
        ExibeSe(local.exibir);
        if (timesUp == 0){
        come(local.tipo, local.fome, local.index);
        local.comeu++;
        }
        dorme(local.dormir);
    }
    *(Animal *)animal = local;
    pthread_exit(NULL);
}

void* iniciarServico(int* index){
    printf("Adestrador %d está no serviço\n", *index);
    int qualComedouro, aux;
    while (timesUp == 0 || timesAnimal == 0){
        qualComedouro = (int)rand()%3;
        //printf("O adestrador %d, escolheu o comedouro %d\n", *index, qualComedouro);
        if (qualComedouro == 0){
            sem_getvalue(&carneVazio, &aux);
            if (aux > 1){
                sem_wait(&carneVazio);
                pthread_mutex_lock(&produtor0);
                estoque[0]--;
                comedouros[0]++;
                pthread_mutex_unlock(&produtor0);
                sem_post(&carneCheio);
                printf("O comedouro 0 está agora com %d\n", comedouros[0]);
            } else {}
        } else if (qualComedouro == 1){
            sem_getvalue(&insetoVazio, &aux);
            if (aux > 1){
                sem_wait(&insetoVazio);
                pthread_mutex_lock(&produtor1);
                estoque[1]--;
                comedouros[1]++;
                pthread_mutex_unlock(&produtor1);
                sem_post(&insetoCheio);
                printf("O comedouro 1 está agora com %d\n", comedouros[1]);
            } else {}
        } else {
            sem_getvalue(&ervaVazio, &aux);
            if (aux > 1){
                sem_wait(&ervaVazio);
                pthread_mutex_lock(&produtor2);
                estoque[2]--;
                comedouros[2]++;
                pthread_mutex_unlock(&produtor2);
                sem_post(&ervaCheio);
                printf("O comedouro 2 está agora com %d\n", comedouros[2]);
            }
        }
    }
    printf("\n\n\n\n\t\t\t\tO adestrador %d acabou seu serviço\n\n\n\n\n", *index);
    for (int i = 0; i<5; i++){
        printf("\a");
        sleep(1);
    }
    pthread_exit(NULL);
}

void* entrega(){
    while (timesUp == 0 || timesAnimal == 0 || timesAdestrador == 0){
        if (estoque[0] == 0 || estoque[1] == 0 || estoque[2] == 0){
            estoque[0] = 5;
            estoque[1] = 5;
            estoque[2] = 5;
            printf("\n\n==================== O entregador reabasteceu o zoo   =======================\n\n");
        } else {
            printf("\n\n==================== Entregador tentou fazer a entrega   =======================\n\n");
        }
        sleep(12);
    }
    pthread_exit(NULL);
}

void mostraResultado(Animal* leoes, Animal* suricatos, Animal* aves){
    for (int i = 0; i < NUMLEAO; i++){
        printf("O leão %d comeu %d vezes.\n\n", i, leoes[i].comeu);
    }
    for (int i = 0; i < NUMSURI; i++){
        printf("O suricato %d comeu %d vezes.\n\n", i, suricatos[i].comeu);
    }
    for (int i = 0; i < NUMAVES; i++){
        printf("O avestruz %d comeu %d vezes.\n\n", i, aves[i].comeu);
    }
}

int main (void) {
    srand(time(NULL));
    system("clear || cls");
    printf("\nInforme uma quantidade de dias para que seja simulado (cada segundo é uma hora, portanto um dia dura 24 segundos da vida real): ");
    int totalDias;
    scanf("%d", &totalDias);
    Animal *leoes, *suricatos, *aves;

    sem_init(&carneVazio, 0, 10);
    sem_init(&insetoVazio, 0, 10);
    sem_init(&ervaVazio, 0, 10);
    sem_init(&carneCheio, 0, 0);
    sem_init(&insetoCheio, 0, 0);
    sem_init(&ervaCheio, 0, 0);

    pthread_mutex_init(&consumidor0, NULL);
    pthread_mutex_init(&consumidor1, NULL);
    pthread_mutex_init(&consumidor2, NULL);
    pthread_mutex_init(&produtor0, NULL);
    pthread_mutex_init(&produtor1, NULL);
    pthread_mutex_init(&produtor2, NULL);


    leoes = criaBicho(NUMLEAO, 0);
    suricatos = criaBicho(NUMSURI, 1);
    aves = criaBicho(NUMAVES, 2);

    int totalAnimais = NUMLEAO + NUMSURI + NUMAVES;

    pthread_t controlaDias;
    pthread_t rotinaAnimais[totalAnimais];
    pthread_t adestradores[NUMADESTRADORES];
    pthread_t fornecedor;

    pthread_create(&controlaDias, NULL, (void*)contaDias, &totalDias);

    int controlVar = 0;
    for (int i = 0; i < NUMLEAO; i++){
        pthread_create(&rotinaAnimais[controlVar], NULL, (void*)iniciarRotina, &leoes[i]);
        controlVar++;
    }
    for (int i = 0; i < NUMSURI; i++){
        pthread_create(&rotinaAnimais[controlVar], NULL, (void*)iniciarRotina, &suricatos[i]);
        controlVar++;
    }
    for (int i = 0; i < NUMAVES; i++){
        pthread_create(&rotinaAnimais[controlVar], NULL, (void*)iniciarRotina, &aves[i]);
        controlVar++;
    }

    int u[NUMADESTRADORES];
    for (int i = 0; i<NUMADESTRADORES; i++){
        u[i] = i;
        pthread_create(&adestradores[i], NULL, (void*)iniciarServico, &u[i]);
    }

    pthread_create(&fornecedor, NULL, (void*)entrega, NULL);

     printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVeio até aqui1\n\n");

    for (int i = 0; i < totalAnimais; i++){
        pthread_join(rotinaAnimais[i], NULL);
    }

    timesAnimal = 1;

     printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVeio até aqui2\n\n");
     printf("Comedouro0 = %d, 1 = %d e 2 = %d\n", comedouros[0], comedouros[1], comedouros[2]);

    for (int i = 0; i < NUMADESTRADORES; i++){
        pthread_join(adestradores[i], NULL);
    }

    timesAdestrador = 1;

     printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVeio até aqui3\n\n");


    pthread_join(controlaDias, NULL);
    pthread_join(fornecedor, NULL);

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVeio até aqui4\n\n");

    mostraResultado(leoes, suricatos, aves);

    liberaAnimal(leoes);
    liberaAnimal(suricatos);
    liberaAnimal(aves);
    sem_destroy(&carneVazio);
    sem_destroy(&insetoVazio);
    sem_destroy(&ervaVazio);
    sem_destroy(&carneCheio);
    sem_destroy(&insetoCheio);
    sem_destroy(&ervaCheio);
    pthread_mutex_destroy(&consumidor0);
    pthread_mutex_destroy(&consumidor1);
    pthread_mutex_destroy(&consumidor2);
    pthread_mutex_destroy(&produtor0);
    pthread_mutex_destroy(&produtor1);
    pthread_mutex_destroy(&produtor2);

    return 0;
}


