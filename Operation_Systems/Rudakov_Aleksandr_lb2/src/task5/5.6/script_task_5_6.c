//скрипт для показа политики потоков одного процесса
#include <stdio.h>
#include <pthread.h>
#include <sched.h>

void* thread_func(void* arg) {
    int policy;
    struct sched_param param;

    pthread_getschedparam(pthread_self(), &policy, &param);

    const char* policy_name;
    switch (policy) {
        case SCHED_OTHER: policy_name = "SCHED_OTHER (CFS)"; break;
        case SCHED_FIFO:  policy_name = "SCHED_FIFO"; break;
        case SCHED_RR:    policy_name = "SCHED_RR"; break;
        default:          policy_name = "UNKNOWN"; break;
    }

    printf("Thread ID %lu: policy = %s, priority = %d\n",
           (unsigned long)pthread_self(), policy_name, param.sched_priority);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_func, NULL);
    pthread_create(&thread2, NULL, thread_func, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
