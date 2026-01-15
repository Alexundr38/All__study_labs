//скрипт для получения кванта времени в RR
#include <stdio.h>
#include <sched.h>
#include <time.h>

int main()
{
    struct timespec quantum;
    sched_rr_get_interval(0, &quantum);
    printf("quantum = %lds, %ldns\n", quantum.tv_sec, quantum.tv_nsec);
    return 0;
}
