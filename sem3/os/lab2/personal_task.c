#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


void print_ids(const char* message) {
    pid_t current_pid = getpid();
    pid_t parent_pid = getppid();
    printf("%s: PID = %d, PPID = %d\n", message, current_pid, parent_pid);
}

pid_t create_process(int child_num) {
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {
        // дочерний
        print_ids("Дочерний процесс после создания");
        return pid;
    } else {
        // родитель
        printf("Процесс с ID %d породил процесс с ID %d\n", getpid(), pid);
        return pid;
    }
}

int main() {
    print_ids("Процесс после запуска");

    // номера:   0 1 2 3 4 5 6 7
    // процессы: # 0 1 2 2 3 4 6 
    pid_t pids[8];
    
    pids[1] = create_process(1);

    if (pids[1] == 0) {
        // процесс 1
        pids[2] = create_process(2);   
        
        if (pids[2] == 0) {
            // процесс 2
            print_ids("Процесс 2 перед exec");
            printf("Процесс %d выполняет exec для команды 'ps aux'\n", getpid());
            
            char *args[] = {"ps", "aux", NULL};
            execvp("ps", args);
            
            perror("exec failed");
            exit(EXIT_FAILURE);
        } else {
            // процесс 1
            pids[3] = create_process(3);
            
            if (pids[3] == 0) {
                // процесс 3
                pids[5] = create_process(5);
                
                if (pids[5] == 0) {
                    // процесс 5
                    print_ids("Процесс 5 перед завершением");
                    printf("Процесс с ID %d и PPID %d завершает работу\n", getpid(), getppid());
                    exit(EXIT_SUCCESS);
                } else {
                    // процесс 3
                    waitpid(pids[5], NULL, 0);
                    print_ids("Процесс 3 перед завершением");
                    printf("Процесс с ID %d и PPID %d завершает работу\n", getpid(), getppid());
                    exit(EXIT_SUCCESS);
                }
            } else {
                // процесс 2
                pids[4] = create_process(4);
                
                if (pids[4] == 0) {
                    // процесс 4
                    pids[6] = create_process(6);
                    
                    if (pids[6] == 0) {
                        //процесс 6
                        pids[7] = create_process(7);
                        
                        if (pids[7] == 0) {
                            // процесс 7
                            print_ids("Процесс 7 перед завершением");
                            printf("Процесс с ID %d и PPID %d завершает работу\n", getpid(), getppid());
                            exit(EXIT_SUCCESS);
                        } else {
                            // процесс 6
                            waitpid(pids[7], NULL, 0);
                            print_ids("Процесс 6 перед завершением");
                            printf("Процесс с ID %d и PPID %d завершает работу\n", getpid(), getppid());
                            exit(EXIT_SUCCESS);
                        }
                    } else {
                        // процесс 4
                        waitpid(pids[6], NULL, 0);
                        print_ids("Процесс 4 перед завершением");
                        printf("Процесс с ID %d и PPID %d завершает работу\n", getpid(), getppid());
                        exit(EXIT_SUCCESS);
                    }
                } else {
                    // процесс 2
                    waitpid(pids[3], NULL, 0);
                    waitpid(pids[4], NULL, 0);
                }
            }
            waitpid(pids[2], NULL, 0);
        }
    } else {
        // процесс 0, корневой
        waitpid(pids[1], NULL, 0);
        
        print_ids("Корневой процесс перед завершением");
        printf("Процесс с ID %d и PPID %d завершает работу\n", getpid(), getppid());
    }
    
    return 0;
}