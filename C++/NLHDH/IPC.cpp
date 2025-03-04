#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>

#define SHM_KEY 1234
#define BUFFER_SIZE 100

int shmid;
char *shared_memory;

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        printf("P1 received modified data from P2: %s\n", shared_memory);
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
        exit(0);
    }
}

int main() {
    shmid = shmget(SHM_KEY, BUFFER_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    pid_t p2_pid;
    printf("Enter P2 PID: ");
    scanf("%d", &p2_pid);

    strcpy(shared_memory, "Hello from P1");
    printf("P1 wrote: %s\n", shared_memory);

    kill(p2_pid, SIGUSR1);
    signal(SIGUSR2, signal_handler);
    pause();
    return 0;
}
