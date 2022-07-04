//  OS lab 1 : Implement the priority queue scheduling algorithm using linked list.
//  Created by YASH VINAYVANSHI 19BCS081 on 15/02/21.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node* add_process(struct node*); //O(n^2)
struct node* execute_process(struct node*); //O(1)
void display_schedule(struct node*); //O(n)
struct node
{
    char process_name[5];
    int process_priority;
    struct node* next;
};
int main()
{
    printf("________MAIN MENU________\n");
    printf("1. Add process\n");
    printf("2. Execute process\n");
    printf("3. Exit\n\n");
    
    struct node* head = NULL;
    
    int choice = 0;
    do
    {
        printf("Enter Choice code : ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1 :
                head = add_process(head);
                display_schedule(head);
                break;
            case 2 :
                head = execute_process(head);
                display_schedule(head);
                break;
        }
    }while(choice != 3);
    return 0;
}
struct node* add_process(struct node* head)
{
    char process_name[5];
    int process_priority;
    printf("Enter process_name : ");
    scanf("%s", process_name);
    printf("Enter process_priority : ");
    scanf("%d", &process_priority);
    printf("\n");
           
    //if queue empty
    if(head == NULL)
    {
        head = (struct node*)malloc(sizeof(struct node));
        strcpy(head -> process_name, process_name);
        head -> process_priority = process_priority;
        head -> next = NULL;
        printf("Process '%s' successfully added to priority schedule.\n", process_name);
        return head;
    }
    else
    {
        //traverse list
        struct node* temp;
        struct node* temp1 = NULL;
        temp = head;
        temp1 = head;
        while(temp -> process_priority >= process_priority && temp -> next != NULL)
        {
            temp1 = temp;
            temp = temp -> next;
        }
        //make new node
        struct node* new_node;
        new_node = (struct node*)malloc(sizeof(struct node));
        new_node -> next = NULL;
        
        //insert at beginning
        if(temp1 == head)
        {
            if(temp -> process_priority < process_priority)
            {
                new_node -> next = head;
                head = new_node;
                strcpy(head -> process_name, process_name);
                head -> process_priority = process_priority;
            }
            else
            {
                new_node -> next = head -> next;
                head -> next = new_node;
                strcpy(new_node -> process_name, process_name);
                new_node -> process_priority = process_priority;
            }
        }

        //insert at end
        else if(temp -> next == NULL)
        {
            temp -> next = new_node;
            new_node -> next = NULL;
            strcpy(new_node -> process_name, process_name);
            new_node -> process_priority = process_priority;
        }

        //insert in middle
        else
        {
            new_node -> next = temp1 -> next;
            temp1 -> next = new_node;
            strcpy(new_node -> process_name, process_name);
            new_node -> process_priority = process_priority;
        }
        printf("Process '%s' successfully added to priority schedule.\n", process_name);
        return head;
    }
}
struct node* execute_process(struct node* head)
{

    if(head == NULL)
        return head;
    else
    {
    
        //simple delete from head where lies process with highest priority
        printf("Process |%s|%d| has been executed\n", head -> process_name, head -> process_priority);
        struct node* temp;
        temp = head;
        head = head -> next;
        free(temp);

    }
    return head;

}
void display_schedule(struct node* head)
{
    struct node* temp = NULL;
    if(head == NULL)
    {
        printf("Error : no process is queued\n\n");
    }
    else
    {
        printf("Current priority queue is : ");
        temp = head;
        printf("|%s|%d|-->", temp -> process_name, temp -> process_priority);

        while(temp -> next != NULL)
        {
            temp = temp -> next;
            printf("|%s|%d|-->", temp -> process_name, temp -> process_priority);
        }
        printf("NULL\n\n");
    }
}
