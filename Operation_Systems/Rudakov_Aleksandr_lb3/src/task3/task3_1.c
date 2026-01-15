#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>



void sigusr1_handler(int sig) {
    printf("Caught SIGUSR1\n");
}


void sigusr2_handler(int sig) {
    printf("Caught SIGUSR2\n");
}


int main() {
    struct sigaction sigact;

    sigact.sa_handler = sigusr1_handler;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    if (sigaction(SIGUSR1, &sigact, NULL) < 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    sigact.sa_handler = sigusr2_handler; 
    if (sigaction(SIGUSR2, &sigact, NULL) < 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);

    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    printf("SIGUSR1 is blocked. Send SIGUSR1 to unblock.\n");

    while (1) {
    }

    return 0;
}
