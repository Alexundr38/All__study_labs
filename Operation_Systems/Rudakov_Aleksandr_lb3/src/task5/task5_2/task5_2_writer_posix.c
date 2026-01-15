#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char **argv) {
    char keyFile[100] = {0};
    strcpy(keyFile, (argc < 2) ? DEF_KEY_FILE : argv[1]);

    key_t key = ftok(keyFile, 'Q');
    if (key < 0) { perror("Error ftok"); exit(1); }

    int shmemory = shmget(key, sizeof(Message), 0666);
    if (shmemory < 0) { perror("Error shmget"); exit(1); }

    Message *p_msg = (Message *)shmat(shmemory, 0, 0);
    if (p_msg == (void *)-1) { perror("Error shmat"); exit(1); }

    sem_t *sem_read = sem_open(SEM_READ_NAME, O_CREAT, 0666, 0);
    if (sem_read == SEM_FAILED) { perror("Error sem_open sem_read"); exit(1); }
    sem_t *sem_write = sem_open(SEM_WRITE_NAME, O_CREAT, 0666, 1);
    if (sem_write == SEM_FAILED) { perror("Error sem_open sem_write"); exit(1); }

    char buf[100];
    while (1) {
        printf("Enter a message for the server. An empty line to exit\n");
        fgets(buf, 100, stdin);
        if (strlen(buf) == 1 && buf[0] == '\n') {
            printf("End\n");
            break;
        }
        sem_wait(sem_write);
        sprintf(p_msg->buf, "%s", buf);
        sem_post(sem_read);
    }
    shmdt(p_msg);
    sem_close(sem_read);
    sem_close(sem_write);
    return 0;
}
