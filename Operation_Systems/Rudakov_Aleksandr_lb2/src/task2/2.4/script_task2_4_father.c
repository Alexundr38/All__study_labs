//скрипт для фиксаций разных состояний завершения процесса
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void normal_completion() {
    printf("\n--- Situation 1: Normal completion ---\n");
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        execl("./son2_4", "son2_4", NULL);
        perror("Exec failed");
        exit(1);
    } else {
        // Код родителя
        printf("Father process waiting for son to finish...\n");
        system("ps -l > parent_wait.txt");
        wait(NULL);
        printf("Father process finished.\n");
    }
}

void parent_exits_first() {
    printf("\n--- Situation 2: Parent exits first ---\n");
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        sleep(2);
        printf("Son process after parent exit: PID = %d, PPID = %d\n", getpid(), getppid());
        execl("./son2_4", "son2_4", NULL);
        perror("Exec failed");
        exit(1);
    } else {
        printf("Son process before parent exit: PID = %d, PPID = %d\n", getpid(), getppid());
        printf("Father process exiting without waiting for son...\n");
        system("ps -l > parent_exit.txt");
        exit(0);
    }
}

void zombie_state() {
    printf("\n--- Situation 3: Zombie state ---\n");
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        execl("./son2_4", "son2_4", NULL);
        perror("Exec failed");
        exit(1);
    } else {
        printf("Father process not waiting for son...\n");
        sleep(10); 
        system("ps -l > zombie_state.txt");
    }
}

int main() {
    normal_completion();

    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        parent_exits_first();
        exit(0);
    } else {
        wait(NULL);
        sleep(5);
    }

    zombie_state();

    return 0;
}
