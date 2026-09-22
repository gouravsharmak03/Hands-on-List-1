#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, newfd;

    fd = open("dup.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    newfd = dup(fd);

    if (newfd == -1) {
        perror("dup");
        close(fd);
        return 1;
    }

    printf("Original FD = %d\n", fd);
    printf("Duplicate FD = %d\n", newfd);

    write(fd, "Hello from FD1\n", 15);
    write(newfd, "Hello from FD2\n", 15);

    close(fd);
    close(newfd);

    return 0;
}
