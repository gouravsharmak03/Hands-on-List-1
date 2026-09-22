#include <stdio.h>
#include <unistd.h>

int main() {

    execl("./hello", "hello", "Gourav", NULL);

    perror("execl");

    return 1;
}
