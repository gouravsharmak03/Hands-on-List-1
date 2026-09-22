#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    int priority;

    priority = getpriority(PRIO_PROCESS, 0);

    printf("PID = %d\n", getpid());
    printf("Current nice value = %d\n", priority);

    printf("Program is running...\n");

    while (1) {
        sleep(1);
    }

    return 0;
}
