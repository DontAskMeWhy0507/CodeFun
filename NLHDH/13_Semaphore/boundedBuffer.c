#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#define BUFFER_SIZE 5
#define PRODUCE_COUNT 10

// Semaphore operations
void sem_op(int semid, int sem_num, int op) {
    struct sembuf sb = {sem_num, op, 0};
    semop(semid, &sb, 1);
}

int main() {
    // Shared memory for buffer and indices
    int shmid = shmget(IPC_PRIVATE, sizeof(int) * BUFFER_SIZE + sizeof(int) * 2, IPC_CREAT | 0666);
    int *shared = (int *)shmat(shmid, NULL, 0);
    int *buffer = shared;       // First BUFFER_SIZE elements for buffer
    int *in = &shared[BUFFER_SIZE];   // write index
    int *out = &shared[BUFFER_SIZE + 1]; // read index
    *in = *out = 0;

    // Semaphore set: 0 = empty, 1 = full, 2 = mutex
    int semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, BUFFER_SIZE); // empty = BUFFER_SIZE
    semctl(semid, 1, SETVAL, 0);           // full = 0
    semctl(semid, 2, SETVAL, 1);           // mutex = 1

    pid_t pid = fork();

    if (pid == 0) {
        // Producer
        srand(getpid());
        for (int i = 0; i < PRODUCE_COUNT; i++) {
            int item = rand() % 100;
            sem_op(semid, 0, -1); // wait(empty)
            sem_op(semid, 2, -1); // wait(mutex)

            buffer[*in] = item;
            printf("Producer produced: %d at index %d\n", item, *in);
            *in = (*in + 1) % BUFFER_SIZE;

            sem_op(semid, 2, 1);  // signal(mutex)
            sem_op(semid, 1, 1);  // signal(full)

            sleep(1);
        }
        exit(0);
    } else {
        // Consumer
        for (int i = 0; i < PRODUCE_COUNT; i++) {
            sem_op(semid, 1, -1); // wait(full)
            sem_op(semid, 2, -1); // wait(mutex)

            int item = buffer[*out];
            printf("Consumer consumed: %d at index %d\n", item, *out);
            *out = (*out + 1) % BUFFER_SIZE;

            sem_op(semid, 2, 1);  // signal(mutex)
            sem_op(semid, 0, 1);  // signal(empty)

            sleep(2);
        }
        wait(NULL);

        // Cleanup
        shmdt(shared);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
