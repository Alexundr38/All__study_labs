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
    char buffer[MAX_SIZE + 1];

    mq = mq_open(QUEUE_NAME, O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    if (mq_getattr(mq, &attr) == -1) {
        perror("mq_getattr");
        exit(EXIT_FAILURE);
    }
    printf("Recipient: Queue attributes: maxmsg = %ld, msgsize = %ld, curmsgs = %ld\n",
           attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    printf("Recipient: We are awaiting receipt of messages...\n\n");

    // читаем сообщения
    for (int i = 0; i < NUM_MESSAGES; i++) {
        ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_read < 0) {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }
        buffer[bytes_read] = '\0';
        printf("Received: \"%s\"\n", buffer);
    }

    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}
