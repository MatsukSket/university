#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int value = 0;
pthread_mutex_t m;

void* do_work(void* thread_id) {
    int id = *(int*)thread_id;

    pthread_mutex_lock(&m);
    value = 1;
    for (int i = 0; i < 5; i++) {
        printf("Thread %d: %d\n", id, value);
        value++;
        sleep(1);
    }
    pthread_mutex_unlock(&m);
    return NULL;
}

int main() 
{
    pthread_t t1, t2;
    int t1_id = 1, t2_id = 2;
    pthread_mutex_init(&m, NULL);
    pthread_create(&t1, NULL, do_work, &t1_id);
    pthread_create(&t2, NULL, do_work, &t2_id);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&m);
    return 0;
} 