#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    char str[30];
    struct Node* next;
}Node;

void reverse(char str[]){
    int length = strlen(str);
    for(int i=0; i<length/2; i++){
        char temp = str[i];
        str[i]=str[length-i-1];
        str[length-i-1]=temp;
    }
}

void reverse_ll(Node* head){
    Node* curr = head;
    while(curr!=NULL){
        reverse(curr->str);
        curr = curr->next;
    }
}

void sort(Node* head){
    Node* curr = head;
    int swap = 1; 
    while(swap){
        swap = 0; 
        while(curr->next!=NULL){
            if(strcmp(curr->str, curr->next->str)>0){
                char temp[30];
                strcpy(temp,curr->str);
                strcpy(curr->str, curr->next->str);
                strcpy(curr->next->str, temp);

                swap = 1;
            }
            curr = curr->next;
        }
    }
}

void display(Node* head){
    Node* curr = head; 
    while(curr!=NULL){
        printf("%s ",curr->str);
        curr=curr->next;
    }
}

int main(){
    Node* head = (Node*)malloc(sizeof(Node));
    head->next = (Node*)malloc(sizeof(Node));  
    strcpy(head->str, "apple");
    strcpy(head->next->str, "banana");
    head->next->next = NULL;

    reverse_ll(head);
    display(head);
    sort(head);
    display(head);
}