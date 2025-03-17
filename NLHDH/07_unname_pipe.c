#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

int main() {
    int fd[2];  // fd[0] for reading, fd[1] for writing
    pid_t pid;

    if (pipe(fd) == -1) {  // Create pipe
        perror("pipe failed");
        exit(1);
    }

    pid = fork();  // Create child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        close(fd[1]);  // Close unused write end

        char buffer[BUFFER_SIZE];
        read(fd[0], buffer, BUFFER_SIZE);  // Read from pipe
        printf("Child received: %s\n", buffer);

        close(fd[0]);  // Close read end
    } else {  // Parent process
        close(fd[0]);  // Close unused read end
        sleep(5);

        char message[] = "Hello from Parent!";
        write(fd[1], message, strlen(message) + 1);  // Write to pipe

        close(fd[1]);  // Close write end
        wait(NULL);  // Wait for child to finish
    }

    return 0;
}