//скрипт для определения максимального и минимального приоритета в SCHED_RR
#include <stdio.h>
#include <sched.h>

int main() {
    int min = sched_get_priority_min(SCHED_RR);
    int max = sched_get_priority_max(SCHED_RR);
    printf("SCHED_RR: min = %d, max = %d\n", min, max);
    return 0;
}
