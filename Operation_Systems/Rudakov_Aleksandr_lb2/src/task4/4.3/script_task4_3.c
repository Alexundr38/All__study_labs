//скрипт для демонстрации общего пространства потоков
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int value = 0;

void* thread_function(void* arg) {
    for (int i = 0; i < 10; i++) {
        value++;
        printf("Thread (%d) increment value to %d\n", gettid(), value);
        sleep(1);   
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Shared variable value: %d\n", value);

    return 0;
}
