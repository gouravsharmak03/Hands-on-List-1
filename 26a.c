#include <stdio.h>
#include <unistd.h>

int main() {

    printf("Executing hello program...\n");

    execl("./hello", "hello", NULL);

    // This runs only if execl() fails
    perror("execl");

    return 1;
}
