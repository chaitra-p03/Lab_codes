/*
Write a c program to store a long intger as a circular doubly linked list, where each node stores
one digit. Program should 
Read the no as a string an create a list one digit per node insert using last pointer
displat the odd digits in list
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}Node; 

Node* create_node(int data){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memo not allocated\n");
        exit(0);
    }
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

void create_dll(char str[], Node**last){
    for(int i=0; i<strlen(str); i++){
        char c = str[i];
        int digit = c-'0';

        Node* newnode = create_node(digit);
        if(*last==NULL){
            *last=newnode;
            newnode->next = newnode;
        }
        else{
            Node* temp = (*last)->next;
            (*last)->next = newnode;
            newnode->prev = *last;
            newnode->next = temp;
            temp->prev = newnode;
            *last = newnode;
        }
    }
}

void display(Node* last){
    if(last==NULL){
        return;
    }
    Node* temp = last;
    do{
        printf("%d ",temp->data);
        temp = temp->next;

    }while(temp!=last);
}

void display_odd(Node* last){
    if(last==NULL){
        return;
    }
    Node* temp = last;
    do{
        if(temp->data%2!=0){
            printf("%d ",temp->data);
        }
        temp = temp->next;

    }while(temp!=last);

}

int main(){
    char str[20];
    printf("ENTER: ");
    scanf("%s",str);
    Node* last = NULL;
    create_dll(str,&last);
    display(last);
    display_odd(last);
}