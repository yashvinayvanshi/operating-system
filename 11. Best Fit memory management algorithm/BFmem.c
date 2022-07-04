//
//  main.c
//  OS lab 11
//
//  Created by YASH VINAYVANSHI on 19/04/21.
//
//  Best fit block allocation

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int main(){
    int no_of_blocks;
    int no_of_processes;
    printf("Enter no. of blocks : ");
    scanf("%d", &no_of_blocks);
    int block[no_of_blocks];
    printf("Enter blocks : ");
    for(int i=0; i<no_of_blocks; i++){
        scanf("%d", &block[i]);
    }
    printf("Enter no. of processes : ");
    scanf("%d", &no_of_processes);
    int process[no_of_processes];
    printf("Enter processes : ");
    for(int i=0; i<no_of_processes; i++){
        scanf("%d", &process[i]);
    }
    //to record which block is assigned to a process if assigned
    int block_assigned[no_of_processes];
    //to record which blocks are occupied
    //Assuming two processes cannot reside in the same page
    bool block_occupied[no_of_blocks];
    //-1 indicated no block is assigned to ith process
    memset(block_assigned, -1, sizeof(block_assigned));
    //false means block is free to be allocated
    memset(block_occupied, false, sizeof(block_occupied));
    printf("ProcessId\tBlock Allotted\t Internal fragmentation\n");
    for(int i=0; i<no_of_processes; i++){
        int min = 10000;
        //to store which block is assigned to ith process
        int blockallocated=-1;
        //find the best fit block
        for(int j=0; j<no_of_blocks; j++){
            if((block[j]<min) && ((block[j]>=process[i]) && (block_occupied[j]==false))){
                min = block[j];
                blockallocated = j;
            }
        }
        block_assigned[i]=blockallocated;
        block_occupied[blockallocated]=true;
        if(blockallocated!=-1)
            printf("%d\t\t\t%d\t\t\t%d\n", i+1, blockallocated+1, block[blockallocated]-process[i]);
        else
            printf("%d\t\t\tNot Allocated\n", i+1);
    }
}
/*
 Test case
 5
 100 500 200 300 600
 4
 212 417 112 426
*/
