#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

#define SHM_SIZE 1024  // Kích thước shared memory
#define MSG_KEY 1234   // Key cho message queue
#define SHM_KEY 5678   // Key cho shared memory

// Cấu trúc thông điệp cho message queue
struct msgbuf {
    long mtype;        // ID của client
    struct info {
        int offset;    // Địa chỉ bắt đầu trong shared memory
        int size;      // Kích thước dữ liệu
    } info;
};

int main() {
    // Tạo shared memory
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Tạo message queue
    int msqid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget failed");
        exit(1);
    }

    int offset = 0;  // Vị trí hiện tại trong shared memory
    while (1) {
        // Đọc dữ liệu từ bàn phím
        printf("Nhập dữ liệu để gửi: ");
        char data[100];
        fgets(data, sizeof(data), stdin);
        int len = strlen(data);
        if (len > 0 && data[len - 1] == '\n') {
            data[len - 1] = '\0';  // Xóa ký tự xuống dòng
            len--;
        }

        // Kiểm tra xem shared memory còn đủ chỗ không
        if (offset + len > SHM_SIZE) {
            printf("Shared memory đầy, không thể ghi thêm dữ liệu\n");
            continue;
        }

        // Ghi dữ liệu vào shared memory
        memcpy(shm + offset, data, len);

        // Đọc ID của client
        printf("Nhập ID của client để gửi đến: ");
        int client_id;
        scanf("%d", &client_id);
        getchar();  // Xóa ký tự xuống dòng sau scanf

        // Tạo và gửi thông điệp qua message queue
        struct msgbuf msg;
        msg.mtype = client_id;      // ID của client nhận
        msg.info.offset = offset;   // Địa chỉ bắt đầu
        msg.info.size = len;        // Kích thước dữ liệu
        if (msgsnd(msqid, &msg, sizeof(msg.info), 0) == -1) {
            perror("msgsnd failed");
            continue;
        }

        offset += len;  // Cập nhật offset cho lần ghi tiếp theo
    }

    // Cleanup (thực tế vòng lặp vô hạn nên không đến đây)
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}