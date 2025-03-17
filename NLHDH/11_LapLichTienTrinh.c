#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <math.h>

#define MAX_PROCESSES 100
#define TIME_QUANTUM 4 // Lượng tử thời gian cho RR

typedef struct {
    long mtype;  // Loại message, dùng để đặt ưu tiên trong IPC
    int pid;     // ID tiến trình
    int burst_time; // Thời gian thực hiện
    int priority;   // Độ ưu tiên
} ProcessMessage;

// Hàng đợi message IPC
int msg_queue_id;

// Gửi tiến trình vào hàng đợi IPC
void send_process(int pid, int burst_time, int priority) {
    ProcessMessage msg;
    msg.mtype = priority;  // Độ ưu tiên
    msg.pid = pid;
    msg.burst_time = burst_time;
    msg.priority = priority;

    msgsnd(msg_queue_id, &msg, sizeof(ProcessMessage) - sizeof(long), 0);
}

// Nhận tiến trình từ hàng đợi IPC
int receive_process(ProcessMessage *msg) {
    return msgrcv(msg_queue_id, msg, sizeof(ProcessMessage) - sizeof(long), 0, IPC_NOWAIT);
}

// So sánh cho SJF (sắp xếp theo thời gian thực hiện tăng dần)
int compare_sjf(const void *a, const void *b) {
    return ((ProcessMessage *)a)->burst_time - ((ProcessMessage *)b)->burst_time;
}

// So sánh cho PRI (sắp xếp theo độ ưu tiên tăng dần)
int compare_pri(const void *a, const void *b) {
    return ((ProcessMessage *)a)->priority - ((ProcessMessage *)b)->priority;
}

// Bộ lập lịch tiến trình
void scheduler(int algorithm, int preemptive) {
    ProcessMessage queue[MAX_PROCESSES];
    int process_count = 0;
    int total_wait_time = 0, context_switches = 0;
    float wait_times[MAX_PROCESSES], throughput = 0.0;

    // Nhận tất cả tiến trình từ hàng đợi
    while (receive_process(&queue[process_count]) > 0) {
        process_count++;
    }

    if (algorithm == 2) {
        // SJF: sắp xếp theo thời gian thực hiện
        qsort(queue, process_count, sizeof(ProcessMessage), compare_sjf);
    } else if (algorithm == 3) {
        // PRI: sắp xếp theo độ ưu tiên
        qsort(queue, process_count, sizeof(ProcessMessage), compare_pri);
    }

    int current_time = 0;
    for (int i = 0; i < process_count; i++) {
        int wait_time = current_time;
        wait_times[i] = wait_time;
        total_wait_time += wait_time;
        current_time += queue[i].burst_time;
        throughput += 1.0 / current_time;
        context_switches++;
    }

    // Tính toán độ lệch chuẩn
    float mean_wait = (float) total_wait_time / process_count;
    float std_dev = 0.0;
    for (int i = 0; i < process_count; i++) {
        std_dev += (wait_times[i] - mean_wait) * (wait_times[i] - mean_wait);
    }
    std_dev = sqrt(std_dev / process_count);

    printf("Thời gian chờ trung bình: %.2f\n", mean_wait);
    printf("Độ lệch chuẩn thời gian chờ: %.2f\n", std_dev);
    printf("Thông lượng hệ thống: %.2f\n", throughput);
    printf("Số lần context switch: %d\n", context_switches);
}

// Vòng lặp chính
int main() {
    key_t key = ftok("scheduler", 65);
    msg_queue_id = msgget(key, 0666 | IPC_CREAT);

    int n, algorithm, preemptive;
    printf("Nhập số tiến trình: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int burst_time, priority;
        printf("Nhập thời gian thực hiện và độ ưu tiên (t p) cho tiến trình %d: ", i + 1);
        scanf("%d %d", &burst_time, &priority);
        send_process(i + 1, burst_time, priority);
    }

    printf("Chọn thuật toán (1.FCFS, 2.SJF, 3.PRI, 4.RR): ");
    scanf("%d", &algorithm);
    printf("Chế độ preemptive? (1: Có, 0: Không): ");
    scanf("%d", &preemptive);

    scheduler(algorithm, preemptive);
    
    msgctl(msg_queue_id, IPC_RMID, NULL); // Xóa hàng đợi IPC sau khi xong
    return 0;
}
