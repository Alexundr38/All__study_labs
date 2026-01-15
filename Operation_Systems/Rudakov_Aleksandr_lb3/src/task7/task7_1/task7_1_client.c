#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    while (1){
        memset(buffer, 0, sizeof(buffer));
        printf("Enter a message for the server: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
            perror("send");
            exit(EXIT_FAILURE);
        }
        printf("A message has been sent to the server %s", buffer);

        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received < 0) {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        buffer[bytes_received] = '\0';
        printf("A response was received from the server: %s\n", buffer);
    }
    
    close(client_socket);

    return 0;
}
