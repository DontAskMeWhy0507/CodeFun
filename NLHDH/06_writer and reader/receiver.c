#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/myfifo"
#define BUFFER_SIZE 100

int main() {
    char buffer[BUFFER_SIZE];

    int fd = open(FIFO_PATH, O_RDONLY);  // Open FIFO for reading
    read(fd, buffer, BUFFER_SIZE);  // Read message
    close(fd);

    printf("Received: %s\n", buffer);

    unlink(FIFO_PATH);  // Remove FIFO after reading
    return 0;
}