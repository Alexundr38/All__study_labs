//скрипт для уточнения наследования clone
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

#define STACK_SIZE (1024 * 1024)

int child_func(void *arg) {
    printf("Child PID: %d\n", getpid());

    int *shared_var = (int *)arg;
    printf("Child shared_var before: %d\n", *shared_var);
    (*shared_var)++;
    printf("Child shared_var after: %d\n", *shared_var);

    int fd = open("text_task6_4.txt", O_WRONLY | O_APPEND);
    write(fd, "Child wrote this\n", 17);
    close(fd);

    printf("send SIGUSR1\n");
    raise(SIGUSR1);

    return 0;
}

void signal_handler(int sig) {
    printf("Process %d received signal %d\n", getpid(), sig);
}

int main() {
    char *stack = malloc(STACK_SIZE);
    int *shared_var = malloc(sizeof(int));
    *shared_var = 100;

    signal(SIGUSR1, signal_handler);

    int fd = open("text_task6_4.txt",  O_RDWR | O_CREAT, 0644);
    write(fd, "Parent wrote this\n", 18);

    printf("Parent PID: %d\n", getpid());

    int flags = CLONE_VM | CLONE_FILES | CLONE_SIGHAND | SIGCHLD;

    pid_t child_pid = clone(child_func, stack + STACK_SIZE, flags, shared_var);
    if (child_pid == -1) {
        perror("clone");
        return 1;
    }

    waitpid(child_pid, NULL, 0);

    printf("Parent shared_var: %d\n", *shared_var);

    lseek(fd, 0, SEEK_SET);
    char buf[100];
    read(fd, buf, sizeof(buf));
    printf("Parent read:\n%s", buf);

    free(stack);
    free(shared_var);
    close(fd);
    return 0;
}
