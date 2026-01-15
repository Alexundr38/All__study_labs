//скрипт вызываемый через exec
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Son process started in script_task2_4_son.c with PID: %d, PPID: %d\n", getpid(), getppid());
    sleep(5);
    printf("Son process finished.\n");
    return 0;
}
