#include <stdio.h>
#include <stdlib.h>

// using array
#define MAX 10
char stack[MAX];
int top = -1;

void push(char c){
    if(top==MAX-1){
        printf("Overflow");
        return;
    }
    stack[++top]=c;
}

char pop(){
    if(top==-1){
        printf("Underflow");
        return '\0';
    }
    return stack[top--];
}

void peek(){
    if(top==-1){
        printf("Empty\n");
        return;
    }
    printf("Peeked element is %c",stack[top]);
}

void display(){
    int temp = top;
    while(temp!=-1){
    printf("%c ", stack[temp]);
    temp--;
}
}

// using ll 
typedef struct Node{
    int data;
    struct Node* next;
}Node; 

Node* head = NULL;
Node* createnode(int data){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("memory not allocated\n");
        exit(1);
    }
    newnode->data = data;
    newnode->next = NULL;

    return newnode;
}

void push(int data){
    Node* newnode = createnode(data);

    newnode->next = head;
    head = newnode;
    
}

int pop(){
    if(head == NULL){
        printf("Underflow!");
        return -1;
    }
    
    int data = head->data;
    Node* popped = head;
    head = head->next;
    free(popped);
    return data;
}

// if popped was being returned 
// Node* popped = head;
// head = head->next;
// popped->next = NULL;
// return popped;

void display(){
    Node* temp = head;
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp = temp->next;
    }
}

void peek(){
    if(head==NULL){
        printf("Empty!");
        return;
    }
    printf("%d ",head->data);
}



// int = return -1 
// Node* = return NULL
// void = return
// char = return '\0'