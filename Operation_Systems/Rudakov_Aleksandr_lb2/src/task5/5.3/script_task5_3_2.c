//скрипт для определения максимального и минимального приоритета в SCHED_FIFO
#include <stdio.h>
#include <sched.h>

int main() {
    int min = sched_get_priority_min(SCHED_FIFO);
    int max = sched_get_priority_max(SCHED_FIFO);
    printf("SCHED_FIFO: min = %d, max = %d\n", min, max);
    return 0;
}
