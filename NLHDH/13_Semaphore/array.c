#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define N 10
int main() {
    float a[N] = {1.5, 2.3, 3.0, 4.1, 5.2, 6.3, 7.4, 8.5, 9.6, 10.7};
    int k = N/2 - 1;

    int shmid = shmget(IPC_PRIVATE, sizeof(int) * N, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        float x2 = 0.0;
        for (int i = k + 1; i < N; i++) {
            x2 += a[i];
        }
        // Attach shared memory segment to process
        int *shm_ptr = shmat(shmid, NULL, 0);
        if (shm_ptr == (int *) -1) {
            perror("shmat");
            exit(1);
        }
        // Store the result in shared memory
        shm_ptr[k] = x2;
        if (shmdt(shm_ptr) < 0) {
            perror("shmdt");
            exit(1);
        }
        exit(0);
    } else {
        float x1 = 0.0;
        for (int i = 0; i < N; i++) {
            x1 += a[i];
        }
        wait(NULL); // Wait for P2 to finish
        // Attach shared memory segment to process
        int *shm_ptr = shmat(shmid, NULL, 0);
        if (shm_ptr == (int *) -1) {
            perror("shmat");
            exit(1);
        }
        // Retrieve the result from shared memory
        float total = x1 + shm_ptr[k];
        printf("Total: %f\n", total);
        // cleanup
        if (shmdt(shm_ptr) < 0) {
            perror("shmdt");
            exit(1);
        }
        if (shmctl(shmid, IPC_RMID, NULL) < 0) {
            perror("shmctl");
            exit(1);
        }
    }
   
}