#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);  // Generate the same unique key
    int shmid = shmget(key, SHM_SIZE, 0666);  // Access shared memory

    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    char *shm_ptr = (char *)shmat(shmid, NULL, 0);  // Attach shared memory
    if (shm_ptr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    printf("Received message: %s\n", shm_ptr);  // Read from shared memory

    shmdt(shm_ptr);  // Detach from shared memory
    shmctl(shmid, IPC_RMID, NULL);  // Remove shared memory

    return 0;
}