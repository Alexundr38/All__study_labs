#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define DEF_KEY_FILE "key"

typedef struct {
    long type;
    char buf[100];
} Message;

static struct sembuf writeEna[1] = {{1, -1, 0}};
static struct sembuf setReadEna[1] = {{0, 1, 0}};

int main(int argc, char **argv) {
    printf("The client is running\n");
    
    char keyFile[100] = {0};
    strcpy(keyFile, (argc < 2) ? DEF_KEY_FILE : argv[1]);
    printf("The key file is being used: %s\n", keyFile);

    key_t key = ftok(keyFile, 'Q');
    if (key < 0) {
        printf("Error: couldn't get the key for the file %s\n", keyFile);
        exit(1);
    }
    printf("The IPC key was successfully received: %d\n", key);

    int shmemory = shmget(key, sizeof(Message), 0666);
    if (shmemory < 0) {
        printf("Error: couldn't connect to shared memory\n");
        exit(1);
    }
    printf("Successful connection to shared memory, ID: %d\n", shmemory);

    Message *p_msg = (Message *)shmat(shmemory, 0, 0);
    if (p_msg == (void *)-1) {
        printf("Error: couldn't attach shared memory\n");
        exit(1);
    }
    printf("The shared memory has been successfully attached to: %p\n", p_msg);

    int semaphore = semget(key, 2, 0666);
    if (semaphore < 0) {
        printf("Error: couldn't connect to semaphore\n");
        exit(1);
    }
    printf("Successful connection to the semaphore, ID: %d\n", semaphore);

    printf("\nThe client is ready to send messages to the server\n");
    printf("To complete the work, enter an empty line\n\n");

    char buf[100];
    while (1) {
        printf("Enter a message for the server: ");
        fgets(buf, 100, stdin);
        
        if (strlen(buf) == 1 && buf[0] == '\n') {
            printf("\nClient Shutdown...\n");
            break;
        }

        printf("Sending a message to the server...\n");
        semop(semaphore, writeEna, 1);
        sprintf(p_msg->buf, "%s", buf);
        semop(semaphore, setReadEna, 1);
        printf("The message has been sent successfully!\n\n");
    }

    printf("Detaching from shared memory...\n");
    shmdt(p_msg);
    printf("The client has completed the work\n");
    
    return 0;
}
