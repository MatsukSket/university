#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* work(void* arg) {
    for (int i = 0; i < 3; i++) {
        puts(arg);
        sleep(1);
    }
    return "Bye, World!";
}

int main() 
{
    pthread_t thread;
    void* thread_result;

    pthread_create(&thread, NULL, work, "Hello, World!");
    
    pthread_join(thread, &thread_result);
    puts(thread_result);

    return 0;
}