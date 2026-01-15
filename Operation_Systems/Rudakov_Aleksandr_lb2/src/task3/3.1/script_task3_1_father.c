//скрипт для демонстрации разных реакций процессов на поступление сигнала kill
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    pid_t son1, son2, son3;

    son1 = fork();
    if (son1 == 0) {
        execl("./script_task3_1_son1", "script_task3_1_son1", NULL);
    }

    son2 = fork();
    if (son2 == 0) {
        execl("./script_task3_1_son2", "script_task3_1_son2", NULL);
    }

    son3 = fork();
    if (son3 == 0) {
        execl("./script_task3_1_son3", "script_task3_1_son3", NULL);
    }

    system("ps -s > processes_before.txt");

    sleep(2);

    kill(son1, SIGUSR1);
    kill(son2, SIGUSR1);
    kill(son3, SIGUSR1);

    system("ps -s > processes_after.txt");
    wait(NULL);
    wait(NULL);
    wait(NULL);


    return 0;
}
