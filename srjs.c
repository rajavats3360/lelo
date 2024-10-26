//shortest remaning job first-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <limits.h>

void calculateTimes(int n, int burst_time[], int arrival_time[], int waiting_time[], int turnaround_time[]) 
{
    int remaining_time[n];
    int completion_time[n];
    int current_time = 0;
    int completed = 0;
    int shortest = -1;
    int min_remaining_time = INT_MAX;
    for (int i = 0; i < n; i++) 
    {
        remaining_time[i] = burst_time[i];
    }
    int gantt_chart[1000];
    int gantt_index = 0;
    while (completed < n) 
    {
        for (int i = 0; i < n; i++) 
        {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0 && remaining_time[i] < min_remaining_time) 
            {
                min_remaining_time = remaining_time[i];
                shortest = i;
            }
        }
        if (shortest == -1) 
        {
            current_time++;
            continue;
        }
        gantt_chart[gantt_index++] = shortest;
        remaining_time[shortest]--;
        current_time++;
        if (remaining_time[shortest] == 0) 
        {
            completion_time[shortest] = current_time;
            turnaround_time[shortest] = completion_time[shortest] - arrival_time[shortest];
            waiting_time[shortest] = turnaround_time[shortest] - burst_time[shortest];
            completed++;
            min_remaining_time = INT_MAX;
        }   
        shortest = -1;
    }
    printf("Gantt Chart: ");
    for (int i = 0; i < gantt_index; i++) 
    {
        printf("P%d | ", gantt_chart[i]);
    }
    printf("\n\n");

    for(int i=0;i<n;i++)
    {
        printf("P%d %d %d %d %d\n",gantt_chart[i],arrival_time[i],burst_time[i],waiting_time[i],turnaround_time[i]);
    }
    printf("\n\n");
    printf("through put->%f\n",(1.0*n)/current_time);
    double total_bt=0;
    for(int i=0;i<n;i++)
    {
        total_bt+=burst_time[i];
    }
    printf("efficiency->%f\n\n",(total_bt/current_time)*100);
}

void printAverageTimes(int n, int waiting_time[], int turnaround_time[]) 
{
    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) 
    {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    printf("Average waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
}

int main() 
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int burst_time[n], arrival_time[n], waiting_time[n], turnaround_time[n];
    printf("Enter burst time for each process: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &burst_time[i]);
    }
    printf("Enter arrival time for each process: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &arrival_time[i]);
    }
    calculateTimes(n, burst_time, arrival_time, waiting_time, turnaround_time);
    printAverageTimes(n, waiting_time, turnaround_time);
    return 0;
}

//sjfs-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdbool.h>

#define MAX 100

void calculateTimes(int n, int burst_time[], int arrival_time[], int waiting_time[], int turnaround_time[], int completion_time[]) 
{
    bool completed[n];
    for (int i = 0; i < n; i++) 
    {
        completed[i] = false;
    }
    int current_time = 0;
    int completed_count = 0;
    int gantt_chart[MAX];
    int gantt_index = 0;
    while (completed_count < n) 
    {
        int min_index = -1;
        int min_burst_time = MAX;
        for (int i = 0; i < n; i++) 
        {
            if (arrival_time[i] <= current_time && !completed[i] && burst_time[i] < min_burst_time) 
            {
                min_burst_time = burst_time[i];
                min_index = i;
            }
        }
        if (min_index == -1) 
        {
            current_time++;
            continue;
        }
        gantt_chart[gantt_index++] = min_index;
        current_time += burst_time[min_index];
        completion_time[min_index] = current_time;
        turnaround_time[min_index] = completion_time[min_index] - arrival_time[min_index];
        waiting_time[min_index] = turnaround_time[min_index] - burst_time[min_index];
        completed[min_index] = true;
        completed_count++;
    }
    printf("Gantt Chart: ");
    for (int i = 0; i < gantt_index; i++) 
    {
        printf("P%d | ", gantt_chart[i]);
    }
    printf("\n\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d %d %d %d %d\n",gantt_chart[i],arrival_time[i],burst_time[i],waiting_time[i],turnaround_time[i]);
    }
    printf("\n\n");
    printf("through put->%f\n",(1.0*n)/current_time);
    double total_bt=0;
    for(int i=0;i<n;i++)
    {
        total_bt+=burst_time[i];
    }
    printf("efficiency->%f\n\n",(total_bt/current_time)*100);
}

void printAverageTimes(int n, int waiting_time[], int turnaround_time[]) 
{
    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) 
    {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    printf("Average waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
}

int main() 
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int burst_time[n], arrival_time[n], waiting_time[n], turnaround_time[n], completion_time[n];
    printf("Enter burst time for each process: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &burst_time[i]);
    }
    printf("Enter arrival time for each process: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &arrival_time[i]);
    }
    calculateTimes(n, burst_time, arrival_time, waiting_time, turnaround_time, completion_time);
    printAverageTimes(n, waiting_time, turnaround_time);
    return 0;
}

//priority --------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <limits.h>

void preemptive_priority_scheduling(int n, int burst_time[], int arrival_time[], int priority[]) {
    int waiting_time[n], turnaround_time[n], completion_time[n], remaining_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;
    int current_time = 0, completed = 0;

    // Initialize remaining time and other arrays
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
    }
    int gantt_chart[100],gantt_index=0;

    printf("Gantt Chart: ");

    while (completed != n) {
        int highest_priority = -1;
        int min_priority = INT_MAX;

        // Find the highest priority process that is ready
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0) {
                if (priority[i] < min_priority) {
                    min_priority = priority[i];
                    highest_priority = i;
                }
            }
        }

        if (highest_priority == -1) {
            current_time++;  // No process is ready, increment time
        } else {
            // Process execution for one time unit
            gantt_chart[gantt_index++] = highest_priority;
            remaining_time[highest_priority]--;

            // If the process is completed
            if (remaining_time[highest_priority] == 0) {
                completed++;
                completion_time[highest_priority] = current_time + 1;  // +1 because we're considering the current time
                turnaround_time[highest_priority] = completion_time[highest_priority] - arrival_time[highest_priority];
                waiting_time[highest_priority] = turnaround_time[highest_priority] - burst_time[highest_priority];
                total_waiting_time += waiting_time[highest_priority];
                total_turnaround_time += turnaround_time[highest_priority];
            }
            current_time++;  // Move time forward
        }
        
    }
    for (int i = 0; i < gantt_index; i++) 
    {
        printf("P%d | ", gantt_chart[i]);
    }
    printf("\n\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d %d %d %d %d\n",gantt_chart[i],arrival_time[i],burst_time[i],waiting_time[i],turnaround_time[i]);
    }
    printf("\n\n");
    printf("through put->%f\n",(1.0*n)/current_time);
    double total_bt=0;
    for(int i=0;i<n;i++)
    {
        total_bt+=burst_time[i];
    }
    printf("efficiency->%f\n\n",(total_bt/current_time)*100);

    printf("\nAverage waiting time: %.2f\n", (float)total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    int burst_time[n], arrival_time[n], priority[n];

    printf("Enter burst times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burst_time[i]);
    }

    printf("Enter arrival times: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arrival_time[i]);
    }

    printf("Enter priorities (lower number means higher priority): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &priority[i]);
    }

    printf("\nPreemptive Priority Scheduling:\n");
    preemptive_priority_scheduling(n, burst_time, arrival_time, priority);

    return 0;
}
//fcfs-------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
struct process
{
    int at, bt, ct, tat, wt;
};
typedef struct process process;
int main()
{
    int n;
    printf("Enter the number of processes\n");
    scanf("%d", &n);
    process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival and burst time for process %d\n", (i + 1));
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
    int vis[100] = {0}, gantt[100];
    int completed = 0, idleTime = 0, idx = 0, currTime = 0, tot_tat = 0, tot_wt = 0;
    while (completed < n)
    {
        int curr = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currTime && !vis[i])
            {
                if (curr == -1 || p[i].at < p[curr].at)
                {
                    curr = i;
                }
            }
        }
        if (curr == -1)
        {
            currTime++;
        }
        else
        {
            currTime += p[curr].bt;
            p[curr].ct = currTime;
            p[curr].tat = p[curr].ct - p[curr].at;
            p[curr].wt = p[curr].tat - p[curr].bt;
            tot_tat += p[curr].tat;
            tot_wt += p[curr].wt;
            gantt[idx++] = curr;
            completed++;
            vis[curr] = 1;
        }
    }

    printf("Printing the gantt chart\n");
    for (int i = 0; i < idx; i++)
    {
        printf("P%d | ", gantt[i]);
    }
    printf("\n\n");
    for (int i = 0; i < idx; i++)
    {
        printf("P%d %d %d %d %d\n", gantt[i],p[i].at,p[i].bt,p[i].wt,p[i].tat);
    }
    printf("\n\n");
    float avg_tat = (tot_tat / (1.0 * n)), avg_wt = (tot_wt / (1.0 * n));
    float through_put = (1.0*n) / currTime;
    float efficiency = ((currTime - idleTime) / (currTime * 1.0))*100;
    printf("avg turn around time ->%f\navg waiting time-> %f\ncpu effiency-> %f\nthrough put->%f\n", avg_tat, avg_wt, efficiency,through_put);
}
//fork()-------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h> 
#include <unistd.h> 
int main() {
    pid_t pid; pid = fork(); 
    if(pid<0)
    {
        printf("Fork failed!\n");
        return 1; 
    }
    elseif(pid==0)
    {
        printf("This is the child process\n");
    }
    else 
    {
        printf("This is the parent process\n");     
    }
    return 0; 
}
//wait()-------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() 
{
    pid_t pid1;
    pid1 = fork();
    if (pid1 < 0) 
    {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid1 == 0)    
    {
        printf("Child 1 (Listing files): My PID is %d\n", getpid());
        exit(0);
    }
    else {
        wait(NULL);
        printf("Parent process is done waiting for the first child.\n");
        printf("Parent is terminating.\n");
        exit(0);
    }
    return 0;
}
//round robin-------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
struct Process
{
    int at, bt, ct, pid, tat, bt_rem,wt;
};
typedef struct Process process;

int compare(const void *a, const void *b)
{
    process *p1 = (process *)a;
    process *p2 = (process *)b;
    return (p1->at - p2->at);
}

int main()
{
    int n;
    printf("Enter the number of processes\n");
    scanf("%d", &n);
    process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter the arrival and burst time\n");
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].bt_rem = p[i].bt;
        p[i].pid = i;
    }
    qsort(p, n, sizeof(process), compare);
    int tq = 2, curr = p[0].at, front = 0, rear = 0, idleTime = p[0].at, idx = 0, cnt = 0;
    double tot_tat =0,tot_wt=0;
    int q[100], gantt[100];
    int vis[100] = {0};
    q[0] = 0;
    vis[0] = 1;
    while (cnt < n)
    {
        int temp = q[front];
        front++;
        gantt[idx] = p[temp].pid;
        idx++;
        if (p[temp].bt_rem > tq)
        {
            curr += tq;
            p[temp].bt_rem -= tq;
        }
        else
        {
            curr += p[temp].bt_rem;
            p[temp].ct = curr;
            p[temp].tat = p[temp].ct - p[temp].at;
            p[temp].wt = p[temp].tat-p[temp].bt;
            tot_tat += p[temp].tat;
            tot_wt += p[temp].wt;
            p[temp].bt_rem = 0;
            cnt++;
        }
        for (int i = 0; i < n; i++)
        {
            if ((p[i].at <= curr) && (vis[i] == 0) && (i != temp) && (p[i].bt_rem > 0))
            {
                ++rear;
                q[rear] = i;
                vis[i] = 1;
            }
        }
        if (p[temp].bt_rem > 0)
        {
            ++rear;
            q[rear] = temp;
        }
        if (front > rear)
        {
            curr++;
        }
    }
    printf("Printing the Gantt chart\n");
    for (int i = 0; i < idx; i++)
    {
        printf("P%d | ", gantt[i]);
    }
    printf("Printing the details\n");
    printf("\n\n");
    for(int i=0;i<n;i++)
    {
        printf("P%d %d %d %d %d\n",gantt[i],p[i].at,p[i].bt,p[i].wt,p[i].tat);
    }
    printf("\n\n");
    printf("through put->%f\n",(1.0*n)/curr);
    double total_bt=0;
    for(int i=0;i<n;i++)
    {
        total_bt+=p[i].bt;
    }
    printf("efficiency->%f\n\n",(total_bt/curr)*100);
    printf("avg turn around time ->%f\navg waiting time-> %f\n", tot_tat/(1.0*n), tot_wt/(1.0*n));
}
//sum with fork()-------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void compute_even_sum(int limit) {
    int even_sum = 0;
    for (int i = 0; i <= limit; i += 2) {
        even_sum += i;
    }
    printf("Sum of even numbers: %d\n", even_sum);
}

void compute_odd_sum(int limit) {
    int odd_sum = 0;
    for (int i = 1; i <= limit; i += 2) {
        odd_sum += i;
    }
    printf("Sum of odd numbers: %d\n", odd_sum);
}

int main() {
    int limit;

    // Input validation
    printf("Enter the limit: ");
    scanf("%d",&limit);

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Error in creating process
        printf("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Parent process: compute the sum of even numbers
        printf("Child process  computing odd sum...\n");
        compute_odd_sum(limit);
        printf("Child process finished.\n");
    } else {
        // Child process: compute the sum of odd numbers
       printf("Parent process computing even sum...\n");
        compute_even_sum(limit);
        
        // Wait for child process to finish
        printf("Parent process  finished.\n");
    }

    return 0;
}

