//скрипт для сравнения процессов с разными приоритетами в SCHED_RR с использованием sched_yield
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <stdlib.h>

void set_fifo_priority(int priority) {
    struct sched_param param;
    param.sched_priority = priority;
    if (sched_setscheduler(0, SCHED_RR, &param) == -1) {
        perror("sched_setscheduler");
        exit(1);
    }
}

void child_process(int id, int priority) {
    set_fifo_priority(priority);
    printf("%d (PID: %d, priority = %d) start\n", id, getpid(), priority);

    if (id == 2){
        printf("%d (PID: %d, priority = %d) call sched_yield\n", id, getpid(), priority);
        sched_yield();
    }

    for (int i = 0; i < 3; i++) {
        printf("%d (PID: %d, priority = %d) work (i = %d)\n", id, getpid(), priority, i);
        for (int j = 0; j < 100000000; j++);
    }
    printf("%d (PID: %d, priority = %d) finish\n", id, getpid(), priority);
}

int main() {
    pid_t p1, p2, p3;

    p1 = fork();
    if (p1 == 0) {
        child_process(1, 10);
        return 0;
    }

    p2 = fork();
    if (p2 == 0) {
        child_process(2, 50);
        return 0;
    }

    p3 = fork();
    if (p3 == 0) {
        child_process(3, 90);
        return 0;
    }

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    waitpid(p3, NULL, 0);

    return 0;
}
