//
//  main.c
//  os lab 2 corrected
//
//  Created by YASH VINAYVANSHI on 22/02/21.
//
//  input : three-tuples : process_name submission_time burst_time
//  output : table attributes : process_id submission_time burst_time reaponse_time completion_time;
//           average waiting time, average turnaround time
//
//  NOTES
//      arrival time : time when process enters ready queue
//      burst time : time of CPU required by process
//      response time : time spent between ready state and getting CPU for the first time
//      waiting time : time spent in ready state
//      completion time : time at which process completes its execution
//      turnaround time : total time passes form submission of process to its completion
//      in this case since we've considered a non premptive processing system -> waiting time is same as response time
//

#include<stdio.h>

int main()
{
    
    //inputs----------------------------------------------------------------------------
    int n;
    printf("Enter no. of processes : ");
    scanf("%d", &n);
    int processes[n];
    int burst_time[n];
    int submission_time[n];
    for(int i=0; i<n; i++)
    {
        scanf("%d %d %d", &processes[i], &submission_time[i], &burst_time[i]);
    }
    
    //outputs----------------------------------------------------------------------------
    int waiting_time[n];
    int turnaround_time[n];
    int completion_time[n];
    
    //Computing waiting time for each process--------------------------------------------
    //first process has zero waiting time
    //this is just like dp
    waiting_time[0] = 0;
    for (int i = 1; i < n ; i++)
    {
        waiting_time[i] =  burst_time[i-1] + waiting_time[i-1] - submission_time[i] + submission_time[0];
        if(waiting_time[i]<0)
            waiting_time[i] = 0;
    }
    
    //Computing completion time for each process-----------------------------------------
    completion_time[0] = waiting_time[0] + burst_time[0] + submission_time[0];
    for(int i=1; i < n; i++)
    {
        if(submission_time[i] <= submission_time[i-1]+burst_time[i-1])
            completion_time[i] = completion_time[i-1] + burst_time[i];
        else
            completion_time[i] = completion_time[i-1] + submission_time[i] - submission_time[i-1] - burst_time[i-1] + burst_time[i];
    }
    
    //Computing turnaround time for each process-----------------------------------------
    for (int i = 0; i < n ; i++)
        turnaround_time[i] = completion_time[i] - submission_time[i];
    

    //Computing average waiting time & average turnaround time---------------------------
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for(int i = 0; i < n; i++)
    {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    int s = (float)total_waiting_time / (float)n;
    int t = (float)total_turnaround_time / (float)n;
    
    //Display processes along with all details in a table--------------------------------
    printf("Process_id    Subm. time    Burst time   Resp. time   Compl time   TurnAr. time\n");
    for (int  i=0; i<n; i++)
    {
        printf("   %d",processes[i]);
        printf("             %d", submission_time[i]);
        printf("             %d", burst_time[i]);
        printf("             %d", waiting_time[i]);
        printf("             %d", completion_time[i]);
        printf("             %d\n", turnaround_time[i]);
    }

    printf("Average waiting time = %d\n",s);
    printf("Average turn around time = %d\n\n",t);
    
    //Produce Gantt Chart : type 1--------------------------------------------------------
    printf("Gantt Chart : type 1\n");
    printf("Process id./time ->  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25\n");
    for(int i=0; i<n; i++)
    {
        printf("%d                    ", processes[i]);
        for(int j=0; j<submission_time[i]; j++)
            printf("   ");
        for(int j=submission_time[i]; j<=submission_time[i]+burst_time[i]-1; j++)
            printf("***");
        printf(">>");
        printf("\n");
    }
    
    //Produce Gantt Chart : type 2----------------------------------------------------------
    printf("\nGantt Chart : type 2\n");
    
    printf("|p%d", processes[0]);
    for(int i=1; i<n; i++)
    {
        if(burst_time[i] < completion_time[i]-completion_time[i-1])
        {
            for(int j=0; j<burst_time[i]; j++)
                printf(" ");
            for(int j=0; j < completion_time[i] - completion_time[i-1] - burst_time[i]; j++)
                printf("-");
        }
        else
        {
            for(int j=0; j<completion_time[i]-completion_time[i-1]; j++)
            printf(" ");
        }
        printf("|p%d", processes[i]);
        
    }
    printf("|\n");
    printf("%d", submission_time[0]);
    for(int i=1; i<n; i++)
    {
        if(burst_time[i] < completion_time[i]-completion_time[i-1])
        {
            for(int j=0; j<burst_time[i]; j++)
                printf(" ");
            printf(" %d", completion_time[i-1]);
            for(int j=0; j < completion_time[i] - completion_time[i-1] - burst_time[i]; j++)
                printf("-");
            printf(" %d", completion_time[i] - burst_time[i]);
        }
        else
        {
            for(int j=0; j<completion_time[i]-completion_time[i-1]; j++)
            printf(" ");
            printf(" %d", completion_time[i-1]);
        }
    }
    printf("\n");
}
    
