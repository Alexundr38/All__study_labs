//скрипт для фиксации таблицы состояния процессов
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    system("ps -l > father_processes_before_wait.txt");
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        execl("./son2_2", "son2_2", NULL);
        perror("Exec failed");
        exit(1);
    } else {
        printf("Father process started with PID: %d\n", getpid());
        printf("Child process created with PID: %d\n", pid);

        wait(NULL);
        system("ps -l > father_processes_after_wait.txt");
        printf("Father process finished.\n");
    }

    return 0;
}
