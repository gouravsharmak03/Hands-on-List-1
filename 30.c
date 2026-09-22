#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main() {
    pid_t pid;
    time_t now;
    struct tm *t;

    // Create child
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    // Parent exits
    if (pid > 0) {
        exit(0);
    }

    // Create new session
    if (setsid() < 0) {
        exit(1);
    }

    // Change working directory
    chdir("/");

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Daemon loop
    while (1) {

        time(&now);
        t = localtime(&now);

        /*
           Change this time according
           to your requirement.
        */
        if (t->tm_hour == 23 && t->tm_min == 00) {

            system("/home/user/Hands On List 1/myscript.sh");

            // Don't run it repeatedly during the same minute
            sleep(60);
        }

        sleep(1);
    }

    return 0;
}
