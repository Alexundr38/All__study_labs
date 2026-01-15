//скрипт второго процесса
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    printf("son2: PID = %d\n", getpid());
    signal(SIGUSR1, SIG_IGN);
    sleep(3);
    printf("son2: finished\n");
    return 0;
}
