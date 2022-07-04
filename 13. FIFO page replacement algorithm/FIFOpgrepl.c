//  main.c
//  OS lab 13
//
//  Created by YASH VINAYVANSHI on 15/05/21.
//
//  FIFO page replacement

#include <stdio.h>
#include <stdbool.h>
int main()
{
    int no_of_pages;
    printf("Enter No. of pages in MM : ");
    scanf("%d", &no_of_pages);
    int size_of_reference_string;
    printf("Enter Size of reference string : ");
    scanf("%d", &size_of_reference_string);
    char reference_string[size_of_reference_string];
    printf("Enter Reference String : ");
    scanf("%s", reference_string);
    char allocation[no_of_pages];
    int entry[no_of_pages];
    for(int i=0; i<no_of_pages; i++){
        allocation[i]='-';
        entry[i]=-1;
    }
    int count=0;
    int fault=0;
    int hit=0;
    for(int i=0; i<size_of_reference_string; i++){
        int block=reference_string[i];
        bool flag=false;
        for(int j=0; j<no_of_pages; j++){
            if(allocation[j]==block){
                flag= true;    //MM hit
                hit++;
                printf("page : %c ; ", reference_string[i]);
                printf("result : page hit ;                ");
                printf("MM : ");
                for(int k=0; k<no_of_pages; k++){
                    printf("%c ", allocation[k]);
                }
                printf("\n");
            }
        }
        if(flag==false){ //MM miss
            fault++;
            int min=entry[0]; //first in block will have smallest count
            int victim=0;
            for(int j=0; j<no_of_pages; j++){ //find first in block
                if(entry[j]<min){
                    min=entry[j];
                    victim=j;
                }
            }
            count++;
            char removed=allocation[victim];
            allocation[victim]=reference_string[i];
            entry[victim]=count;
            printf("page : %c ; ", reference_string[i]);
            printf("result : page fault ; ");
            printf("victim : %c ; ", removed);
            printf("MM : ");
            for(int k=0; k<no_of_pages; k++){
                printf("%c ", allocation[k]);
            }
            printf("\n");
        }
    }
    printf("\nTotal pages : %d\n", size_of_reference_string);
    printf("Total faults : %d\n", fault);
    printf("Total hits : %d\n", hit);
    printf("Average fault : %f %%\n", (float)fault*100/(float)size_of_reference_string);
    return 0;
}
/*
 Test case
 Enter No. of pages in MM : 3
 Enter Size of reference string : 20
 Enter Reference String : HABCADAECDADCBCABHAB
 */
