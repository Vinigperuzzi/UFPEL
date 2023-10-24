#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

pthread_mutex_t consumidor0 = PTHREAD_MUTEX_INITIALIZER;
sem_t carneVazio;

int main (void){
    pthread_mutex_init(&consumidor0, NULL);
    sem_init(&carneVazio, 0, 1);

    pthread_mutex_lock(&consumidor0);
    pthread_mutex_unlock(&consumidor0);
    sem_wait(&carneVazio);
    sem_post(&carneVazio);

    sem_destroy(&carneVazio);
    pthread_mutex_destroy(&consumidor0);

}