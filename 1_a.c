#include <stdio.h>
#include <unistd.h>

int main() {
    if (symlink("file.txt", "softlink.txt") == -1) {
        perror("symlink");
        return 1;
    }

    printf("Soft link created successfully.\n");
    return 0;
}
