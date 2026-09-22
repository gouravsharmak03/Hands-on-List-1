#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    int ticket;
    struct flock lock;

    // Open ticket file
    fd = open("ticket.txt", O_RDWR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Create write lock
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(ticket);
    lock.l_pid = getpid();

    printf("Waiting for write lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    // Go to beginning
    lseek(fd, 0, SEEK_SET);

    // Read ticket number
    read(fd, &ticket, sizeof(ticket));

    printf("Old ticket number = %d\n", ticket);

    // Increment ticket
    ticket++;

    // Go back to beginning
    lseek(fd, 0, SEEK_SET);

    // Store new ticket number
    write(fd, &ticket, sizeof(ticket));

    printf("New ticket number = %d\n", ticket);

    // Unlock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    close(fd);

    return 0;
}
