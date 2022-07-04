//
//  main.cpp
//  OS lab 3
//
//  Created by YASH VINAYVANSHI on 28/02/21.
//  Non Preemtive Shortest Job first
#include<iostream>

void SortByArrival(int, int [][6]);
void CompletionTime(int, int [][6]);
void ProduceGanttChart(int, int[][6]);
int main()
{
    //input no. of processses
    int n;
    std::cout << "Enter number of Processes: ";
    std::cin >> n;
    
    //declare a table with 6 columns holding various parameters regarding processes (n in number)
    int table[n][6];
    
    //input process details
    std::cout << "---Enter the processes Details---\n";
    for(int i=0; i<n; i++)
        //Enter Process Id, Arrival time, Burst time
        std::cin >> table[i][0] >> table[i][1] >> table[i][2];
    
    //print table beforre schduling
    std::cout<<"---Before Scheduling---\n";
    std::cout<<"Process ID\tArrival Time\tBurst Time\n";
    for(int i = 0; i < n; i++)
    {
        std::cout<<table[i][0]<<"\t\t"<<table[i][1]<<"\t\t"<<table[i][2]<<"\n";
    }
    
    //
    SortByArrival(n, table);
    CompletionTime(n, table);
    
    //print table after scheduling and executing processes
    std::cout<<"---Final Result---\n";
    std::cout<<"Process ID\tArrival Time\tBurst Time\tCompletion time\tWaiting Time\tTurnaround Time\n";
    for(int i = 0; i < n; i++)
    {
        std::cout<<table[i][0]<<"\t\t\t"<<table[i][1]<<"\t\t\t\t"<<table[i][2]<<"\t\t\t"<<table[i][3]<<"\t\t\t"<<table[i][4]<<"\t\t\t"<<table[i][5]<<"\n";
    }
    
    //Calculate average waiting time ad average turnaroud time
    int temp1 = 0;
    int temp2 = 0;
    for(int i = 0; i < n; i++)
    {
        temp1 += table[i][4];
        temp2 += table[i][5];
    }
    std::cout <<"average waiting time = "<< temp1/n << "\n";
    std::cout <<"average turnaround time = "<<temp2/n << "\n";
    
    ProduceGanttChart(n, table);
    return 0;
}
//Sorting by arrival is required because a shortest job coming later will be executed later as well bec this is nonpreemptive SJF
void SortByArrival(int n, int table[][6])
{
    //Sorting rows based on arrival time : used bubble sort here
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(table[j][1] > table[j+1][1])
            {
                //swap all attributes of rows based on sorting of arrival time attribute
                for(int k = 0; k < 5; k++)
                {
                    //swap mat[j][k], mat[j+1][k]
                    int temp = table[j][k];
                    table[j][k] = table[j+1][k];
                    table[j+1][k] = temp;
                }
            }
        }
    }
}
void CompletionTime(int n, int table[][6])
{
    //initialise first row
    //completion time = arrival time + burst time
    table[0][3] = table[0][1] + table[0][2];
    //turnaround time = completion time - arrival time
    table[0][5] = table[0][3] - table[0][1];
    //waiting time = turnaround time - burst time
    table[0][4] = table[0][5] - table[0][2];
     
    //calculate other rows
    int temp, val=0;
    for(int i=1; i<n; i++) //ith job is currently considered
    {
        temp = table[i-1][3]; //completion time of previous job
        int low = table[i][2]; //burst time of ith job
        //all other jobs have to wait until this ith job is complete
        for(int j=i; j<n; j++) //for all jobs ahead of ith job by arrival times
        {
            //case when cpu will remain idle : Cpu free and no job in ready queue yet
            //completion time of prev. job >= arrival time of job ahead
            //  to ensure that the job is present in the ready queue already

            if(temp >= table[j][1] && low >= table[j][2])
            {
                //choose job with smallest burst time for execution 
                low = table[j][2];
                val = j;
            }
        }
        //CT = AT + BT
        table[val][3] = temp + table[val][2];
        //TAT = CT - AT
        table[val][5] = table[val][3] - table[val][1];
        //WT = TAT - BT
        table[val][4] = table[val][5] - table[val][2];
        for(int k=0; k<6; k++)
        {
            //swap table[val][k], table[i][k]
            int temp = table[val][k];
            table[val][k] = table[i][k];
            table[i][k] = temp;
        }
    }
}
void ProduceGanttChart(int n, int table[][6])
{
    std::cout <<"|";
    for(int i = 0; i < n; i++)
    {
        std::cout << "p"<<table[i][0]<<"\t|";
    }
    std::cout << "\n";
    std::cout << table[0][1] << "   ";
    for(int i = 0; i < n; i++)
    {
        std::cout << table[i][3] << "   ";
    }
    std::cout << "\n";
}
  


