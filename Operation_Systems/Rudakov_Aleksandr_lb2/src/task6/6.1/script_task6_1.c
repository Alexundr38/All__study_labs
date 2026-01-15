//скрипт для опредения доступа потомка к файлу, открытому родителем
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    int fd = open("text_task6_1.txt", O_RDWR | O_CREAT, 0644);
    write(fd, "parent text\n", 13);
    printf("parent write\n");

    pid_t pid = fork();
    if (pid == 0) {
        write(fd, "child text\n", 12);
        lseek(fd, 0, SEEK_SET);
        char buf[20];
        read(fd, buf, 20);
        printf("Child read: %s\n", buf);
        printf("child exec ls\n");
        execl("/bin/ls", "ls", NULL);
    } else {
        wait(NULL);
        lseek(fd, 0, SEEK_SET);
        char buf[20];
        read(fd, buf, 20);
        printf("Parent read: %s\n", buf);
    }
    return 0;
}
