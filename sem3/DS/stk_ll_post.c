#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node{
    char val;
    struct Node* next;
}Node;

Node* op = NULL;
Node* create_node(char c){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory Not Allocated\n");
        exit(1);
    } 
    newnode->val=c;
    newnode->next = NULL;
    return newnode;
}

void push_op(char c){
    Node* newnode = create_node(c);
    newnode->next=op;
    op = newnode;
}

char pop_op(){
    if(op == NULL){
        return '\0';
    }
  char c = op->val;
  Node* temp = op;
  op = op->next;
  free(temp);
  temp = NULL;
  return c;
}

int isoperator(char c){
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
}
int isoperand(char c){
    if(c>='A'&&c<='Z') return 1; 
    else if (c>='0' && c<='9') return 1;
    else if (c>='a' && c<='z') return 1;
    return 0;
}

int precedence(char c){
    if(c=='+' || c=='-') return 1;
    else if (c=='*' || c=='/') return 2;
    else if(c=='^') return 3;
    else return 0;
}

int isgreaterorequal(char c1, char c2){
    int n1 = precedence(c1);
    int n2 = precedence(c2);
    if(n1==n2){
        if(c1=='^') return 0;
        else return 1;
    }
    return (n1>n2);
}

void convert(char infix[], char postfix[]){
     int i = 0, j = 0;
    int len = strlen(infix);
    
    while(i < len){
        char current = infix[i];
        
        if(isoperand(current)){
            postfix[j++] = current;
        }
        else if(current == '('){
            push_op(current);
        }
        else if(current == ')'){
            while(op != NULL && op->val != '('){
                postfix[j++] = pop_op();
            }
            if(op != NULL){
                pop_op();
            }
        }
        else if(isoperator(current)){
            while(op != NULL && op->val != '(' && isgreaterorequal(op->val, current)){
                postfix[j++] = pop_op();
            }
            push_op(current);
        }
        i++;
    }
    
    while(op != NULL){
        postfix[j++] = pop_op();
    }
    
    postfix[j] = '\0';
}

int main(){
    char infix[100];
    char postfix[100];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    convert(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;

}