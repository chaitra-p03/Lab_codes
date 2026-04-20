// priority queues

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    int id;
    char name[20];
    int priority;
    struct Node* next;
}Node;

Node* front = NULL;
Node* rear = NULL;

Node* getnode(int id, char* name, int p){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory not allocated\n");
        exit(1);
    }
    newnode->id = id;
    strcpy(newnode->name,name);
    newnode->priority=p;
    newnode->next = NULL;

    return newnode;
}

void add(Node* patient){
    if(front==NULL){
        front = patient;
        rear = patient;
        return;
    }
    int p = patient->priority; 
    if(p==1){  // add to front
        patient->next=front;
        front=patient;
        return;
    }
    else{
       rear->next = patient;
       rear = patient;
       return; 
    }
}

Node* serve(){
    if(front==NULL){
        printf("empty\n");
        return NULL;
    }
    if(front->next==NULL){
        rear=NULL;
        Node* temp = front;
        front=NULL;
        return temp;
    }
    else{
        Node* temp = front;
        front=front->next;
        return temp;
    }
}

void display(){
    int e=0;
    int r=0;
    Node*temp = front;
    while(temp!=NULL){
        printf("%d %s %d | ",temp->id, temp->name, temp->priority);
        if(temp->priority==1) e++;
        else if(temp->priority==2) r++;
        temp = temp->next;
    }
    printf("\nCount of Emergency is %d and regular is %d\n",e,r);
}

int main(){
    printf("1. Add 2.Serve 2.Display 4.Exit\n");
    int input=1;
    while(input){
        printf("Enter input: ");
        scanf("%d",&input);
        switch(input){
            case 1: printf("Enter id, name, priority: ");
            int id, p;
            char name[20];
            scanf("%d",&id);
            scanf("%s",name);
            scanf("");
            scanf("%d",&p);
            Node* newnode = getnode(id, name, p);
            add(newnode);
            break;

            case 2: 
            printf("Served: \n");
            Node* served = serve();
            if(served==NULL) printf("Empty");
            else printf("%d %s %d\n",served->id, served->name, served->priority);
            break;

            case 3: 
            display();
            break;

            case 4: 
            printf("EXITED\n");
            exit(1);
            break;

            default: 
            printf("Enter valid!\n");
        }
    }
}