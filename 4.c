#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    fd = open("test.txt", O_RDWR | O_CREAT | O_EXCL, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("File created and opened successfully.\n");
    printf("File descriptor = %d\n", fd);

    close(fd);

    return 0;
}
