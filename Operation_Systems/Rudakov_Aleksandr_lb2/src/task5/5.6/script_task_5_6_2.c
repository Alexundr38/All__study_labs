//скрипт для изменения приоритета в потоках
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

void *thread_func(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 5; i++) {
        printf("Thread %d (priority %d) iteration %d\n", 
               id, sched_get_priority_max(SCHED_FIFO), i);
        usleep(100000);
    }
    return NULL;
}

void *thread_func_rt(void *arg) {
    struct sched_param param;
    param.sched_priority = 50;
    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param)) {
        perror("pthread_setschedparam");
    }
    
    int id = *(int *)arg;
    for (int i = 0; i < 5; i++) {
        printf("REALTIME Thread %d (priority %d) iteration %d\n", 
               id, param.sched_priority, i);
        usleep(100000);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    int id1 = 1, id2 = 2, id3 = 3;
    
    pthread_create(&t1, NULL, thread_func, &id1);
    pthread_create(&t2, NULL, thread_func, &id2);
    
    pthread_create(&t3, NULL, thread_func_rt, &id3);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    
    return 0;
}
