#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* create_node(){
    Node* newnode = (Node *)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory Not Allocated\n");
        exit(0);
    }
    printf("Enter data: ");
    scanf("%d",&newnode->data);
    newnode->next=NULL;
    return newnode;
}

void create_list(Node** head, Node** tail){
    printf("Enter no of elements: ");
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        Node * newnode = create_node();
        if(*head==NULL){
            *head=*tail=newnode;
        }
        else{
        (*tail)->next = newnode;
        *tail = newnode;
        }
    }
    (*tail)->next=*head;
    printf("Circular Linked List created\n");
    return;
}

void insert_end(Node** head, Node**tail){
    Node * newnode = create_node();
    if(*head==NULL){
        *head=newnode;
        *tail=newnode;
        (*tail)->next=*head;
        return;
    }
    else{
        (*tail)->next=newnode;
        newnode->next=*head;
        *tail=newnode;
    }
}


void delete_beg(Node** head, Node**tail){
    if(*head==NULL){
        printf("List is empty! Cannot delete");
        return;
    }
    Node* temp = *head;
    if(temp->next==*head){
        printf("Single element");
        *head=NULL;
        *tail = NULL;
        free(temp);
        temp=NULL;
        return;
    }
    else{
        (*tail)->next = (*tail)->next->next;
        *head = (*tail)->next;
        free(temp);
        temp=NULL;
        return;
    }
}

void display(Node* head){
    if(head==NULL){
        printf("List is empty");
        return;
    }
    Node*temp = head;
    do{
        printf("%d--",temp->data);
        temp=temp->next;
    }while(temp!=head);
}

int main(){
    Node* head = NULL;
    Node* tail = NULL;
    printf("1.Creation\n2.Insertion at the end \n3.Deletion from beg\n4.Display\n0.EXIT\n");
    int input=1;
    while(input){
        printf("Enter input: ");
        scanf("%d",&input);
        switch(input){
            case 1: 
            create_list(&head,&tail);
            display(head);
            break;
            case 2: 
            insert_end(&head,&tail);
            display(head);
            break;
            case 3: 
            delete_beg(&head,&tail);
            display(head);
            break;
            case 4:
            display(head);
            break;
            case 0: 
            printf("EXITING");
            break;
            default: 
            printf("Enter valid!");
        }
    }
    return 0;
}