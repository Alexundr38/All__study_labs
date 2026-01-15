#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define DEF_KEY_FILE "key"
#define SEM_READ_NAME "/sem_read"
#define SEM_WRITE_NAME "/sem_write"

typedef struct {
    long type;
    char buf[100];
} Message;

Message *p_msg;
int shmemory;
sem_t *sem_read, *sem_write;

void intHandler(int sig) {
    printf("\nAn interrupt signal has been received (SIGINT)\n");
    printf("I'm starting resource cleanup....\n");
    
    printf("Detaching shared memory...\n");
    shmdt(p_msg);
    
    printf("Deleting shared memory...\n");
    shmctl(shmemory, IPC_RMID, 0);
    
    printf("Closing semaphores...\n");
    sem_close(sem_read);
    sem_close(sem_write);
    
    printf("Deleting named semaphores...\n");
    sem_unlink(SEM_READ_NAME);
    sem_unlink(SEM_WRITE_NAME);
    
    printf("The server is shutting down.\n");
    exit(0);
}

int main(int argc, char **argv) {
    printf("The server is running \n");
    
    char keyFile[100] = {0};
    strcpy(keyFile, (argc < 2) ? DEF_KEY_FILE : argv[1]);
    printf("The key file is being used: %s\n", keyFile);

    printf("Generating an IPC key...\n");
    key_t key = ftok(keyFile, 'Q');
    if (key < 0) {
        perror("Error during key generation");
        exit(1);
    }
    printf("The IPC key has been successfully generated: %d\n", key);

    printf("Creating shared memory...\n");
    shmemory = shmget(key, sizeof(Message), IPC_CREAT | 0666);
    if (shmemory < 0) {
        perror("Error when creating shared memory");
        exit(1);
    }
    printf("Shared memory has been created, ID: %d\n", shmemory);

    printf("Connecting to shared memory...\n");
    p_msg = (Message *)shmat(shmemory, 0, 0);
    if (p_msg == (void *)-1) {
        perror("Error when connecting to shared memory");
        exit(1);
    }
    printf("Successfully connected to shared memory\n");

    printf("Initializing semaphores...\n");
    printf("Writing semaphore\n");
    sem_write = sem_open(SEM_WRITE_NAME, O_CREAT, 0666, 1);
    if (sem_write == SEM_FAILED) {
        perror("Error when creating a writing semaphore");
        exit(1);
    }
    
    printf("Reading semaphore\n");
    sem_read = sem_open(SEM_READ_NAME, O_CREAT, 0666, 0);
    if (sem_read == SEM_FAILED) {
        perror("Error when creating a reading semaphore");
        exit(1);
    }

    printf("Installing the SIGINT signal handler...\n");
    signal(SIGINT, intHandler);

    printf("\nThe server is ready to receive messages. Waiting for the client...\n");

    while (1) {
        printf("Waiting for a message from the client...\n");
        sem_wait(sem_read);
        printf("A new message has been received: %s", p_msg->buf);
        sem_post(sem_write);
        printf("Ready to receive the next message\n\n");
    }
    
    return 0;
}
