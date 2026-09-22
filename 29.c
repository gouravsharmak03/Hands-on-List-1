#include <stdio.h>
#include <unistd.h>
#include <sched.h>

int main() {
    int policy;
    struct sched_param param;

    // Get current policy
    policy = sched_getscheduler(0);

    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Current policy: ");

    if (policy == SCHED_OTHER)
        printf("SCHED_OTHER\n");

    else if (policy == SCHED_FIFO)
        printf("SCHED_FIFO\n");

    else if (policy == SCHED_RR)
        printf("SCHED_RR\n");

    else
        printf("Unknown\n");

    // Set priority
    param.sched_priority = 10;

    // Change policy to SCHED_FIFO
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler");
        return 1;
    }

    printf("Policy changed to SCHED_FIFO.\n");

    return 0;
}
