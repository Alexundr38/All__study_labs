//скрипт для создания псевдораспаралеливания
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int value = 0;

void do_func()
{   
    for (int i = 0; i < 5; i++) {
        printf("PID = %d, PPID = %d in stage %d\n", getpid(), getppid(), value);
        value++;
        sleep(1);
    }
}

int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else {
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        do_func();
        printf("%d process finished\n", getpid());
    }
}
