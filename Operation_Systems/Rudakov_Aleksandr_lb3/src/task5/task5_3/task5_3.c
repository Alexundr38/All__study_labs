#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100

char message[BUFFER_SIZE];

int message_ready = 0;


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_writer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_reader = PTHREAD_COND_INITIALIZER;

void *writer_thread(void *arg) {
    char buf[BUFFER_SIZE];
    while (1) {
        printf("Enter a message: ");
        fflush(stdout);
        if (fgets(buf, BUFFER_SIZE, stdin) == NULL)
            break;

        pthread_mutex_lock(&mutex);
        while (message_ready)
            pthread_cond_wait(&cond_writer, &mutex);

        if (strcmp(buf, "\n") == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        strcpy(message, buf);
        message_ready = 1;
        pthread_cond_signal(&cond_reader);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *reader_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (!message_ready)
            pthread_cond_wait(&cond_reader, &mutex);

        if (strcmp(message, "\n") == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        printf("The message has been read: %s", message);
        message_ready = 0;
        pthread_cond_signal(&cond_writer);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t writer, reader;
    if (pthread_create(&writer, NULL, writer_thread, NULL) != 0) {
        perror("Error creating the writer thread");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&reader, NULL, reader_thread, NULL) != 0) {
        perror("Error creating the reader thread");
        exit(EXIT_FAILURE);
    }

    pthread_join(writer, NULL);
    pthread_mutex_lock(&mutex);
    message_ready = 1;
    strcpy(message, "\n");
    pthread_cond_signal(&cond_reader);
    pthread_mutex_unlock(&mutex);
    pthread_join(reader, NULL);

    return 0;
}
