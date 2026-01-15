#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/my_fifo"
#define BUFFER_SIZE 1024
#define NUM_MESSAGES 5

int main(void) {
    if (access(FIFO_PATH, F_OK) == -1) {
        if (mkfifo(FIFO_PATH, 0644) == -1) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
        printf("FIFO '%s' successfully created.\n", FIFO_PATH);
    } else {
        printf("FIFO '%s' already exists.\n", FIFO_PATH);
    }
    
    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    char buffer[BUFFER_SIZE];
    printf("Sender: we send %d messages\n", NUM_MESSAGES);
    for (int i = 0; i < NUM_MESSAGES; i++) {
        snprintf(buffer, BUFFER_SIZE, "Message %d", i);
        if (write(fd, buffer, strlen(buffer) + 1) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        printf("Send: \"%s\"\n", buffer);
        sleep(1);
    }
    
    close(fd);
    printf("Sender: completed sending messages.\n");
    return 0;
}
