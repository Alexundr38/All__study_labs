#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
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

static struct sembuf readEna[1] = {{0, -1, 0}};
static struct sembuf setWriteEna[1] = {{1, 1, 0}};

Message *p_msg;
int shmemory;
int semaphore;

void intHandler(int sig) {
    printf("\nAn interrupt signal has been received(SIGINT)\n");
    printf("I'm starting to clean up the resources...\n");
    
    if (shmdt(p_msg) < 0) {
        printf("Error when disabling shared memory\n");
        exit(1);
    }
    printf("Shared memory has been successfully disabled\n");
    
    if (shmctl(shmemory, IPC_RMID, 0) < 0) {
        printf("Error deleting shared memory\n");
        exit(1);
    }
    printf("Shared memory has been successfully deleted\n");
    
    if (semctl(semaphore, 0, IPC_RMID) < 0) {
        printf("Error when deleting a semaphore\n");
        exit(1);
    }
    printf("Semaphore successfully deleted\n");
    
    printf("Shutting down the server\n");
    exit(0);
}

int main(int argc, char **argv) {
    printf("The server is running\n");
    
    char keyFile[100] = {0};
    strcpy(keyFile, (argc < 2) ? DEF_KEY_FILE : argv[1]);
    printf("The key file is being used: %s\n", keyFile);

    key_t key = ftok(keyFile, 'Q');
    if (key < 0) {
        printf("Mistake: couldn't get the key for the file%s\n", keyFile);
        exit(1);
    }
    printf("The IPC key was successfully received: %d\n", key);

    shmemory = shmget(key, sizeof(Message), IPC_CREAT | 0666);
    if (shmemory < 0) {
        printf("Mistake: failed to create shared memory\n");
        exit(1);
    }
    printf("Shared memory has been created successfully, ID: %d\n", shmemory);

    p_msg = (Message *)shmat(shmemory, 0, 0);
    if (p_msg == (void *)-1) {
        printf("Mistake: couldn't connect to shared memory\n");
        exit(1);
    }
    printf("Successfully connected to shared memory at: %p\n", p_msg);

    semaphore = semget(key, 2, IPC_CREAT | 0666);
    if (semaphore < 0) {
        printf("Mistake: failed to create a semaphore\n");
        exit(1);
    }
    printf("The semaphore was created successfully, ID: %d\n", semaphore);

    signal(SIGINT, intHandler);
    printf("The signal handler is configured\n");

    semop(semaphore, setWriteEna, 1);
    printf("The server is ready to receive messages\n\n");

    while (1) {
        printf("Waiting for a message from the client...\n");
        semop(semaphore, readEna, 1);
        printf("A new message has been received from the client: %s", p_msg->buf);
        semop(semaphore, setWriteEna, 1);
        printf("Ready to receive the next message\n\n");
    }
    
    return 0;
}
