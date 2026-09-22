#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    fd_set readfds;
    struct timeval timeout;
    char buffer[100];

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input for 10 seconds...\n");

    int result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select");
        return 1;
    }
    else if (result == 0) {
        printf("No data available within 10 seconds.\n");
    }
    else {
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            int n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

            if (n > 0) {
                buffer[n] = '\0';
                printf("Data received: %s", buffer);
            }
        }
    }

    return 0;
}
