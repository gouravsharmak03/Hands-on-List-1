#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    off_t position;

    // Open/create the file in read-write mode
    fd = open("lseek.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write first 10 bytes
    if (write(fd, "AAAAAAAAAA", 10) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Move file pointer 10 bytes forward
    position = lseek(fd, 10, SEEK_CUR);

    // Check return value of lseek()
    if (position == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Return value of lseek = %ld\n", (long)position);

    // Write another 10 bytes
    if (write(fd, "BBBBBBBBBB", 10) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);

    printf("File created successfully.\n");
    printf("Now use: od -c lseek.txt\n");

    return 0;
}
