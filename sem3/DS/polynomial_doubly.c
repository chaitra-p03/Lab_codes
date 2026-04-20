#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int coeff;
    int exp;
    struct Node * next;
    struct Node * prev;
}Node;

Node* create_node(){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory not allocated\n");
        exit(0);
    }
    newnode->next=NULL;
    newnode->prev=NULL;
    newnode->coeff=0;
    newnode->exp=0;
    return newnode;
}

// make the polynomial list by attaching
void attach(Node** tail, int coeff, int exp){
    Node* newnode = create_node();
    newnode->coeff=coeff;
    newnode->exp=exp;

    (*tail)->next=newnode;
    newnode->prev=*tail;
    *tail = newnode;
}


#define compare(a,b) ((a<b ? -1 : (a==b ? 0 :1)))
Node* add(Node* poly1_head, Node*poly2_head, Node**tail){
    Node* curr1 = poly1_head->next;
    Node* curr2 = poly2_head->next;
    Node* result = create_node();
    *tail = result;

    while(curr1!=NULL && curr2!=NULL){
        int sum = 0;
        switch (compare(curr1->exp, curr2->exp))
        {
            case 1: 
            if(curr1->coeff!=0){
                attach(tail,curr1->coeff, curr1->exp);
            }
            curr1 = curr1->next;
            break;

            case 0:
            sum = curr1->coeff+curr2->coeff;
            if(sum!=0){
                attach(tail,sum,curr1->exp);
            }
            curr1=curr1->next;
            curr2=curr2->next;
            break;

            case -1: 
            if(curr2->coeff!=0){
                attach(tail,curr2->coeff,curr2->exp);
            }
            curr2=curr2->next;
            break;
    }
}
while(curr1!=NULL){
    if(curr1->coeff!=0){
        attach(tail, curr1->coeff, curr1->exp);
    }
    curr1=curr1->next;
}
while(curr2!=NULL){
    if(curr2->coeff!=0){
        attach(tail, curr2->coeff, curr2->exp);
    }
    curr2=curr2->next;
}

return result;
}

void display(Node* head){
    // empty res or empty poly case cause dummy node
    if(head==NULL || head->next==NULL){
        printf("Empty!");
        return;
    }
    Node * curr = head->next;
    while(curr!=NULL){
        printf("%dx^%d ",curr->coeff,curr->exp);
        curr=curr->next;
    }
}

// EVAL 
double evaluate(struct Polynomial* poly, double x) {
    double result = 0.0;
    struct Term* current = poly->head;
    
    while (current != NULL) {
        result += current->coefficient * pow(x, current->exponent);
        current = current->next;
    }
    
    return result;
}

int main(){
    Node* poly1_head = create_node(); 
    Node* poly2_head = create_node();
    Node* poly1_tail = poly1_head;
    Node* poly2_tail = poly2_head;

    Node* tail = NULL;
    Node * res = NULL;

    printf("1. To attach\n 2. To add\n 3. Display\n0. EXIT\n");
    int input;
    do{
        printf("Enter input: ");
        scanf("%d",&input);
        switch(input){
            case 1: 
            printf("Enter coefficient: ");
            int coeff;
            scanf("%d",&coeff);
            printf("Enter exp: ");
            int exp;
            scanf("%d",&exp);
            printf("Enter polynomial 1 or 2: ");
            int i; 
            scanf("%d",&i);
            if(i==1){
                attach(&poly1_tail, coeff,exp);
            }
            else if(i==2){
                attach(&poly2_tail,coeff,exp);
            }
            break;

            case 2: 
            res = add(poly1_head, poly2_head, &tail);
            break;

            case 3:
            display(poly1_head);
            printf("\n");
            display(poly2_head);
            printf("\n");
            display(res);
            break;

            case 0: 
            printf("Exiting!");
            break;

            default: 
            printf("Enter valid!");
        }
    }while(input!=0);
    return 0;
}