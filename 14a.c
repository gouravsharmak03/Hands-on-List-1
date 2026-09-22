#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat st;

    // Check whether file name is given
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get information about the file
    if (lstat(argv[1], &st) == -1)
    {
        perror("lstat");
        return 1;
    }

    printf("File name: %s\n", argv[1]);

    return 0;
}
