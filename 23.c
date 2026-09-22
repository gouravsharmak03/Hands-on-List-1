#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child exits immediately
        printf("Child process exiting...\n");
        exit(0);
    }
    else {
        // Parent does not call wait()
        printf("Parent PID = %d\n", getpid());
        printf("Child PID  = %d\n", pid);

        printf("Parent sleeping for 30 seconds...\n");
        sleep(30);
    }

    return 0;
}
