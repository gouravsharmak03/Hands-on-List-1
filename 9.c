#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct stat s;
    char filename[100];

    printf("Enter filename: ");
    scanf("%99s", filename);

    if (stat(filename, &s) == -1) {
        perror("stat");
        return 1;
    }

    printf("\nFile Information\n");
    printf("-------------------------\n");

    printf("Inode number       : %ld\n", (long)s.st_ino);
    printf("Number of links    : %ld\n", (long)s.st_nlink);
    printf("UID                : %d\n", s.st_uid);
    printf("GID                : %d\n", s.st_gid);
    printf("Size               : %ld bytes\n", (long)s.st_size);
    printf("Block size         : %ld bytes\n", (long)s.st_blksize);
    printf("Number of blocks   : %ld\n", (long)s.st_blocks);

    printf("Last access time   : %s", ctime(&s.st_atime));
    printf("Last modification  : %s", ctime(&s.st_mtime));
    printf("Last status change : %s", ctime(&s.st_ctime));

    return 0;
}
