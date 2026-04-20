#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int price;
    struct Node* next;
    struct Node* prev;
}Node;

Node* create_node(int price){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory not allocated\n");
        exit(0);
    }
    newnode->price = price;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

Node* create_list(int n){
    if(n<=0) {
        printf("Enter valid");
        exit(0);
    }
    Node* dummy = create_node(-1);
    Node* curr = dummy;
    for(int i=0; i<n; i++){
        printf("Enter price: ");
        int price;
        scanf("%d",&price);
        Node* newnode = create_node(price);
        curr->next = newnode; 
        newnode->prev = curr;
        curr = newnode;
    }

    return dummy->next;
}

int total(Node* head){
    int sum = 0;
    Node* curr = head; 
    while(curr!=NULL){
        sum+=curr->price;
        curr=curr->next;
    }
    return sum;
}

void display(Node* head){
    Node* curr = head; 
    while(curr!=NULL){
        printf("%d--",curr->price);
        curr=curr->next;
    }
}

void append_total_end(Node* head, int total){
    if(head==NULL){
        printf("List is empty");
        return;
    }
    Node* curr = head; 
    while(curr->next!=NULL){
        curr=curr->next;
    }
    Node* final = create_node(total);
    curr->next = final; 
    final->prev = curr; 

}