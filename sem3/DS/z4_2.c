#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    char str[30];
    struct Node* next;
}Node;



Node* create_node(char str[]){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("mem not\n");
        exit(0);
    }
    strcpy(newnode->str, str);
    newnode->next = NULL;

    return newnode;
}

Node* create_route(){
    Node * head = NULL;
    Node * curr = NULL;
    int n;
    printf("Enter n: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        char str[30];
        scanf("%s",str);
    Node * newnode = create_node(str);
    if(head==NULL){
        head = newnode;
        curr = newnode;
    }
    else {
        curr->next = newnode; 
        curr = newnode;
    }
}

    return head;
}

void insert_before(Node** head, char before[], char stop[]){
    Node * newnode = create_node(stop);
    if(strcmp((*head)->str,before)==0){
        // add at head
        newnode->next = *head;
        *head = newnode;
        return;
    }
    Node * curr = *head; 
    Node * prev = NULL;
    while(curr!=NULL){
        if(strcmp(curr->str,before)==0){
            prev->next = newnode;
            newnode->next = curr;
            return;
        }
        prev = curr;
        curr = curr->next;
   }
   printf("Not found")
}

void display();
