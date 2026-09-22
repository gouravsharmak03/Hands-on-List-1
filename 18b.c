#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct record {
    int id;
    char name[20];
};

int main() {
    int fd;
    int record_no;
    struct record r;
    struct flock lock;

    // Open file
    fd = open("records.dat", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("Enter record number (1-3): ");
    scanf("%d", &record_no);

    if (record_no < 1 || record_no > 3) {
        printf("Invalid record number.\n");
        close(fd);
        return 1;
    }

    record_no--;

    // Create read lock
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = record_no * sizeof(struct record);
    lock.l_len = sizeof(struct record);
    lock.l_pid = getpid();

    printf("Waiting for read lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Read lock acquired.\n");

    // Move to selected record
    lseek(fd, record_no * sizeof(struct record), SEEK_SET);

    // Read record
    read(fd, &r, sizeof(r));

    printf("\nRecord Information\n");
    printf("ID   : %d\n", r.id);
    printf("Name : %s\n", r.name);

    // Unlock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    printf("Read lock released.\n");

    close(fd);

    return 0;
}
