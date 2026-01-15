//скрипт для смены приоритета в процессе выполнения
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    while (1) {
        printf("PID=%d, nice=%d\n", getpid(), getpriority(PRIO_PROCESS, 0));
        sleep(3);
    }
    return 0;
}
