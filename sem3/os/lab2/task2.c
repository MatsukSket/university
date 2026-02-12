#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_time_and_pid(const char *proc_name) {
    struct timeval tv;
    struct tm *tm_info;

    gettimeofday(&tv, NULL);
    tm_info = localtime(&tv.tv_sec);

    printf("[%s] PID=%d, PPID=%d, Время: %02d:%02d:%02d:%03ld\n",
           proc_name,
           getpid(),
           getppid(),
           tm_info->tm_hour,
           tm_info->tm_min,
           tm_info->tm_sec,
           tv.tv_usec / 1000);
}

int main() {
    pid_t pid1, pid2;


    pid1 = fork();

    if (pid1 < 0) {
        perror("Ошибка fork()");
        exit(1);
    }

    if (pid1 == 0) {
        print_time_and_pid("Дочерний 1");
        exit(0);
    } else {

        pid2 = fork();

        if (pid2 < 0) {
            perror("Ошибка fork()");
            exit(1);
        }

        if (pid2 == 0) { 

            print_time_and_pid("Дочерний 2");
            exit(0);
        } else {

            print_time_and_pid("Родительский");


            wait(NULL);
            wait(NULL);

            printf("Родительский процесс выполняет команду ps -x:\n\n");
            system("ps -x");
        }
    }

    return 0;
}
