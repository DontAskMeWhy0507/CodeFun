// Hãy viết chương trình C thực hiện các nhiệm vụ sau theo thứ tự thời gian tăng dần:
// 1. Từ tiến trình cha P1, tạo một tiến trình con P2.
// 2. P2 ghi dữ liệu là nhãn thời gian hiện tại theo định dạng yyyy-mm-dd HH:MM:ss (ví dụ 2025-02-18 11:05:23) vào một file text tên là T. P2 kết thúc.
// 3. P1 chờ cho P2 ghi xong, đọc dữ liệu từ T, in ra hai nhãn thời gian: nhãn thời gian đọc của P1, và nhãn thời gian được ghi trong T. P1 kết thúc.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define FILE_NAME "T"

void write_timestamp_to_file(const char *filename) {
    // Open file for writing if it doesn't exist, create it
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    // Get current time 
    time_t now = time(NULL);
    // Convert time to local time
    struct tm *tm_info = localtime(&now);
    // Format time as string
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    // Write time to file
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
    // Fork failed
    if (pid < 0) {
        perror("Fork failed");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        // Tiến trình con P2
        write_timestamp_to_file(FILE_NAME);
        exit(EXIT_SUCCESS);
    } else {
        // Tiến trình cha P1
        wait(NULL); // Chờ tiến trình con hoàn thành
        read_timestamp_from_file(FILE_NAME);
    }
    
    return EXIT_SUCCESS;
}
