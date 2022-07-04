//  main.c
//  OS lab 14
//
//  Created by YASH VINAYVANSHI on 15/05/21.
//
//  FCFS disk scheduling

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
    for(int i=0; i<no_of_requests; i++){
        service_sequence[i]=request_sequence[i];
        head_movement[i]=abs(service_sequence[i]-current_head_pos);
        current_head_pos=service_sequence[i];
        total_head_movement+=head_movement[i];
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
 Test case
 50
 8
 176 79 34 60 92 11 41 114
 */
