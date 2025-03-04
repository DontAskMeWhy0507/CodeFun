#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    // Create a named pipe (FIFO)
    mkfifo(FIFO_PATH, 0666);

    char message[] = "Hello from Writer!";
    int fd = open(FIFO_PATH, O_WRONLY);    // Open FIFO for writing
    write(fd, message, strlen(message) + 1);    // Write message
    close(fd);

    printf("Message sent: %s\n", message);
    return 0;
}