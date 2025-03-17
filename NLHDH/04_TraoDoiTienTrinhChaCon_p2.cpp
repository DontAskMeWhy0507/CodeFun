#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define FILE_NAME "T"

void write_timestamp_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(file, "%s", buffer);
    fclose(file);
}

void read_timestamp_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    char buffer[20];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error reading file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
    
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char current_time[20];
    strftime(current_time, sizeof(current_time), "%Y-%m-%d %H:%M:%S", tm_info);
    
    printf("Timestamp read from file: %s\n", buffer);
    printf("Current timestamp: %s\n", current_time);
}

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        // Tiến trình con P2
        while (getppid() != 1) {
            // Chờ tiến trình cha P1 kết thúc
            sleep(1);
        }
        read_timestamp_from_file(FILE_NAME);
        exit(EXIT_SUCCESS);
    } else {
        // Tiến trình cha P1
        write_timestamp_to_file(FILE_NAME);
        exit(EXIT_SUCCESS);
    }
    
    return EXIT_SUCCESS;
}