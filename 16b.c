#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    struct flock lock;

    // Open file
    fd = open("lock.txt", O_RDONLY | O_CREAT, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Set read lock
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    printf("Trying to acquire read lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Read lock acquired.\n");
    printf("PID = %d\n", getpid());
    printf("Press Enter to release the lock...\n");

    getchar();

    // Remove lock
    lock.l_type = F_UNLCK;

    fcntl(fd, F_SETLK, &lock);

    printf("Read lock released.\n");

    close(fd);

    return 0;
}}
