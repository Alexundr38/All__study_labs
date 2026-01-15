#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>


#define FIFO_PATH "/tmp/my_fifo"
#define BUFFER_SIZE 1024
#define NUM_MESSAGES 5

void print_fifo_info(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        perror("stat");
        return;
    }
    
    printf("Info FIFO '%s':\n", path);
    printf("File type: ");
    if (S_ISFIFO(st.st_mode))
        printf("FIFO\n");
    else
        printf("Не FIFO\n");
    
    printf("Access rights: %o\n", st.st_mode & 0777);
    printf("Size: %ld byte\n", st.st_size);
    printf("UID: %d, GID: %d\n", st.st_uid, st.st_gid);
    printf("Last changes: %s", ctime(&st.st_mtime));
}

int main(void) {
    print_fifo_info(FIFO_PATH);
    
    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    char buffer[BUFFER_SIZE];
    printf("Recipient: We are awaiting receipt of messages...\n\n");
    for (int i = 0; i < NUM_MESSAGES; i++) {
        ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer[bytes_read] = '\0';
        printf("Received: \"%s\"\n", buffer);
    }
    
    close(fd);

    if (unlink(FIFO_PATH) == -1) {
        perror("unlink");
    } else {
        printf("\nFIFO '%s' deleted.\n", FIFO_PATH);
    }
    
    return 0;
}
