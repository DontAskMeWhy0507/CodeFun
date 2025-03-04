#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int return_val;

    return_val = fork();    // Create a new process

    if (return_val < 0) {
        perror("Cannot create a new process");
        return(1);
    }
    else if (return_val > 0) {    // Parent process
        printf("Parent process: return_val = %d my ID = %d parent process ID = %d\n",
            return_val, getpid(), getppid());
        wait(NULL);
        printf("Child process %d exit\n", return_val);
    }
    else {    // Child process
        printf("Child process: return_val = %d my ID = %d parent process ID = %d\n",
            return_val, getpid(), getppid());
           sleep(5);   // them xoa dong nay de kiem tra tien trinh cha cho tien trinh con
    }
    return(0);
}