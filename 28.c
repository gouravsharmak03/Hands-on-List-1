#include <stdio.h>
#include <sched.h>

int main() {
    int min, max;

    // SCHED_FIFO
    min = sched_get_priority_min(SCHED_FIFO);
    max = sched_get_priority_max(SCHED_FIFO);

    if (min == -1 || max == -1) {
        perror("sched_get_priority");
        return 1;
    }

    printf("SCHED_FIFO\n");
    printf("Minimum priority = %d\n", min);
    printf("Maximum priority = %d\n", max);

    // SCHED_RR
    min = sched_get_priority_min(SCHED_RR);
    max = sched_get_priority_max(SCHED_RR);

    printf("\nSCHED_RR\n");
    printf("Minimum priority = %d\n", min);
    printf("Maximum priority = %d\n", max);

    return 0;
}
