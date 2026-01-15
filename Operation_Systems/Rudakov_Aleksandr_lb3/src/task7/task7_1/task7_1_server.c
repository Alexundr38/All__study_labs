#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 10


void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    char buffer[1024];

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received < 0) {
            perror("recv");
            break;
        } else if (bytes_received == 0) {
            printf("The client has disconnected\n");
            break;
        }

        printf("Received from the client: %s\n", buffer);

        if (send(client_socket, buffer, bytes_received, 0) < 0) {
            perror("send");
            break;
        }
    }

    close(client_socket);
    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t threads[MAX_CLIENTS];
    int thread_count = 0;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("The server is running. Waiting for connections...\n");

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }
        printf("A new client has been connected\n");

        if (pthread_create(&threads[thread_count], NULL, handle_client, &client_socket) != 0) {
            perror("pthread_create");
            continue;
        }
        thread_count++;

        if (thread_count >= MAX_CLIENTS) {
            printf("The maximum number of clients has been reached. Waiting for new connections...\n");
            break;
        }
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    close(server_socket);
    return 0;
}
