//скрипт, вызываемый через exec
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    printf("==========================\n");
    printf("Son process started with PID: %d\n", getpid());

    printf(" Arguments:\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    printf(" Environment variables:\n");
    for (int i = 0; envp[i] != NULL; i++) {
        printf("envp[%d] = %s\n", i, envp[i]);
    }

    printf("Son process finished.\n");
    printf("==========================\n");
    return 0;
}
