#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int signal_sent = 0;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex;

void* thread1_work(void* arg) {
    pthread_mutex_lock(&mutex);
    puts("Thread1 starts and waits for signal");

    while (!signal_sent) 
       pthread_cond_wait(&condvar, &mutex); 
    // pthread_cond_wait(&condvar, &mutex);

    puts("Thread1 received a signal");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* thread2_work(void* arg) {
    pthread_mutex_lock(&mutex);
    puts("Thread2 starts and does some work");
    
    puts("Thread2 is sending a signal");
    signal_sent = 1;
    pthread_cond_signal(&condvar);
    
    puts("Thread2 sent a signal");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, NULL, thread1_work, NULL);
    sleep(2);
    pthread_create(&thread2, NULL, thread2_work, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex); 
    return 0;
}