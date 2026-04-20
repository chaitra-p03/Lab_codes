#include<stdio.h>
#include<string.h>

typedef struct printer{
    int id;
    char name[30];
}printer;

#define MAX 20
printer queue[MAX];
int front=-1;
int rear=-1;

void enqueue(printer task){
    if(rear==MAX-1){
        printf("Queue full");
        return;
    }
    if(front==-1){
        front=0;
    }
    rear=rear+1;
    queue[rear]=task;
    printf("Added\n");
    return;
}

void dequeue(){
    if(front==-1){
        printf("Queue Empty");
        return;
    }
    if(front==rear){
        printf("Printing %d %s\n",queue[front].id, queue[front].name);
        front=rear=-1;
        return;
    }
    printf("Printing %d %s\n",queue[front].id, queue[front].name);
    front = front+1;
}

int main(){
    int n; 
    printf("Enter no of tasks: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        printer task;
        printf("Enter id and doc name: ");
        scanf("%d",&task.id);
        scanf("%s",task.name);
        enqueue(task);
    }
    for(int i=0; i<n; i++){
        dequeue();
    }
}