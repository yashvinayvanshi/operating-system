//
//  main.c
//  os lab 7
//
//  Created by YASH VINAYVANSHI on 11/04/21.
//  Preemptive priority scheduling

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

//data structures
struct process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int response_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int priority;
    int progress;
    int status;
    //status = 0 : process not executed on cpu even once
    //status = 1 : process completed
    //status = 2 : process under progress or process is reponded atleast once
}process_queue[10];
int no_of_processes;
int gantt[100];

//functions
void Arrival_Time_Sorting(void);
void record_event(int, int, int); //starting time, ending time, pid
void print_gantt_chart(void);

int main()
{
    //declatarions
    int quanta;
    int time = 0;
    int largest;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    float total_response_time = 0;
    float total_completion_time = 0;
    float average_response_time;
    float average_waiting_time;
    float average_turnaround_time;
    float average_completion_time;
    
    //Input process attributes
    printf("\nEnter Total Number of Processes : ");
    scanf("%d", &no_of_processes);
    printf("\nEnter quanta : ");
    scanf("%d", &quanta);
    printf("\nEnter Details For Processes : \n");
    for(int i = 0; i < no_of_processes; i++)
    {
        scanf("%d %d %d %d", &process_queue[i].process_id, &process_queue[i].arrival_time, &process_queue[i].burst_time, &process_queue[i].priority);
    }
    for(int i=0; i<100; i++)
    gantt[i] = -1;
    
    //assuming user doesn't already input process by arrival time
    //process queue sorted by arrival time
    Arrival_Time_Sorting();
    
    //Execution course begins
    process_queue[9].priority = -9999; //Give last process the lowest possible priority
    time = 0;
    int num = 0;
    while(1)
    {
        //exit condition : all processes given are executed
        if(num == no_of_processes)
            break;
        
        //find the largest priority arrived process in the process_queue
        largest = 9;
        bool isfound = false;
        for(int i = 0; i < no_of_processes; i++)
        {
            if(process_queue[i].arrival_time <= time && process_queue[i].status != 1 && process_queue[i].priority > process_queue[largest].priority)
                //process eligible to check if it has come before the current time
                //process considered for ready queue if its not completed yet
            {
                largest = i;
                isfound = true;
            }
        }
        //cpu idle case : no process found in ready queue
        if(isfound == false)
        {
            record_event(time, time, -1);
            time++;
            continue;
        }
            
        //if remaining time of process > quanta, execute it for a quanta then prempt check
        if(process_queue[largest].burst_time-process_queue[largest].progress>=quanta)
        {
            if(process_queue[largest].status == 0)
            {
                process_queue[largest].response_time = time - process_queue[largest].arrival_time;
                process_queue[largest].status = 2;
            }
            record_event(time, time+quanta, process_queue[largest].process_id);
            time = time + quanta;
            process_queue[largest].progress += quanta;
            continue;
        }
        
        //if remaining time of process < quanta, process completes and terminates before a full quanta
        else
        {
            record_event(time,  process_queue[largest].burst_time-process_queue[largest].progress, process_queue[largest].process_id);
            time = time + process_queue[largest].burst_time-process_queue[largest].progress;
            process_queue[largest].progress = process_queue[largest].burst_time;
            //process completes
            process_queue[largest].status = 1;
            //calculate all other attributes since the process has completed.
            //completion time
            process_queue[largest].completion_time = time;
            //waiting time
            process_queue[largest].waiting_time = process_queue[largest].completion_time - process_queue[largest].arrival_time - process_queue[largest].burst_time;
            //turnaround time
            process_queue[largest].turnaround_time = process_queue[largest].completion_time - process_queue[largest].arrival_time;
            total_waiting_time += process_queue[largest].waiting_time;
            total_turnaround_time += process_queue[largest].turnaround_time;
            total_response_time += process_queue[largest].response_time;
            total_completion_time += process_queue[largest].completion_time;
            //one more process completed
            num++;
            continue;
        }
    }
    
    //display execution details
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tResponse Time\tCompln Time\tWaiting Time\tTurnaround Time");
    for(int i=0; i<no_of_processes; i++)
        printf("\n%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d", process_queue[i].process_id, process_queue[i].arrival_time, process_queue[i].burst_time, process_queue[i].priority, process_queue[i].response_time, process_queue[i].completion_time, process_queue[i].waiting_time, process_queue[i].turnaround_time);
    average_waiting_time = total_waiting_time / no_of_processes;
    average_turnaround_time = total_turnaround_time / no_of_processes;
    average_response_time = total_response_time / no_of_processes;
    average_completion_time = total_completion_time / no_of_processes;
    printf("\n\nAverage waiting time:\t%f\n", average_waiting_time);
    printf("Average Turnaround Time:\t%f\n", average_turnaround_time);
    printf("Average Response Time:\t%f\n", average_response_time);
    printf("Average Completion Time:\t%f\n", average_completion_time);
    
    //print gantt chart
    print_gantt_chart();
    
    return 0;
}
void Arrival_Time_Sorting()
{
    struct process temp;
    //selection sort
    for(int i = 0; i < no_of_processes - 1; i++)
    {
        for(int j = i + 1; j < no_of_processes; j++)
        {
                if(process_queue[i].arrival_time > process_queue[j].arrival_time)
                {
                    //put process in right row in order of their priority
                    temp = process_queue[i];
                    process_queue[i] = process_queue[j];
                    process_queue[j] = temp;
                }
        }
    }
}
void record_event(int start_time, int end_time, int pid)
{
    for(int i=start_time; i<=end_time; i++)
        gantt[i] = pid;
}
void print_gantt_chart(void)
{
    printf("Gantt Array is : \n");
    for(int i=0; i<100; i++)
        printf("%d ", gantt[i]);
    
    printf("\nGantt Chart is : \n");
    printf("|");
    for(int i=0; i<100; i++)
    {
        if(gantt[i]!=gantt[i+1])
            printf("%d\t|", gantt[i]);
    }
    printf("\n");
    printf("0\t");
    for(int i=0; i<100; i++)
    {
        if(gantt[i+1]!=gantt[i])
            printf("%d\t", i+1);
    }
    printf("\n");
}

