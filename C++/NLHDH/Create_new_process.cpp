#include <stdio.h>
#include <unistd.h>

int main()
{
    int return_val = -1;
    int value = 2025;

    return_val = fork();    // Create a new process

    if (return_val < 0) {
        perror("Cannot create a new process");
        return(1);
    }
    else if (return_val > 0) {    // Parent process
        printf("Parent process: return_val = %d my ID = %d parent process ID = %d\n",
            return_val, getpid(), getppid());
        value = 2024;
        printf("Parent: value = %d\n", value);
    }
    else {    // Child process
        printf("Child process: return_val = %d my ID = %d parent process ID = %d\n",
            return_val, getpid(), getppid());
        printf("Child: value = %d\n", value);
    }
    return(0);
}