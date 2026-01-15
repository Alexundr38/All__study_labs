//скрипт для фиксации таблицы состояния процессов
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Son process started with PID: %d\n", getpid());

    system("ps -l > son_processes.txt");

    printf("Son process finished.\n");
    return 0;
}
