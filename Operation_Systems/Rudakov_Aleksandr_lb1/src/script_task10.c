#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char *filename = "/home/user1/task10.txt";
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error when opening a file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error when writing to standard output");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead == -1) {
        perror("Error reading the file");
    }

    close(fd);
    return 0;
}
