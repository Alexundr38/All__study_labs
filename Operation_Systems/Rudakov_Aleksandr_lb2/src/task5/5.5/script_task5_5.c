//скрипт для показа возможности использовать разные политики одновременно
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void set_policy(pid_t pid, int policy, int priority) {
    struct sched_param param = {.sched_priority = priority};
    if (sched_setscheduler(pid, policy, &param)) {
        perror("sched_setscheduler");
    }
}

void cpu_loop(const char *name) {
    while (1) {
        volatile unsigned long i;
        for (i = 0; i < 1000000000UL; i++);
        printf("%s running\n", name);
    }
}

int main() {
    pid_t pid_a = fork();
    if (pid_a == 0) {
        set_policy(0, SCHED_RR, 50);
        cpu_loop("Process A (SCHED_RR)");
        return 0;
    }

    pid_t pid_b = fork();
    if (pid_b == 0) {
        set_policy(0, SCHED_FIFO, 50);
        cpu_loop("Process B (SCHED_FIFO)");
        return 0;
    }

    pid_t pid_c = fork();
    if (pid_c == 0) {
        set_policy(0, SCHED_OTHER, 0);
        nice(19);
        cpu_loop("Process C (SCHED_OTHER)");
        return 0;
    }

    wait(NULL);
    return 0;
}
