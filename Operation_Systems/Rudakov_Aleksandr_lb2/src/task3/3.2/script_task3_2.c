//скрипт для демонстрации родителем множества процессов потомков
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void child_process(int id) {
    printf("son %d (PID: %d) started\n", id, getpid());
    sleep(id * 3);
    printf("son %d (PID: %d) finished\n", id, getpid());
    exit(id * 3);
}

int main() {
    pid_t pids[3];
    int status;

    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            child_process(i + 1);
        }
    }
    sleep(1);

    for (int i = 0; i < 3; i++) {
        pid_t target_pid = pids[i]; 
        printf("father wait son with PID: %d\n", target_pid);
        waitpid(target_pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("son with PID %d end with code: %d\n", target_pid, WEXITSTATUS(status));
        } else {
            printf("son with PID %d end bad\n", target_pid);
        }
    }

    return 0;
}
