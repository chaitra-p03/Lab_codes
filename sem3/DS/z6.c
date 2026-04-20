/* add new in middle and delete first*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    char name[30];
    int reg; 
    char mail[30];
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
    scanf("%d",&newnode->reg);
    scanf("%s",newnode->mail);
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

void add_middle(Node*head, int n){
    if(head == NULL || head->next == NULL) return;
    Node* newnode = create_node();
    Node* slow = head;
    Node* fast = head;
    while(fast!=NULL && fast->next!=NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    newnode->next = slow;
    newnode->prev = slow->prev;
    slow->prev->next = newnode;
    slow->prev = newnode;
}

void delfirst(Node**head){
    if(*head == NULL){
        return;
    }
    else if((*head)->next==NULL){
        Node* temp = *head;
        *(head)=NULL;
        free(temp);
    }
    else{
        Node* temp = *head;
        (*head)=(*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

void search(Node* head, int data){
    Node* temp = head;
    do{
        if(temp->data==data){
            printf("Found");
            return;
        }
        temp=temp->next;
    }while(temp!=head);
}

void reverse(Node*head){
    Node* temp = head;
    
}