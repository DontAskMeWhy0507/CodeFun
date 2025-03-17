#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int writetext(char *file, char *text)
{
    FILE    *fp;

    fp = fopen(file, "w");
    if (fp == NULL) {
        perror("Cannot open file");
        return(-1);
    }
    fprintf(fp, "%s\n", text);
    fclose(fp);
    return(0);
}

int readtext(char *file, char *text)
{
    FILE    *fp;

    fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Cannot open file");
        return(-1);
    }
    fgets(text, 80, fp);
    fclose(fp);
    return(0);
}

int main()
{
    int return_val = -1, parent = -1;
    char *filename="timestamp.txt";

    parent = getpid();  // Get parent's PID
    return_val = fork();    // Create a new process

    if (return_val < 0) {
        perror("Cannot create a new process");
        return(1);
    }
    else if (return_val > 0) {  // Parent process
        writetext(filename, "Parent write");
    }
    else {  // Child process
        int tmp;
        char buf[80];

        do {    // Polling
            tmp = getppid();    // Get parent's PID
            printf("parent: %d tmp: %d\n", parent, tmp);
            sleep(1);
        } while (parent==tmp);  // When parent is terminated, parent's PID is changed to 1 
        printf("Parent exit --> child exit\n");
        readtext(filename, buf);
        printf("Read: %s\n", buf);
    }
    return(0);
}