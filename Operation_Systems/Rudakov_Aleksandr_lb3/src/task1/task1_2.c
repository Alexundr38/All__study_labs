
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

pthread_t t2;


double get_time_seconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}


void sigusr1_handler(int signum) {
    printf("Second thread: SIGUSR1 signal received! The work continues...\n");
}


void sigterm_handler(int signum) {
    printf("\nThe second thread of the SIGTERM handler is running!\n");
    printf("Shutting down the second thread\n\n");
    pthread_exit(NULL);
}


void* second_thread_function(void* arg) {
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGTERM, sigterm_handler);

    printf("Second thread: Running.\n");

    while (1) {
        printf("Second thread: It works...\n");
        sleep(1);
    }
}


void* first_thread_function(void* arg) {
    double start_time, sigusr1_time, sigterm_time;

    start_time = get_time_seconds();
    if (pthread_create(&t2, NULL, second_thread_function, NULL) != 0) {
        perror("Error when creating the second thread");
        exit(EXIT_FAILURE);
    }

    sleep(3);
    sigusr1_time = get_time_seconds();
    printf("First thread: Sending SIGUSR1 -> (time: %.2f s)\n", sigusr1_time - start_time);
    pthread_kill(t2, SIGUSR1);

    sleep(5);
    sigterm_time = get_time_seconds();
    printf("First thread: Sending SIGTERM -> (time: %.2f s)\n", sigterm_time - start_time);
    pthread_kill(t2, SIGTERM);

    pthread_join(t2, NULL);
    
    double end_time = get_time_seconds();
    printf("First thread: The second thread is deleted. Working time: %.2f s.\n", end_time - start_time);
    printf("First thread: Coming to an end...\n");

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
