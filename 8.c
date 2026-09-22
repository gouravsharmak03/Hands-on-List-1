#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char ch;
    char line[1024];
    int i = 0;
    int n;

    fd = open("file1", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    while ((n = read(fd, &ch, 1)) > 0) {

        line[i++] = ch;

        if (ch == '\n') {
            write(STDOUT_FILENO, line, i);
            i = 0;
        }
    }

    if (i > 0) {
        write(STDOUT_FILENO, line, i);
    }

    close(fd);

    return 0;
}
