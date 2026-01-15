//скрипт для вывода политики
#include <stdio.h>
#include <sched.h>
#include <sys/resource.h>

int main() {
    int pid = getpid();
    
    int policy = sched_getscheduler(pid);
    printf("PID = %d\n", pid);
    printf("Policy: ");
    switch(policy) {
        case SCHED_OTHER: printf("SCHED_OTHER (CFS)\n"); break;
        case SCHED_FIFO:  printf("SCHED_FIFO\n"); break;
        case SCHED_RR:    printf("SCHED_RR\n"); break;
        default:          printf("Unknown\n"); break;
    }
    
    // Получаем nice value
    int nice = getpriority(PRIO_PROCESS, pid);
    printf("Nice value: %d\n", nice);
    
    return 0;
}
