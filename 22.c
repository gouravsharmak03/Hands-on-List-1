#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    pid_t pid;

    // Open file before fork
    fd = open("forkfile.txt",
              O_WRONLY | O_CREAT | O_TRUNC,
              0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Create child
    pid = fork();

    if (pid == -1) {
        perror("fork");
        close(fd);
        return 1;
    }

    if (pid == 0) {
        // Child writes
        write(fd, "Child wrote this\n", 17);
    }
    else {
        // Parent writes
        write(fd, "Parent wrote this\n", 18);
    }

    close(fd);

    return 0;
}
