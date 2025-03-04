#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define FILE_NAME "T"

void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {  // Tiến trình con P2
        FILE *file = fopen(FILE_NAME, "w");
        if (file == NULL) {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }
        
        char timestamp[20];
        get_timestamp(timestamp, sizeof(timestamp));
        fprintf(file, "%s", timestamp);
        fclose(file);
        exit(EXIT_SUCCESS);
    } else {  // Tiến trình cha P1
        wait(NULL); // Chờ P2 kết thúc
        
        FILE *file = fopen(FILE_NAME, "r");
        if (file == NULL) {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }
        
        char recorded_timestamp[20];
        fscanf(file, "%19s", recorded_timestamp);
        fclose(file);
        
        char read_timestamp[20];
        get_timestamp(read_timestamp, sizeof(read_timestamp));
        
        printf("Timestamp ghi trong file: %s\n", recorded_timestamp);
        printf("Timestamp đọc từ file: %s\n", read_timestamp);
    }
    
    return 0;
}
