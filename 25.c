#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t child[3];

    for (int i = 0; i < 3; i++) {

        child[i] = fork();

        if (child[i] == -1) {
            perror("fork");
            return 1;
        }

        if (child[i] == 0) {

            printf("Child %d created. PID = %d\n",
                   i + 1, getpid());

            sleep((i + 1) * 2);

            printf("Child %d exiting.\n", i + 1);

            exit(0);
        }
    }

    // Parent waits specifically for child 2
    printf("Parent waiting for Child 2...\n");

    waitpid(child[1], NULL, 0);

    printf("Child 2 has finished.\n");

    return 0;
}
