//скрипт третьего процесса
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig) {
    printf("son3: signal %d has been received\n", sig);
}

int main() {
    printf("son3: PID = %d\n", getpid());
    signal(SIGUSR1, handle_signal);
    pause();
    printf("son3: finished\n");
    return 0;
}
