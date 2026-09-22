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

        printf("Child process\n");
        printf("Child PID  = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());

        sleep(10);

        printf("\nParent has exited.\n");
        printf("Child PID = %d\n", getpid());
        printf("New Parent PID = %d\n", getppid());
    }
    else {

        printf("Parent process\n");
        printf("Parent PID = %d\n", getpid());

        printf("Parent exiting...\n");

        exit(0);
    }

    return 0;
}
