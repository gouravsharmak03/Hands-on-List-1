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

    // Open/create file
    fd = open("records.dat", O_RDWR | O_CREAT, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Check if file is empty
    if (lseek(fd, 0, SEEK_END) == 0) {

        struct record records[3] = {
            {1, "Alice"},
            {2, "Bob"},
            {3, "Charlie"}
        };

        write(fd, records, sizeof(records));
    }

    printf("Enter record number (1-3): ");
    scanf("%d", &record_no);

    if (record_no < 1 || record_no > 3) {
        printf("Invalid record number.\n");
        close(fd);
        return 1;
    }

    // Convert 1,2,3 to 0,1,2
    record_no--;

    // Create write lock
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = record_no * sizeof(struct record);
    lock.l_len = sizeof(struct record);
    lock.l_pid = getpid();

    printf("Waiting for write lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Write lock acquired.\n");

    // Go to selected record
    lseek(fd, record_no * sizeof(struct record), SEEK_SET);

    // Read record
    read(fd, &r, sizeof(r));

    printf("Current ID   : %d\n", r.id);
    printf("Current Name : %s\n", r.name);

    // Modify record
    printf("Enter new name: ");
    scanf("%19s", r.name);

    // Go back to record
    lseek(fd, record_no * sizeof(struct record), SEEK_SET);

    // Write modified record
    write(fd, &r, sizeof(r));

    printf("Record updated successfully.\n");

    // Unlock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    printf("Write lock released.\n");

    close(fd);

    return 0;
}
