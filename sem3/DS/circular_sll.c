// Operations on circular singly linked lists
#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* create_node(){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory Not allocated\n");
        exit(0);
    }
    printf("Enter data: ");
    scanf("%d",&newnode->data);
    newnode->next=NULL;
    return newnode;
}

void create_csll(Node** head, Node** tail){
    int n;
    printf("No of elements: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        Node* newnode = create_node();
        if(*head==NULL){
            *head=newnode;
            *tail=newnode;
        }
        else{
            (*tail)->next=newnode;
            *tail=newnode;
        }
    }
    // for the connection 
    (*tail)->next = *head;
}

// INSERTION AT BEGINNING
// more efficient - insert node after head and swap the data of old head and new head 
void insert_beg_head(Node**head){
    Node* newnode = create_node();
    
    // if empty list then new is the first node
    if(*head==NULL){
        *head=newnode;
        newnode->next=newnode;
        return;
    }
    else{
        Node * temp = *head;
        while(temp->next!=*head){
            temp=temp->next;
        }
            newnode->next=*head;
            temp->next=newnode;
            *head=newnode;
    }
}

void insert_beg_tail(Node** tail){
    Node* newnode = create_node();
    // if list is empty
    if(*tail==NULL){
        *tail=newnode;
        newnode->next=newnode;
        return;
    }
    else{
        newnode->next=(*tail)->next;
        (*tail)->next=newnode;
    }
}

// INSERTION AT END 
void insert_end_head(Node** head){
    Node * newnode = create_node();
    // is empty
    if(*head==NULL){
        *head=newnode;
        newnode->next=newnode;
        return;
    }
    else{
        Node* curr = *head;
        while(curr->next!=*head){
            curr=curr->next;
        }
        curr->next=newnode;
        newnode->next=*head;
    }
}

void insert_end_tail(Node** tail){
    Node* newnode = create_node();
    // is empty
    if(*tail==NULL){
        *tail=newnode;
        newnode->next=newnode;
        return;
    }
    else{
        Node* temp = (*tail)->next;
        (*tail)->next = newnode;
        newnode->next = temp;
        *tail= newnode;
    }
}

void display(Node* head){
    if(head==NULL){
        printf("List is empty");
        return;
    }
    Node* temp = head;
    if(temp->next==head){
        printf("Single element %d",head->data);
        return;
    }
    do{
        printf("%d--",temp->data);
        temp=temp->next;
    }
    while(temp!=head);
}

void delete_beg_head(Node** head){
    if(*head==NULL){
        printf("List is empty! Cannot delete");
        return;
    }
    Node* temp = *head;
    if(temp->next==*head){
        printf("Single element");
        *head=NULL;
        free(temp);
        temp=NULL;
        return;
    }
    Node * curr = *head;
    while(curr->next!=*head){
        curr=curr->next;
    }
    *head=(*head)->next;
    curr->next=*head;
    free(temp);
    temp=NULL;
}

void delete_beg_tail(Node **tail){
      if(*tail==NULL){
        printf("List is empty! Cannot delete");
        return;
    }
    Node * temp = (*tail)->next;
    if(temp==*tail){
        printf("Single element");
        *tail=NULL;
        free(temp);
        return;
    }   
    (*tail)->next = temp->next;
    printf("Deleted %d",temp->data);
    free(temp);
    temp=NULL;
}

void del_end_head(Node **head){
    if(*head==NULL){
        printf("Empty list! Cannot delete");
        return;
    }
    Node* temp = *head; 
    if(temp->next==*head){
        printf("Single elemenet");
        *head=NULL;
        free(temp);
        return;
    }
    while(temp->next->next!=*head){
        temp=temp->next;
    }
    Node * deleted = temp->next;
    temp->next=*head;
    free(deleted);
    deleted=NULL;
}

void del_end_tail(Node **tail){
    if(*tail==NULL){
        printf("Empty list cannot delete");
        return;
    }
    Node * temp = (*tail)->next;
    if(temp==*tail){
        printf("Single element");
        *tail =NULL;
        free(temp);
        temp=NULL;
        return;
    }
    while(temp->next!=*tail){
        temp=temp->next;
    }
    Node * deleted = *tail;
    temp->next=(*tail)->next;
    *tail = temp;
    free(deleted);
    deleted=NULL;
}

// insertion and deletion at specific position is the same as singly linked list,
// edge cases which a diff already implemented above


Node* reverse_sll_recursive(Node* head){
    if(head == NULL || head->next == NULL){
        return head;
    }
    
    Node* new_head = reverse_sll_recursive(head->next);
    head->next->next = head;
    head->next = NULL;
    
    return new_head;
}

int main(){
    int input=0;
    Node * head=NULL;
    Node * tail=NULL;
    printf("1. Create\n 2.Insert beg using head\n 3.Insert beg using tail\n 4.Insert end using head\n 5.Insert end using tail\n");
    printf("6. Display\n 7. del beg using head\n 8. del beg using tail\n 9. del end using head\n 10. del end using tail\n");
    printf("11.Head\n 12.Tail\n");
    do{
        printf("Enter input: ");
        scanf("%d",&input);
        switch(input){
            case 1: 
            create_csll(&head,&tail);
            break;
            case 2: 
            insert_beg_head(&head);
            break;
            case 3:
            insert_beg_tail(&tail);
            break; 
            case 4: 
            insert_end_head(&head);
            break;
            case 5:
            insert_end_tail(&tail); 
            break;
            case 6:
            display(head);
            break;
            case 7:
            delete_beg_head(&head);
            break;
            case 8:
            delete_beg_tail(&tail);
            break;
            case 9:
            del_end_head(&head);
            break;
            case 10:
            del_end_tail(&tail);
            break;
            case 11: 
            printf("Val at head %d",head->data);
            break;
            case 12: 
            printf("Val at tail %d",tail->data);
            break;
        }
    }while(input!=0);
}