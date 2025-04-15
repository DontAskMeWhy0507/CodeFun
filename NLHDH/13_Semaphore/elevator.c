#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SEM_KEY 1234      // Shared semaphore key
#define MAX_PEOPLE 6      // Max people in elevator
#define TOTAL_PEOPLE 8    // Total number of people to simulate

// General semaphore operation: op = -1 (P), op = 1 (V)
void semaphore_operation(int semid, int op) {
    struct sembuf sb;   // Semaphore buffer
    sb.sem_num = 0;   // Only using the first semaphore
    sb.sem_op = op;   // -1 = wait, +1 = signal
    sb.sem_flg = 0;
    semop(semid, &sb, 1);   // Perform the operation. 
    //if op = -1, wait until the semaphore is available
    //if op = 1, increment the semaphore value
}

int main() {
    // Create semaphore set with SEM_KEY, 
    //IPC_CREAT | 0666 for read/write permissions
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);   
    if (semid == -1) {
        perror("semget failed");
        exit(1);
    }

    // Initialize semaphore to elevator capacity
    // secmt1 is used to set the initial value of the semaphore.
    if (semctl(semid, 0, SETVAL, MAX_PEOPLE) == -1) {
        perror("semctl SETVAL failed");
        exit(1);
    }

    // Fork 8 child processes (each represents a person)
    for (int i = 0; i < TOTAL_PEOPLE; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            printf("Person %d: Waiting to enter elevator...\n", i + 1);
            semaphore_operation(semid, -1);  // Wait (P)
            printf("Person %d: Entered elevator!\n", i + 1);
            sleep(3);  // Simulate elevator ride
            printf("Person %d: Exiting elevator.\n", i + 1);
            semaphore_operation(semid, 1);   // Signal (V)
            exit(0);
        }
    }

    // Parent waits for all children
    for (int i = 0; i < TOTAL_PEOPLE; i++) {
        wait(NULL);
    }

    // Cleanup semaphore
    semctl(semid, 0, IPC_RMID);
    printf("Simulation complete. Semaphore cleaned up.\n");

    return 0;
}
