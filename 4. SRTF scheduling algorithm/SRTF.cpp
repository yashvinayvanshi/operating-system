//
//  main.cpp
//  OS lab 4
//
//  Created by YASH VINAYVANSHI on 08/03/21.
//
  
#include <iostream>
using namespace std;
  
struct ProcessAttributes {
    int ProcessID;
    int BurstTime;
    int ArrivalTime;
    int ResponseTime;
    int CompletionTime;
    int WaitingTime;
    int TurnAroundTime;
};
int Gantt[100];
void FindWaitingTime(ProcessAttributes[], int);
void FindTurnAroundTime(ProcessAttributes[], int);
void FindAvgTime(ProcessAttributes[], int);
void PrintGanttChart(ProcessAttributes[]);


int main()
{
    int n;
    cout << "Enter no. of processes : ";
    cin >> n;
    ProcessAttributes Process[n];
    for(int i=0; i<n; i++)
    {
        cin >> Process[i].ProcessID >> Process[i].BurstTime >> Process[i].ArrivalTime;
    }
    FindAvgTime(Process, n);
    PrintGanttChart(Process);
    return 0;
}

  
void FindWaitingTime(ProcessAttributes Process[], int n)
{
    //Array to store remaining times of processes
    int RemainingTime[n];
    for(int i=0; i<n; i++)
        Process[i].ResponseTime = -1;
    
    //Initially remaining times are nothing else but complete burst times
    for (int i = 0; i < n; i++)
        RemainingTime[i] = Process[i].BurstTime;
    
    for(int i=0; i<100; i++)
        Gantt[i] = 0;
    //Declarations
    int complete = 0,
    t = 0, //time step
    min = INT_MAX; //Shortest remaining time in ready queue
    int shortest = 0; //index of shortest reaming time job
    bool check = false;
    //compute for all processes
    while (complete != n)
    {
        // Find process with minimum remaining time among the processes that are in ready queue by the current time`
        for (int j = 0; j < n; j++)
        {
            if ((Process[j].ArrivalTime <= t) && (RemainingTime[j] < min) && RemainingTime[j] > 0)
            {
                min = RemainingTime[j];
                shortest = j;
                check = true; //SRT job has been chosen for execution
                if(Process[j].ResponseTime == -1)
                    Process[j].ResponseTime = t;
            }
        }
        //no SRT job for execution, CPU idle, time step goes on.
        if (check == false)
        {
            Gantt[t] = -1;
            t++;
            continue;
        }
        Gantt[t] = shortest;
        // Reduce remaining time of job in execution by one
        // Considered time quanta to be one unit of time
        RemainingTime[shortest]--;
  
        // Update minimum as remaining time of SRT Job is reduced
        min = RemainingTime[shortest];
        // If just executed SRT job is complete
        if (min == 0)
            min = INT_MAX;
        if (RemainingTime[shortest] == 0) {
  
            // Increment complete
            complete++;
            check = false;
  
            // Find finish time of current process
            Process[shortest].CompletionTime = t + 1;
  
            // Calculate waiting time
            Process[shortest].WaitingTime = Process[shortest].CompletionTime - Process[shortest].BurstTime - Process[shortest].ArrivalTime;
  
            if (Process[shortest].WaitingTime < 0)
                Process[shortest].WaitingTime = 0;
        }
        // Increment time
        t++;
    }
}
  
void FindTurnAroundTime(ProcessAttributes Process[], int n)
{
    // TAT = BT + WT
    for (int i = 0; i < n; i++)
        Process[i].TurnAroundTime = Process[i].BurstTime + Process[i].WaitingTime;
}
  
// Function to calculate average time
void FindAvgTime(ProcessAttributes Process[], int n)
{
    int TotalCompletionTime = 0;
    int TotalResponseTime = 0;
    int TotalWaitingTime = 0;
    int TotalTurnAroundTime = 0;
  
    // Function to find waiting time of all processes
    FindWaitingTime(Process, n);
  
    // Function to find turn around time for all processes
    FindTurnAroundTime(Process, n);
  
    // Display processes along with all details
    cout << "Processes "<< " Burst time "<< " Arrival Time " << "Completion Time " << " Response time " << " Waiting time "<< " Turn around time\n";
  
    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        TotalWaitingTime += Process[i].WaitingTime;
        TotalTurnAroundTime += Process[i].TurnAroundTime;
        TotalCompletionTime += Process[i].CompletionTime;
        TotalResponseTime += Process[i].ResponseTime;
        cout << " " << Process[i].ProcessID << "\t\t\t" << Process[i].BurstTime << "\t\t\t " << Process[i].ArrivalTime << "\t\t\t " << Process[i].CompletionTime << "\t\t\t\t "<< Process[i].ResponseTime << "\t\t\t\t " << Process[i].WaitingTime << "\t\t\t " << Process[i].TurnAroundTime << endl;
    }
    cout << "\nAverage completion time = "<< (float)TotalCompletionTime / (float)n;
    cout << "\nAverage response time = "<< (float)TotalResponseTime / (float)n;
    cout << "\nAverage waiting time = "<< (float)TotalWaitingTime / (float)n;
    cout << "\nAverage turn around time = "<< (float)TotalTurnAroundTime / (float)n <<endl;
    
 
}
void PrintGanttChart(ProcessAttributes Process[])
{
    cout << endl;
    std::cout <<"|";
    for(int i=0; i<100; i++)
    {
        if(Gantt[i+1]!=Gantt[i])
            cout << "p" << Gantt[i] << "   |";
    }
    cout << endl;
    cout << Process[0].ArrivalTime << "     ";
    for(int i=0; i<100; i++)
    {
        if(Gantt[i+1]!=Gantt[i])
            cout << i << "     ";
    }
    cout << endl;
}
  
/*
 Test Case
 0 9 0
 1 10 0
 2 1 3
 3 1 6
 4 2 10
 */
