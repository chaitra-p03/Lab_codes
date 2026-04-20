#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    char name[30];
    int id; 
    char diag[30];
    struct Node* next; 
    struct Node* prev;
}Node;

Node* create_node(){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Not allocated\n");
        exit(0);
    }
    scanf("%s",newnode->name);
    scanf("%d",&newnode->id);
    scanf("%s",newnode->diag);
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

Node* create_list(int n){
    Node* head = NULL;
    Node* curr = NULL;
    for(int i=0; i<n; i++){
        Node* newnode = create_node();
        if(head==NULL){
            head = curr = newnode;
        }
        else{
            curr->next = newnode;
            newnode->prev = curr;
            curr = newnode;
        }
    }

    return head;
}

void insert_at_pos(Node**head, int pos){
    if(pos<=0) return;

    Node* newnode = create_node();
    if(*head==NULL){
        *head = newnode;
    }
    else if(pos==1){
        newnode->next = *head;
        (*head)->prev = newnode;
        *head = newnode;
    }
    else{
        Node* curr = *head;
        for(int i=1; i<pos && curr!=NULL; i++){
            curr = curr->next;
        }
        if(curr==NULL){
            printf("pos not found");
            return;
        }
        curr->prev->next = newnode;
        newnode->prev = curr->prev;
        newnode->next = curr;
        curr->prev = newnode;
        return;
    }
}

void display(Node* head){
    Node* curr = head;
    while(curr!=NULL){
        printf("%s %d %s",curr->name, curr->id, curr->diag);
        curr = curr->next;
    }
}