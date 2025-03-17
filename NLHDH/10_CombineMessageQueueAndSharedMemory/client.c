#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

#define MSG_KEY 1234  // Key cho message queue
#define SHM_KEY 5678  // Key cho shared memory

// Cấu trúc thông điệp cho message queue
struct msgbuf {
    long mtype;        // ID của client
    struct info {
        int offset;    // Địa chỉ bắt đầu trong shared memory
        int size;      // Kích thước dữ liệu
    } info;
};

int main() {
    // Nhập ID của client
    int client_id;
    printf("Nhập ID của client: ");
    scanf("%d", &client_id);
    getchar();  // Xóa ký tự xuống dòng sau scanf

    // Gắn shared memory
    int shmid = shmget(SHM_KEY, 0, 0);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Mở message queue
    int msqid = msgget(MSG_KEY, 0);
    if (msqid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Vòng lặp nhận thông điệp
    while (1) {
        struct msgbuf msg;
        // Chỉ nhận thông điệp có mtype trùng với client_id
        if (msgrcv(msqid, &msg, sizeof(msg.info), client_id, 0) == -1) {
            perror("msgrcv failed");
            continue;
        }

        // Đọc dữ liệu từ shared memory
        int offset = msg.info.offset;
        int size = msg.info.size;
        char data[size + 1];
        memcpy(data, shm + offset, size);
        data[size] = '\0';  // Thêm ký tự kết thúc chuỗi
        printf("Nhận được: %s\n", data);
    }

    // Cleanup (thực tế vòng lặp vô hạn nên không đến đây)
    shmdt(shm);
    return 0;
}