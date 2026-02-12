#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

#define WAITING_CHAIRS 3
#define NUM_CUSTOMERS 10

sem_t customers;
sem_t barber;
sem_t mutex;

int waiting = 0;
int day_over = 0;
int now_in_barberroom;

void* barber_work(void* arg) {
    while (1) {
        sem_wait(&customers);
        sem_wait(&mutex);

        waiting--;
        printf("Стрижка идет. Ждут: %d\n", waiting);

        sem_post(&barber);
        sem_post(&mutex);

        sleep(3);
        printf("Клиент %d постригся\n", now_in_barberroom);
    }

    return NULL;
}

void* customer_work(void* arg) {
    int id = *(int*)arg;

    sem_wait(&mutex);
    if(waiting < WAITING_CHAIRS) {
        waiting++;
        printf("Клиент %d сел ждать. Ждут: %d\n", id, waiting);
        sem_post(&customers);
        sem_post(&mutex);

        sem_wait(&barber);
        now_in_barberroom = id;
        printf("Клиент %d начал стричься\n", id);
    }
    else {
        sem_post(&mutex);
        printf("Клиент  %d ушел, стульев нет\n", id);
    }

    free(arg);
    return NULL;
}

int main() {
    sem_init(&barber, 0, 0);
    sem_init(&customers, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t barber_thread;
    pthread_t customer_thread[NUM_CUSTOMERS];
    pthread_create(&barber_thread, NULL, barber_work, NULL);

    for ( int i = 1; i <= NUM_CUSTOMERS; i++) {
        sleep(1);
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&customer_thread[i-1], NULL, customer_work, id);
    }

    sleep(20);

    puts("Парикмахерская закрывается");
    return 0;
}