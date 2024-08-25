#include <cstdio>
#include <cstdlib>

// Define the process structure
typedef struct Process {
    int pid;              // Process ID
    int burst_time;       // Burst time (time required for execution)
    int remaining_time;   // Remaining time for the process to complete
    int waiting_time;     // Waiting time
    int turnaround_time;  // Turnaround time
} Process;

// Function to calculate waiting and turnaround times using Round Robin
void calculate_times(Process processes[], int n, int time_quantum) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > time_quantum) {
                    time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].waiting_time = time - processes[i].burst_time;
                    processes[i].turnaround_time = time;
                    processes[i].remaining_time = 0;
                    completed++;
                }
            }
        }
    }
}

// Function to calculate average waiting and turnaround times
void calculate_average_times(Process processes[], int n, int time_quantum) {
    calculate_times(processes, n, time_quantum);

    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time,
               processes[i].waiting_time, processes[i].turnaround_time);
    }

    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time; // Initialize remaining time
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    calculate_average_times(processes, n, time_quantum);

    return 0;
}
