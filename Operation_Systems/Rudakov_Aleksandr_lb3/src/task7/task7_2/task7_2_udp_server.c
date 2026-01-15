#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define MAX_CLIENTS 2000


int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("The server is running. Waiting for messages from clients...\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recvfrom(server_socket, buffer, sizeof(buffer), 0,
                                      (struct sockaddr *)&client_addr, &client_len);
        if (bytes_received < 0) {
            perror("recvfrom");
            continue;
        }

        printf("Received from the client %s:%d: %s\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port), buffer);

        if (sendto(server_socket, buffer, bytes_received, 0,
                   (struct sockaddr *)&client_addr, client_len) < 0) {
            perror("sendto");
            continue;
        }
    }

    close(server_socket);
    return 0;
}
