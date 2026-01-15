//скрипт для создания процессов разными функциями семейства exec
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    char *args[] = {"./son2_3", "arg1", "arg2", "arg3", NULL};

    char *env[] = {"ENV1=value1", "ENV2=value2", "ENV3=value3", NULL};

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Using execl():\n");
        execl("./son2_3", "./son2_3", "arg1", "arg2", "arg3", NULL);
        perror("Exec failed");
        exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Using execv():\n");
        execv("./son2_3", args);
        perror("Exec failed");
        exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Using execle():\n");
        execle("./son2_3", "./son2_3", "arg1", "arg2", "arg3", NULL, env);
        perror("Exec failed");
        exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Using execve():\n");
        execve("./son2_3", args, env);
        perror("Exec failed");
        exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Using execlp():\n");
        execlp("./son2_3", "./son2_3", "arg1", "arg2", "arg3", NULL);
        perror("Exec failed");
        exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (pid == 0) {
        printf("Using execvp():\n");
        execvp("./son2_3", args);
        perror("Exec failed");
        exit(1);
    }
    wait(NULL);

    printf("Father process finished.\n");

    return 0;
}
