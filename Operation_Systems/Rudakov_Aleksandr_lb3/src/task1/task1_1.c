#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

pthread_t t2;
volatile sig_atomic_t stop_thread = 0;

double get_time_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}


void sigusr1_handler(int signum) {
    printf("Second thread: SIGUSR1 signal received, continue working.\n");
}


void sigterm_handler(int signum) {
    printf("Second thread: SIGTERM received, ending...\n");
    stop_thread = 1;
}


void* second_thread_function(void* arg) {
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGTERM, sigterm_handler);

    printf("The second thread is running.\n");

    while (!stop_thread) {
        printf("The second thread is working...\n");
        sleep(1);
    }

    printf("The second thread is completed.\n");
    return NULL;
}


void* first_thread_function(void* arg) {
    double start_time, sigusr1_time, sigterm_time;

    start_time = get_time_seconds();
    if (pthread_create(&t2, NULL, second_thread_function, NULL) != 0) {
        perror("Error when creating the second thread");
        exit(EXIT_FAILURE);
    }

    sleep(2);
    sigusr1_time = get_time_seconds();
    printf("The first thread: sending SIGUSR1 (time: %.2f s)\n", sigusr1_time - start_time);
    pthread_kill(t2, SIGUSR1);

    sleep(3);
    sigterm_time = get_time_seconds();
    printf("The first thread: sending SIGTERM (time: %.2f s)\n", sigterm_time - start_time);
    pthread_kill(t2, SIGTERM);

    pthread_join(t2, NULL);
    
    double end_time = get_time_seconds();
    printf("The second thread has been deleted. Working time: %.2f s.\n", end_time - start_time);
    printf("The first thread is completed.\n");

    return NULL;
}

int main() {
    pthread_t t1;

    if (pthread_create(&t1, NULL, first_thread_function, NULL) != 0) {
        perror("Error when creating the first thread");
        exit(EXIT_FAILURE);
    }

    pthread_join(t1, NULL);
    printf("The program is completed.\n");

    return 0;
}
