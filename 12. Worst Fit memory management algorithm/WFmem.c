//
//  main.c
//  OS lab 12
//
//  Created by YASH VINAYVANSHI on 03/05/21.
//
//  Worst fit block allocation

#include<stdio.h>
  
int main()
{
    int no_of_blocks;
    int no_of_processes;
    printf("Enter no. of blocks : ");
    scanf("%d", &no_of_blocks);
    printf("Ener no. of processes : ");
    scanf("%d", &no_of_processes);
    int block[no_of_blocks];
    int process[no_of_processes];
    printf("Enter blocks : ");
    for(int i=0; i<no_of_blocks; i++)
    {
        scanf("%d", &block[i]);
    }
    printf("Enter processes : ");
    for(int i=0; i<no_of_processes; i++)
    {
        scanf("%d", &process[i]);
    }
    //to record block which is allocated to each processes
    int block_allocated[no_of_processes];
    for(int i=0; i<no_of_processes; i++)
    {
        //-1 marks that no block is allocated to ith process
        //init no block is allocated to any process
        block_allocated[i] = -1;
    }
    printf("\nProcess No.\tProcess Size\tBlock no.\t internal fragmentation\n");
    for (int i=0; i<no_of_processes; i++)
    {
        // Find the worst fit block for ith process
        int worst_block_index = -1;
        for (int j=0; j<no_of_blocks; j++)
        {
            //block should atleast be bigger than the process
            if (block[j] >= process[i])
            {
                if (worst_block_index == -1) //no block is assigned yet
                    worst_block_index = j;   //jth block is candidate for now
                else if (block[worst_block_index] < block[j])
                    //if a block larger than current candidate block is found, new candidate.
                    worst_block_index = j;
            }
        }
        // If no block is found candidate for ith process
        // ie all blocks at this processes's turn are smaller than it
        if (worst_block_index != -1)
        {
            // Allocate block optimal candidate blaock to ith process
            block_allocated[i] = worst_block_index;
  
            // Decrement space in the block
            // Assuming more than one processes can reside in a block
            block[worst_block_index] -= process[i];
        }
        //display allocation data for ith process
        printf("%d\t\t\t%d\t\t\t\t", i+1, process[i]);
        if (block_allocated[i] != -1)
            printf("%d\t\t\t\t%d\n", block_allocated[i] + 1, block[block_allocated[i]]);
        else
            printf("Not Allocated\n");
    }
    //display allocation data
    /*
     printf("\nProcess No.\tProcess Size\tBlock no.\t internal fragmentation\n");
    for (int i=0; i<no_of_processes; i++)
    {
        printf("%d\t\t\t%d\t\t\t\t", i+1, process[i]);
        if (block_allocated[i] != -1)
            printf("%d\t\t\t\t%d\n", block_allocated[i] + 1, block[block_allocated[i]]);
        else
            printf("Not Allocated\n");
    }
    return 0 ;
     */
}

/*
 A test case
 5
 100 500 200 300 600
 4
 212 417 112 426
 */
