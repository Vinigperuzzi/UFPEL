#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

int nAssentos, nNebulizadores, nMedicos;
int fimDeCiclos = 0, threadsLancadas = 0;
int genteNaSala = 0, qtdRiscoDeMorte = 0;

pthread_mutex_t muGenteNaSala;
pthread_mutex_t riscoDeMorte;
pthread_mutex_t medicoSeleciona;

enum Estado{
    esperando,
    nebulizando,
    atendimento,
    partiu
};

typedef struct{
    int sinalVital;
    int idade;
    int estado; //0 - esperando, 1 - nebulizando, 2 - em atendimento, 3 - foi embora
    int indice;
} pessoa;

pessoa *pessoas;

void consultorio(void){
    printf("Lançou médico\n\n");
    while(fimDeCiclos != 1 || genteNaSala > 0){
        int maxIdade = 0, maxIndice = -1;
        pthread_mutex_lock(&medicoSeleciona);
        for (int i = 0; i < threadsLancadas; i++){
            if (pessoas[i].estado == esperando){
                if(pessoas[i].idade > maxIdade){
                    maxIdade = pessoas[i].idade;
                    maxIndice = pessoas[i].indice;
                }
            }
        }
        pthread_mutex_unlock(&medicoSeleciona);
        if (maxIndice != -1){
            pessoas[maxIndice].estado = atendimento;
            genteNaSala--;
            printf("Médico atendendo a pessoa %d.\n", pessoas[maxIndice].indice);
            sleep(rand()%2 + 2);
            pessoas[maxIndice].estado = partiu;
        } else {
            printf("Médico se preparando para pegar o próximo paciente.\n");
            sleep(4);
        }
    }
}

void salaDeEspera(int* indice){
    int ind = *indice;
    ind -= 1;
    if (genteNaSala < 16){
        pthread_mutex_lock(&muGenteNaSala);
        genteNaSala++;
        pthread_mutex_unlock(&muGenteNaSala);
        printf("Pessoa %d chegou ao pronto socorro e foi atendida.\n\n", pessoas[ind].indice);
        while (pessoas[ind].estado == esperando){
            sleep(rand()%1 +1);
            if (pessoas[ind].sinalVital < 10){
                pessoas[ind].sinalVital++;
            } else {
                printf("Pessoa %d: --\"Tô morrendo aqui\".\n\n", pessoas[ind].indice);
                pthread_mutex_lock(&riscoDeMorte);
                qtdRiscoDeMorte++;
                pthread_mutex_unlock(&riscoDeMorte);
            }
        }
        return;
    }
    printf("\nPessoa %d chegou ao pronto socorro, mas a sala estava cheia: --\"Estou indo embora dessa espelunca!!\"\n\n\n", pessoas[ind].indice);
}

void contaTempo(int* tempo){
    printf("Esperando por %d segundos\n\n", *tempo);
    sleep(*tempo);
    fimDeCiclos = 1;
}

pessoa iniciaPessoa(){
    pessoa Pessoa;
    Pessoa.sinalVital = 5;
    Pessoa.estado = 0;
    Pessoa.indice = 0;
    Pessoa.idade = rand()%70 + 10;
    return Pessoa;
}

int main(int argc, char* argv[]){
    system("clear || cls");
    srand(time(NULL));

    if (argv[4] == NULL || argv[5] != NULL){
        printf("\nVocê não informou os parâmetros certos.\nVocê precisa informar o \
número de assentos, de nebulizadores, de médicos e por fim o tempo de execução em segundos.\n \
\"./executavel [nAssentos][nNebulizadores][nMedicos]\".\n\n");
        exit(0);
    }
    nAssentos = atoi(argv[1]);
    nNebulizadores = atoi(argv[2]);
    nMedicos = atoi(argv[3]);
    int qtdTempo = atoi(argv[4]);


    printf("%d %d %d %d\n", nAssentos, nNebulizadores, nMedicos, qtdTempo);

    pthread_t thTempo;
    pthread_t thMedicos[nMedicos];
    pthread_t *thPessoas = malloc(sizeof(pthread_t));
    pessoas = malloc(sizeof(pessoa));

    if (thPessoas == NULL){
        printf("Não foi possível alocar um espaço para o vetor handle das threads.\n\n");
        exit(0);
    }

    if (pessoas == NULL){
        printf("Não foi possível alocar um espaço para o vetor de pessoas.\n\n");
        exit(0);
    }

    pthread_create(&thTempo, NULL, (void *)contaTempo, &qtdTempo);

    for (int i = 0; i < nMedicos; i++){
        pthread_create(&thMedicos[i], NULL, (void *)consultorio, NULL);
    }

    while(fimDeCiclos == 0){
        int espera = rand()%5 + 2;
        sleep(espera);
        threadsLancadas++;
        thPessoas = realloc(thPessoas, (sizeof(pthread_t) * threadsLancadas));
        pessoas = realloc(pessoas, (sizeof(pessoa) * threadsLancadas));
        pessoas[threadsLancadas-1] = iniciaPessoa();
        pessoas[threadsLancadas-1].indice = threadsLancadas-1;
        if (thPessoas == NULL){
            printf("Não foi possível realocar o espaço para o handle das threads.\n");
            exit(0);
        }
        pthread_create(&thPessoas[threadsLancadas-1], NULL, (void*)salaDeEspera, &threadsLancadas);
    }

    pthread_join(thTempo, NULL);
    printf("Joinou o tempo.\n\n");

    for (int i = 0; i < nMedicos; i++){
        pthread_join(thMedicos[i], NULL);
    }
    printf("Joinou os médicos.\n\n");

    for (int i = 0; i < threadsLancadas; i++){
        pthread_join(thPessoas[i], NULL);
        printf("Joinou a pessoa %d\n", i);
    }

    free(thPessoas);
    free(pessoas);
    pthread_mutex_destroy(&muGenteNaSala);
    pthread_mutex_destroy(&riscoDeMorte);
    pthread_mutex_destroy(&medicoSeleciona);

    printf("\n\n\t\t\tFim de execução\n\n");
    printf("Pessas asfixiaram por %d tempos.\n\n", qtdRiscoDeMorte);

    return 0;
}