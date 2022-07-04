//
//  main.cpp
//  os lab 5
//
//  Created by YASH VINAYVANSHI on 15/03/21.
//

// C++ program for implementation of RR scheduling
#include<iostream>
using namespace std;

struct processes
{
    int PID;
    int ArrivalTime;
    int BurstTime;
    int CompletionTime;
    int TurnaroundTime;
    int WaitingTime;
    int ResponseTime;
};
int Gantt[100];
void FindWaitingTime(struct processes[], int, int);
void FindAvgTime(struct processes[], int);
void PrintGanttChart(struct processes[]);
int main()
{
    int n, quantum;
    cout << "Enter no. of processes : ";
    cin >> n;
    struct processes process[n];
    for(int i=0; i<n; i++)
    {
        cin >> process[i].PID >> process[i].ArrivalTime >> process[i].BurstTime;
    }
    cout <<"Enter size of quanta : ";
    cin >> quantum;
    FindWaitingTime(process, n, quantum);
    FindAvgTime(process, n);
    PrintGanttChart(process);
    return 0;
}

void FindWaitingTime(struct processes process[], int n, int quantum)
{
    for(int i=0; i<100; i++)
        Gantt[i] = 0;
    
    //Init remaining burst times
    int RemainingBurstTime[n];
    
    for (int i = 0 ; i < n ; i++)
        RemainingBurstTime[i] =  process[i].BurstTime;
    
    //Init time
    int t = 0;
    bool attended = false;
    
    //Keep executing processes in round robin manner until all complete
    while (1)
    {
        bool done = true;
        
        //Traverse all processes one by one repeatedly
        for (int i = 0 ; i < n; i++)
        {
            //mark response times
            if(attended == false)
                process[i].ResponseTime = t;
            //If reaming burst time of a process is non zero then only to process further
            if (RemainingBurstTime[i] > 0)
            {
                //Marks that there is/are pending process(s)
                done = false;
                if (RemainingBurstTime[i] > quantum)
                {
                    for(int j=0; j<quantum; j++)
                        Gantt[t+j] = process[i].PID;
                    
                    //one more quantum of time passed with execution of process
                    t += quantum;
                    
                    //current process processed by a quantum
                    RemainingBurstTime[i] -= quantum;
                }
  
                //If burst time is smaller than or equal to quantum. Last cycle for this process
                //And quantum has to be terminated earlier
                else
                {
                    for(int j=0; j<RemainingBurstTime[i]; j++)
                        Gantt[t+j] = process[i].PID;
                    
                    t = t + RemainingBurstTime[i];
  
                    //Waiting time is current time minus time used by this process
                    process[i].WaitingTime = t - process[i].BurstTime;
  
                    //As the process gets fully executed make its remaining burst time = 0
                    RemainingBurstTime[i] = 0;
                    //Record its completion time
                    process[i].CompletionTime = t;
                }
            }
        }
        //All processes attended for first time atleast.
        attended = true;
        // If all processes are done
        if (done == true)
          break;
    }
    for(int i=0; i<n; i++)
        //TAT = CT - AT
        process[i].TurnaroundTime = process[i].CompletionTime + process[i].ArrivalTime;
}
void FindAvgTime(struct processes process[], int n)
{
    int total_wt = 0, total_tat = 0;
    // Display processes along with all details
    cout << "PID\t" << "Arrival_Time\t " << "Burst_Time\t" << "Completion_Time\t" << "TurnAround_Time\t"
         << "Waiting Time\t" << "Response_Time\n";
  
    // Calculate total waiting time and total TAT
    for(int i=0; i<n; i++)
    {
        total_wt += process[i].WaitingTime;
        total_tat += process[i].TurnaroundTime;
        cout << " " << process[i].PID << "\t\t" << process[i].ArrivalTime << "\t\t\t" << process[i].BurstTime << "\t\t\t" << process[i].CompletionTime << "\t\t\t" << process[i].TurnaroundTime << "\t\t\t" << process[i].WaitingTime << "\t\t\t" << process[i].ResponseTime << endl;
    }
    cout << "Average waiting time = " << total_wt / n << endl;
    cout << "Average turn around time = "<< total_tat / n << endl;
}
void PrintGanttChart(struct processes process[])
{
    cout << endl;
    std::cout <<"|";
    for(int i=0; i<100; i++)
    {
        if(Gantt[i+1]!=Gantt[i])
            cout << "p" << Gantt[i] << "\t|";
    }
    cout << endl;
    cout << process[0].ArrivalTime;
    for(int i=0; i<100; i++)
    {
        if(Gantt[i+1]!=Gantt[i])
            cout << "\t" << i+1;
    }
    cout << endl;
}
/*
 Test case
 1 0 4
 2 1 5
 3 2 2
 4 3 1
 5 4 6
 6 6 3
*/
