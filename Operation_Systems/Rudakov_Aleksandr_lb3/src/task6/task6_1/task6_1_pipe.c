#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main() {
    int pipefd[2];
    char buf[256];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[1]);
        FILE *file = fopen("./output.txt", "a");

        read(pipefd[0], buf, 50);
        printf("The child process received the message %s\n", buf);

        fprintf(file, "%s", buf);
        printf("The child process wrote the received message to a file\n");

        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    } else {
        close(pipefd[0]);
        FILE *file = fopen("./input.txt", "r");
        fread(buf, sizeof(char), 50, file);
        printf("The parent process reads the information: %s\n", buf);

        write(pipefd[1], buf, 50);
        printf("The parent process sends information to the child\n");

        close(pipefd[1]);
        fclose(file);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}
