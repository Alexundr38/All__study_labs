//скрипт для изменения политики одного потока из всех потоков процесса
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <sys/syscall.h>

void print_scheduling_info(const char* thread_name) {
    int policy;
    struct sched_param param;
    pthread_getschedparam(pthread_self(), &policy, &param);

    const char* policy_name;
    switch (policy) {
        case SCHED_OTHER: policy_name = "SCHED_OTHER"; break;
        case SCHED_FIFO:  policy_name = "SCHED_FIFO"; break;
        case SCHED_RR:    policy_name = "SCHED_RR"; break;
        default:          policy_name = "UNKNOWN"; break;
    }

    printf("%s: policy = %s, priority = %d (TID = %ld)\n", thread_name, policy_name, param.sched_priority, syscall(SYS_gettid));
}

void* normal_thread(void* arg) {
    while (1) {
        volatile unsigned long i;
        for (i = 0; i < 100000000UL; i++);
        print_scheduling_info("Normal thread");
    }
    return NULL;
}

void* fifo_thread(void* arg) {
    print_scheduling_info("Thread before policy change");

    struct sched_param param = { .sched_priority = 50 };
    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param) != 0) {
        perror("Failed to set SCHED_FIFO");
    }

    while (1) {
        volatile unsigned long i;
        for (i = 0; i < 100000000UL; i++);
        print_scheduling_info("Thread after policy change");
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, normal_thread, NULL);
    pthread_create(&thread2, NULL, normal_thread, NULL);
    pthread_create(&thread3, NULL, fifo_thread, NULL); 

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}
