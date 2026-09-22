#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child
        printf("Child process\n");
        printf("Child PID  = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());
    }
    else {
        // Parent
        printf("Parent process\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID  = %d\n", pid);
    }

    return 0;
}
