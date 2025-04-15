#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex;
sem_t can_write;
sem_t can_read;

void* producer(void* arg) {
    int item = 0;
    while (1) {
        item++; // Tạo dữ liệu mới
        sem_wait(&can_write);     // Chờ nếu buffer đầy
        sem_wait(&mutex);         // Truy cập độc quyền

        buffer[in] = item;
        printf("Ghi: %d vào ô %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);         // Nhả quyền truy cập
        sem_post(&can_read);      // Cho phép đọc
        sleep(1);                 // Mô phỏng thời gian ghi
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&can_read);      // Chờ nếu buffer rỗng
        sem_wait(&mutex);         // Truy cập độc quyền

        item = buffer[out];
        printf("Đọc: %d từ ô %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);         // Nhả quyền truy cập
        sem_post(&can_write);     // Cho phép ghi tiếp
        sleep(2);                 // Mô phỏng thời gian đọc
    }
}

int main() {
    pthread_t prod, cons;

    // Khởi tạo semaphore
    sem_init(&mutex, 0, 1);
    sem_init(&can_write, 0, BUFFER_SIZE); // Ban đầu buffer trống
    sem_init(&can_read, 0, 0);            // Ban đầu chưa có gì để đọc

    // Tạo thread
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Chờ các thread (trong thực tế sẽ chạy vô hạn)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
