//скрипт для сравнения процессов с равными приоритетами в SCHED_OTHER
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

void set_fifo_priority(int priority) {
    struct sched_param param;
    param.sched_priority = priority;
    if (sched_setscheduler(0, SCHED_OTHER, &param) == -1) {
        perror("sched_setscheduler");
    }
}

void child_process(int id) {
    set_fifo_priority(0);
    printf("%d (PID: %d) start\n", id, getpid());
    for (int i = 0; i < 5; i++) {
        printf("%d (PID: %d) work (i = %d)\n", id, getpid(), i);
        for (int j = 0; j < 600000000; j++);
    }
    printf("%d (PID: %d) finish\n", id, getpid());
}

int main() {
    pid_t p1, p2, p3;

    p1 = fork();
    if (p1 == 0) {
        child_process(1);
        return 0;
    }

    p2 = fork();
    if (p2 == 0) {
        child_process(2);
        return 0;
    }

    p3 = fork();
    if (p3 == 0) {
        child_process(3);
        return 0;
    }

    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    waitpid(p3, NULL, 0);

    return 0;
}
