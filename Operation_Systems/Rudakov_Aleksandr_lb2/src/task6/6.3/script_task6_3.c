//скрипт для показа диспозиции и наследования сигнала
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void signal_handler(int sig) {
    printf("Process %d received signal %d\n", getpid(), sig);
}

int main() {
    signal(SIGUSR1, signal_handler);

    signal(SIGUSR2, SIG_IGN);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGTERM);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    printf("Parent PID: %d\n", getpid());

    pid_t child_pid = fork();

    if (child_pid == 0) {
        printf("Child PID: %d (after fork)\n", getpid());

        printf("Child: Testing signal handlers before exec...\n");
        raise(SIGUSR1);
        raise(SIGUSR2);
        raise(SIGTERM);

        printf("Child: Executing sleep...\n");
        execl("/bin/sleep", "sleep", "5", NULL);

    } else {
        sleep(1); 
        printf("Parent: Sending signals to child after exec...\n");
        kill(child_pid, SIGUSR1);
        kill(child_pid, SIGUSR2);
        kill(child_pid, SIGTERM); 

        wait(NULL);
        printf("Parent: Child process finished.\n");
    }

    return 0;
}
