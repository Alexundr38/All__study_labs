//скрипт для разделения процесса на потоки
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>

#define STACK_SIZE (1024 * 1024)

void* thread_function(void* arg) {
    int thread_num = *(int*)arg;
    printf("Thread %d (pthread) start, PID = %d, TID = %ld\n", thread_num, getpid(), syscall(SYS_gettid));
    sleep(10);
    printf("Thread %d (pthread) finish\n", thread_num);
    return NULL;
}

int clone_function(void* arg) {
    int thread_num = *(int*)arg;
    printf("Thread %d (clone) start, PID = %d, TID = %ld\n", thread_num, getpid(), syscall(SYS_gettid));
    sleep(10);
    printf("Thread %d (clone) finish\n", thread_num);
    return 0;
}

int main() {
    pthread_t pthread_id;
    int thread_num1 = 1, thread_num2 = 2;
    void* stack = malloc(STACK_SIZE);

    if (stack == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&pthread_id, NULL, thread_function, &thread_num2) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    int clone_pid = clone(clone_function, stack + STACK_SIZE, CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD, &thread_num1);
    if (clone_pid == -1) {
        perror("clone");
        exit(EXIT_FAILURE);
    }

    pthread_join(pthread_id, NULL);

    waitpid(clone_pid, NULL, 0);

    free(stack);
    printf("Main thread finish\n");

    return 0;
}
