#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_NAME "/mq_test"
#define MAX_SIZE 1024
#define NUM_MESSAGES 5

int main(void) {
    mqd_t mq;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;         
    attr.mq_msgsize = MAX_SIZE; 
    attr.mq_curmsgs = 0;     

    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_SIZE];
    printf("Sender: sending %d messages\n", NUM_MESSAGES);
    for (int i = 0; i < NUM_MESSAGES; i++) {
        snprintf(buffer, MAX_SIZE, "Message %d", i);

        if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
            perror("mq_send");
            exit(EXIT_FAILURE);
        }
        printf("Sent: \"%s\"\n", buffer);
        sleep(1);
    }

    mq_close(mq);
    return 0;
}
