#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    int ticket = 100;

    // Create and open file
    fd = open("ticket.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Store ticket number
    write(fd, &ticket, sizeof(ticket));

    printf("Initial ticket number = %d\n", ticket);

    close(fd);

    return 0;
}
