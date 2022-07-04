//  main.c
//  OS lab 17
//
//  Created by YASH VINAYVANSHI on 15/05/21.
//
//  LOOK disk scheduling

#include <stdio.h>
#include <stdlib.h>
int main(){
    int init_head_pos;
    printf("Enter initial head position : ");
    scanf("%d", &init_head_pos);
    int no_of_requests;
    printf("Enter Request Sequence Size : ");
    scanf("%d", &no_of_requests);
    int request_sequence[no_of_requests];
    printf("Enter Request sequence : ");
    for(int i=0; i<no_of_requests; i++){
        scanf("%d", &request_sequence[i]);
    }
    int service_sequence[no_of_requests];
    int head_movement[no_of_requests];
    int total_head_movement=0;
    int current_head_pos=init_head_pos;
    //bubble sort on request sequence
    for(int i=1; i<no_of_requests; i++){
        for(int j=0; j<no_of_requests-i; j++){
            if(request_sequence[j]>request_sequence[j+1]){
                int temp = request_sequence[j];
                request_sequence[j]=request_sequence[j+1];
                request_sequence[j+1]=temp;
            }
        }
    }
    int index=-1;
    for(int i=0; i<no_of_requests; i++){
        if(request_sequence[i]>init_head_pos){
            index=i-1;
            break;
        }
    }
    //scans towards nearest end first
    if(request_sequence[no_of_requests-1]-init_head_pos>init_head_pos){
        int count=0;
        for(int i=index; i>=0; i--){
            service_sequence[count]=request_sequence[i];
            head_movement[count]=abs(current_head_pos-request_sequence[i]);
            total_head_movement+=head_movement[count];
            current_head_pos=request_sequence[i];
            count++;
        }
        for(int i=index+1; i<no_of_requests; i++){
            service_sequence[count]=request_sequence[i];
            head_movement[count]=abs(current_head_pos-request_sequence[i]);
            total_head_movement+=head_movement[count];
            current_head_pos=request_sequence[i];
            count++;
        }
    }
    else{
        int count=0;
        for(int i=index+1; i<no_of_requests; i++){
            service_sequence[count]=request_sequence[i];
            head_movement[count]=abs(current_head_pos-request_sequence[i]);
            total_head_movement+= head_movement[count];
            current_head_pos=request_sequence[i];
            count++;
        }
        for(int i=index; i>=0; i--){
            service_sequence[count]=request_sequence[i];
            head_movement[count]=abs(current_head_pos-request_sequence[i]);
            total_head_movement+= head_movement[count];
            current_head_pos=request_sequence[i];
            count++;
        }
    }
    printf("\nTrack visited from->to    head movement(in no. of tracks)\n");
    printf("%d -> %d\t\t\t\t  %d\n", init_head_pos, service_sequence[0], head_movement[0]);
    for(int i=1; i<no_of_requests; i++){
        printf("%d -> %d\t\t\t\t  %d\n", service_sequence[i-1], service_sequence[i], head_movement[i]);
    }
    printf("\nTotal head movement : %d tracks\n", total_head_movement);
    printf("Average head movement : %f tracks per seek\n", (float)total_head_movement/(float)no_of_requests);
    return 0;
}
/*
 Test case1
 50 (towards left end)
 8
 176 79 34 60 92 11 41 114

 Test case2
 120 (towards right end)
 8
 176 79 34 60 92 11 41 114
 */

