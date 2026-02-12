#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CHILD_PROCESS_NUM 10

int main()
{
    pid_t ret;
    int sum = 0;

    for (int i = 1; i <= CHILD_PROCESS_NUM; i++) {
        ret = fork();
        if (ret == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (ret == 0) 
            exit(i*i);
    }

    
    for (int i = 1; i <= CHILD_PROCESS_NUM; i++) {
        siginfo_t info;

        waitid(P_ALL, NULL, &info, WEXITED);

        if (info.si_code != CLD_EXITED) {
            printf("code != CLD_EXITED\n");
            exit(EXIT_FAILURE);
        }

        printf("process %d ret %d\n", info.si_pid, info.si_status);
        sum += info.si_status;
    }

    printf("sum = %d\n", sum);

    exit(EXIT_SUCCESS); 
}
