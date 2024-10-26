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