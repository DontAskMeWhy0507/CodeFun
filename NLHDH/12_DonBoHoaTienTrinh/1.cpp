#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 5  // Kích thước vùng đệm

// Cấu trúc dùng để lưu trữ trong vùng nhớ chung
typedef struct {
    int buffer[SIZE];
    int in;
    int out;
    int counter;
} shared_data;

// Hàm giả lập việc "sản xuất" một item (Producer)
int produceItem() {
    // Ở đây ta có thể sinh ra một số ngẫu nhiên, hoặc đơn giản là tăng dần
    static int item = 0;
    return ++item;
}

// Hàm giả lập việc "tiêu thụ" một item (Consumer)
void consumeItem(int item) {
    // Ví dụ: in ra màn hình
    printf("Consumer tiêu thụ item: %d\n", item);
}

// Chương trình chính
int main() {
    key_t key;
    int shmid;
    shared_data *shm;
    
    // Tạo key cho shared memory (có thể dùng ftok hoặc dùng hằng số)
    // Giả sử ta đã có 1 file "keyfile" trong thư mục hiện tại
    key = ftok("keyfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Tạo segment shared memory đủ chứa struct shared_data
    shmid = shmget(key, sizeof(shared_data), 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Gắn (attach) segment này vào không gian địa chỉ của tiến trình
    shm = (shared_data *) shmat(shmid, NULL, 0);
    if ((void *) shm == (void *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Khởi tạo các biến dùng chung
    shm->in = 0;
    shm->out = 0;
    shm->counter = 0;
    for (int i = 0; i < SIZE; i++) {
        shm->buffer[i] = 0; 
    }

    // Tạo tiến trình con
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // --- Tiến trình con: Producer ---
        while (1) {
            // Vòng lặp busy-wait nếu buffer đầy (counter == SIZE)
            while (shm->counter == SIZE) {
                // chờ...
            }

            // Sản xuất item
            int item = produceItem();
            // Ghi item vào buffer
            shm->buffer[shm->in] = item;
            shm->in = (shm->in + 1) % SIZE;

            // Tăng biến đếm phần tử trong buffer
            shm->counter++;

            printf("Producer sản xuất item: %d\n", item);
            fflush(stdout);

            // Nghỉ 1 giây cho dễ quan sát
            sleep(1);
        }
        // Detach và thoát (trên thực tế, ta khó thoát vòng while vô tận,
        // nhưng đây là mô phỏng, nên ta có thể thêm điều kiện dừng nếu muốn).
        shmdt(shm);
        exit(0);
    } else {
        // --- Tiến trình cha: Consumer ---
        // Ta có thể cho chạy một số lần rồi kết thúc.
        // Ở đây, minh hoạ chạy 10 lần tiêu thụ, sau đó dừng.
        for (int i = 0; i < 10; i++) {
            // Vòng lặp busy-wait nếu buffer rỗng (counter == 0)
            while (shm->counter == 0) {
                // chờ...
            }

            // Lấy item từ buffer
            int item = shm->buffer[shm->out];
            shm->out = (shm->out + 1) % SIZE;

            // Giảm biến đếm
            shm->counter--;

            // Tiêu thụ item
            consumeItem(item);

            // Nghỉ 2 giây cho dễ quan sát
            sleep(2);
        }

        // Sau khi tiêu thụ xong, ta có thể dừng Producer (nếu muốn),
        // hoặc đơn giản kill tiến trình con. Ở đây ta minh hoạ dừng.
        kill(pid, SIGTERM);

        // Đợi tiến trình con kết thúc
        wait(NULL);

        // Tháo vùng nhớ dùng chung khỏi tiến trình
        shmdt(shm);

        // Xoá segment shared memory
        shmctl(shmid, IPC_RMID, NULL);

        printf("Consumer đã kết thúc.\n");
    }

    return 0;
}
