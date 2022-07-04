//
//  main.c
//  OS lab 9
//
//  Created by YASH VINAYVANSHI on 14/04/21.
//
//  first-fit algorithm in memory management

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

void first_fit(int[], int, int[], int);
int main()
{
    int no_of_blocks;
    printf("Enter no. of blocks in memory : ");
    scanf("%d", &no_of_blocks);
    int block_sizes[no_of_blocks];
    printf("Enter block Sizes : ");
    for (int i = 0; i < no_of_blocks; i++)
        scanf("%d", &block_sizes[i]);
    int no_of_processes;
    printf("Enter no. of processes : ");
    scanf("%d", &no_of_processes);
    int process_sizes[no_of_processes];
    printf("Enter process sizes : ");
    for (int i = 0; i < no_of_processes; i++)
        scanf("%d", &process_sizes[i]);
    first_fit(block_sizes, no_of_blocks, process_sizes, no_of_processes);
    return 0 ;
}
void first_fit(int block_sizes[], int no_of_blocks, int process_sizes[], int no_of_processes)
{
    printf("\nProcess No.\tProcess Size\tBlock no.\tinternal fragmentaion\n");
    // Stores block id of the block allocated to a process
    int allocated_block_id[no_of_processes];
    // Initially no block is assigned to any process
    memset(allocated_block_id, -1, sizeof(allocated_block_id));
    // pick each process and find suitable blocks according to its size and assign to it
    bool allocated;
    for (int i = 0; i < no_of_processes; i++)
    {
        allocated = false;
        printf("%d\t\t\t%d\t\t\t\t", i+1, process_sizes[i]);
        for (int j = 0; j < no_of_blocks; j++)
        {
            if (block_sizes[j] >= process_sizes[i])
            {
                // allocate jth to ith process if size of jth block is enough to accomodate ith process
                allocated_block_id[i] = j;
                // Reduce available memory in this block.
                block_sizes[j] -= process_sizes[i];
                printf("%d\t\t\t\t%d\n", allocated_block_id[i] + 1, block_sizes[allocated_block_id[i]]);
                allocated = true;
                break;
            }
        }
        if(allocated == false)
        {
            printf("Not Allocated");
            printf("\n");
        }
    }
}
/*
 A testcase
 5
 100 500 200 300 600
 4
 220 415 112 428
 */
