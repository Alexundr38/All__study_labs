//Скрипт для показа наследования приоритетов и политики планирования
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sched.h>

int main() {
    struct sched_param param = { .sched_priority = 50 };
    sched_setscheduler(0, SCHED_RR, &param);
    nice(5);
    printf("Parent nice: %d\n", getpriority(PRIO_PROCESS, 0));
    printf("Parent scheduler: %d\n", sched_getscheduler(0));

    pid_t pid = fork();
    if (pid == 0) {
        printf("Child nice: %d\n", getpriority(PRIO_PROCESS, 0));
        printf("Child scheduler: %d\n", sched_getscheduler(0));
        nice(3);
        printf("Change child nice\n");
        printf("Child nice: %d\n", getpriority(PRIO_PROCESS, 0));
        printf("Child scheduler: %d\n", sched_getscheduler(0));
        execl("/bin/sleep", "sleep", "1", NULL);
    } else {
        wait(NULL);
        printf("Parent nice: %d\n", getpriority(PRIO_PROCESS, 0));
        printf("Parent scheduler: %d\n", sched_getscheduler(0));
    }
    return 0;
}
