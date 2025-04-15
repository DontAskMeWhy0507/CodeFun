#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 10
#define M 4  // Tổng số tiến trình, 1 là master, 3 tiến trình con

int main() {
    float a[N] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    int num_workers = M - 1;  // Số tiến trình con

    // Vùng nhớ chung để lưu kết quả từ các tiến trình con (float * num_workers)
    int shmid = shmget(IPC_PRIVATE, sizeof(float) * num_workers, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Chia đều N phần tử cho các tiến trình con
    int chunk_size = N / num_workers;

    for (int i = 0; i < num_workers; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            float *shm_ptr = (float *)shmat(shmid, NULL, 0);
            if (shm_ptr == (void *)-1) {
                perror("shmat");
                exit(1);
            }

            int start = i * chunk_size;
            // Đảm bảo tiến trình cuối cùng lấy hết phần tử còn lại
            int end = (i == num_workers - 1) ? N : start + chunk_size;  

            float partial_sum = 0.0;
            for (int j = start; j < end; j++) {
                partial_sum += a[j];
            }

            // Ghi kết quả vào vị trí tương ứng trong shared memory (number of shm_ptr = num_workers)
            shm_ptr[i] = partial_sum;

            shmdt(shm_ptr);
            exit(0);
        }
    }

    // Tiến trình chính P1
    float total = 0.0;
    for (int i = 0; i < num_workers; i++) {
        wait(NULL);  // Đợi tiến trình con kết thúc
    }

    float *shm_ptr = (float *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    for (int i = 0; i < num_workers; i++) {
        printf("Partial sum from P%d: %.2f\n", i + 2, shm_ptr[i]);
        total += shm_ptr[i];
    }

    printf("Total sum (computed by master P1): %.2f\n", total);

    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);  // Cleanup

    return 0;
}
