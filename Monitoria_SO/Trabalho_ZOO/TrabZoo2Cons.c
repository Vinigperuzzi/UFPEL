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

int timesUp = 0, timesAnimal = 0, timesAdestrador = 0, fimDeadlock = 0, deadlock;

int comedouros[3] = {0, 0, 0}, estoque[3] = {30, 30, 30};
sem_t carneVazio, carneCheio, insetoVazio, insetoCheio, ervaVazio, ervaCheio;
                        /*cheio marca quantos espaços ocupados existem, vazio marca quantos espaços
                        *vazios existem (Se vazio está em zero, não há espaços vazios,
                        *ou seja está cheio e não se pode produzir.),
                        *O cheio, por óbvio, quando está em zero está vazio, não se pode consumir.
                        */
sem_t estCarneVazio, estCarneCheio, estInsetoVazio, estInsetoCheio, estErvaVazio, estErvaCheio;

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

typedef struct grupo {
        Animal* leoes;
        Animal* suricatos;
        Animal* aves;
} party;


Animal* criaBicho(int qtd, int tipo){
    Animal *bicho;
    if ((bicho = malloc(sizeof(Animal) * qtd)) == NULL){
        printf("\n\nWarning: Erro ao criar os bichos");
    } else {
        for(int i = 0; i<qtd; i++){
            if (tipo == 0){
            bicho[i].dormir = ((int)(rand()%6)) + 5;   //Gera um valor aleatório entre 10 e 15.
            bicho[i].fome = ((int)(rand()%4) + 2);
            } else if (tipo == 1){
                bicho[i].dormir = ((int)(rand()%5)) + 4;   //Gera um valor aleatório entre 8 e 12.
                bicho[i].fome = ((int)(rand()%2) + 1);
            } else {
                bicho[i].dormir = ((int)(rand()%5)) + 3;   //Gera um valor aleatório entre 6 e 10.
                bicho[i].fome = ((int)(rand()%3) + 2);
            }
            bicho[i].exibir = 12 - bicho[i].dormir;
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
        printf("\n\n\t\t==================Eis que passa um dia=========================\a\n");
        printf("\t\tEstoque = %d, %d, %d e comedouros = %d, %d, %d\n\n", estoque[0], estoque[1], estoque[2], comedouros[0], comedouros[1], comedouros[2]);
    }
    timesUp = 1;
    pthread_exit(NULL);
}

int come(int tipo, int fome, int index){
    int comeu = 0;
    for(int i = 0; i<fome; i++){
        if (tipo == 0){
            sem_wait(&carneCheio);
            printf("\n\n============================\n||  O Leão %d está comendo ||\n============================\n", index);
            pthread_mutex_lock(&consumidor0);
            comedouros[tipo]--;
            printf("\n**==Comedouro %d ficou com %d porções.==**\n", tipo, comedouros[tipo]);
            pthread_mutex_unlock(&consumidor0);
            sem_post(&carneVazio);
        } else if (tipo == 1){
            sem_wait(&insetoCheio);
            printf("\n\n================================\n||  O Suricato %d está comendo ||\n================================\n", index);
            pthread_mutex_lock(&consumidor1);
            comedouros[tipo]--;
            printf("\n**==Comedouro %d ficou com %d porções.==**\n", tipo, comedouros[tipo]);
            pthread_mutex_unlock(&consumidor1);
            sem_post(&insetoVazio);
        } else {
            sem_wait(&ervaCheio);
            printf("\n\n================================\n||  O Avestruz %d está comendo ||\n================================\n", index);
            pthread_mutex_lock(&consumidor2);
            comedouros[tipo]--;
            printf("\n**==Comedouro %d ficou com %d porções.==**\n", tipo, comedouros[tipo]);
            pthread_mutex_unlock(&consumidor2);
            sem_post(&ervaVazio);
        }
        comeu++;
    }
    return comeu;
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
            local.comeu += come(local.tipo, local.fome, local.index);
        }
        deadlock = 0;
        ExibeSe(local.exibir);
        if (local.tipo  == 0){
            local.fome = ((int)(rand()%6)) + 5;
        } else if (local.tipo == 1){
            local.fome = ((int)(rand()%2) + 1);
        } else {
            local.fome = ((int)(rand()%3) + 2);
        }
        if (timesUp == 0){
            local.comeu += come(local.tipo, local.fome, local.index);
        }
        deadlock = 0;
        dorme(local.dormir);
        if (local.tipo  == 0){
            local.fome = ((int)(rand()%6)) + 5;
        } else if (local.tipo == 1){
            local.fome = ((int)(rand()%2) + 1);
        } else {
            local.fome = ((int)(rand()%3) + 2);
        }
    }
    *(Animal *)animal = local;
    pthread_exit(NULL);
}

void* iniciarServico(int* index){
    printf("Adestrador %d está no serviço\n", *index);
    int qualComedouro, aux, inteiro = 0;
    while (timesUp == 0 || timesAnimal == 0){
        qualComedouro = inteiro % 3;
        inteiro++;
        if (qualComedouro == 0){
            sem_getvalue(&carneVazio, &aux);
            if (aux > 1){
                pthread_mutex_lock(&produtor0);
                sem_wait(&estCarneCheio);
                sem_wait(&carneVazio);
                estoque[0]--;
                comedouros[0]++;
                sem_post(&carneCheio);
                sem_post(&estCarneVazio);
                pthread_mutex_unlock(&produtor0);
                printf("\n\n\t\t\t ++==++== O veterinário deixou o comedouro 0 com %d ==++==++\n", comedouros[0]);
            } else {}
        } else if (qualComedouro == 1){
            sem_getvalue(&insetoVazio, &aux);
            if (aux > 1){
                pthread_mutex_lock(&produtor1);
                sem_wait(&estInsetoCheio);
                sem_wait(&insetoVazio);
                estoque[1]--;
                comedouros[1]++;
                sem_post(&insetoCheio);
                sem_post(&estInsetoVazio);
                pthread_mutex_unlock(&produtor1);
                printf("\n\n\t\t\t ++==++== O veterinário deixou o comedouro 1 com %d ==++==++\n", comedouros[1]);
            } else {}
        } else {
            sem_getvalue(&ervaVazio, &aux);
            if (aux > 1){
                pthread_mutex_lock(&produtor2);
                sem_wait(&estErvaCheio);
                sem_wait(&ervaVazio);
                estoque[2]--;
                comedouros[2]++;
                sem_post(&ervaCheio);
                sem_post(&estErvaVazio);
                pthread_mutex_unlock(&produtor2);
                printf("\n\n\t\t\t ++==++== O veterinário deixou o comedouro 2 com %d ==++==++\n", comedouros[2]);
            }
        }
        deadlock = 0;
    }
    printf("\n\n\t\tO adestrador %d acabou seu serviço\n", *index);
    pthread_exit(NULL);
}

void* entrega(){
    while (timesAnimal != 1){
        int aux1, aux2, aux3;
        sem_getvalue(&estCarneCheio, &aux1);
        sem_getvalue(&estInsetoCheio, &aux2);
        sem_getvalue(&estErvaCheio, &aux3);
        if (aux1 == 0 || aux2 == 0 || aux3 == 0){
            for (int i = 0; i < 30 - aux1; i++){
                sem_wait(&estCarneVazio);
                estoque[0]++;
                sem_post(&estCarneCheio);
            }
            for (int i = 0; i < 30 - aux2; i++){
                sem_wait(&estInsetoVazio);
                estoque[1]++;
                sem_post(&estInsetoCheio);
            }
            for (int i = 0; i < 30 - aux3; i++){
                sem_wait(&estErvaVazio);
                estoque[2]++;
                sem_post(&estErvaCheio);
            }
            printf("\n\nEstoque abastecido com sucesso. %d carnes, %d insetos e %d ervas.\n\n", estoque[0], estoque[1], estoque[2]);
        }
    }
    pthread_exit(NULL);
}

void mostraResultado(Animal* leoes, Animal* suricatos, Animal* aves){
    printf("\n\n\t\t\t\t\t\t=================================\n");
    for (int i = 0; i < NUMLEAO; i++){
        printf("\t\t\t\t\t\t||    O leão %d comeu %02d vezes.  ||\n", i, leoes[i].comeu);
    }
    printf("\t\t\t\t\t\t=================================\n");
    for (int i = 0; i < NUMSURI; i++){
        printf("\t\t\t\t\t\t|| O suricato %d comeu %02d vezes. ||\n", i, suricatos[i].comeu);
    }
    printf("\t\t\t\t\t\t=================================\n");
    for (int i = 0; i < NUMAVES; i++){
        printf("\t\t\t\t\t\t|| O avestruz %d comeu %02d vezes. ||\n", i, aves[i].comeu);
    }
    printf("\t\t\t\t\t\t=================================\n\n\n");
}

void liberaTudo(Animal *leoes, Animal *suricatos, Animal *aves){
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
    sem_destroy(&estCarneVazio);
    sem_destroy(&estInsetoVazio);
    sem_destroy(&estErvaVazio);
    sem_destroy(&estCarneCheio);
    sem_destroy(&estInsetoCheio);
    sem_destroy(&estErvaCheio);
}

void *testaDL(party* zoo){
    Animal *leoes = zoo->leoes;
    Animal *suricatos = zoo->suricatos;
    Animal *aves = zoo->aves;
    while(1){
        if (fimDeadlock == 0){
            if (deadlock == 0){
                deadlock = 1;
                sleep(30 + 1);
            } else{
                printf("\n\n\t\tInfelizmente foi detectado um deadlock e o programa teve que ser abortado.\n\n");
                liberaTudo(leoes, suricatos, aves);
                exit(-1);
            }
        } else{
            pthread_exit(NULL);
        }
    }
}

int main (void) {
    srand(time(NULL));
    system("clear || cls");
    int totalDias;
    do {
        printf("\nInforme uma quantidade de dias para que seja simulado (cada segundo é uma hora, portanto um dia dura 24 segundos da vida real): ");
        scanf("%d", &totalDias);
        totalDias--;
        if (totalDias < 0){
            printf("\nValor inválido de dias, informe um valor maiorou igual a 0");
        }
    } while (totalDias < 0);
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

    sem_init(&estCarneVazio, 0, 0);
    sem_init(&estInsetoVazio, 0, 0);
    sem_init(&estErvaVazio, 0, 0);
    sem_init(&estCarneCheio, 0, 30);    //Esse inicia de com os valores opostos, pois o estoque inicia cheio
    sem_init(&estInsetoCheio, 0, 30);
    sem_init(&estErvaCheio, 0, 30);

    leoes = criaBicho(NUMLEAO, 0);
    suricatos = criaBicho(NUMSURI, 1);
    aves = criaBicho(NUMAVES, 2);

    int totalAnimais = NUMLEAO + NUMSURI + NUMAVES;

    pthread_t controlaDias;
    pthread_t rotinaAnimais[totalAnimais];
    pthread_t adestradores[NUMADESTRADORES];
    pthread_t fornecedor;
    pthread_t testeDeadlock;

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

    party zoo;
    zoo.leoes = leoes;
    zoo.suricatos = suricatos;
    zoo.aves = aves;

    pthread_create(&testeDeadlock, NULL, (void*)testaDL, &zoo);

    for (int i = 0; i < totalAnimais; i++){
        pthread_join(rotinaAnimais[i], NULL);
    }

    timesAnimal = 1;

     //printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVeio até aqui2\n\n");
     //printf("Comedouro = %d, 1 = %d e 2 = %d\n", comedouros[0], comedouros[1], comedouros[2]);

    for (int i = 0; i < NUMADESTRADORES; i++){
        pthread_join(adestradores[i], NULL);
    }

    timesAdestrador = 1;

     //printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVeio até aqui3\n\n");


    fimDeadlock = 1;
    pthread_join(controlaDias, NULL);
    pthread_join(fornecedor, NULL);
    printf("\n\n\t\t++**++ Aguardando o detector de deadlock terminar a sua análise ++**++\n\n");
    pthread_join(testeDeadlock, NULL);


    mostraResultado(leoes, suricatos, aves);

    liberaTudo(leoes, suricatos, aves);

    return 0;
}


