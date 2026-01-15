//скрипт первого процесса
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    printf("son1: PID = %d\n", getpid());
    pause();
    return 0;
}
