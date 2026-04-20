// single digits
// multi??

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
typedef struct Node{
    int val;
    struct Node* next;
}Node;

Node* stack = NULL;
Node* create_node(int c){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory Not Allocated\n");
        exit(1);
    } 
    newnode->val=c;
    newnode->next = NULL;
    return newnode;
}

void push(int c){
    Node* newnode = create_node(c);
    newnode->next=stack;
    stack = newnode;
}

int pop(){
    if(stack == NULL){
        printf("Empty!");
        return 0;
    }
  int c = stack->val;
  Node* temp = stack;
  stack = stack->next;
  free(temp);
  temp = NULL;
  return c;
}
int isoperator(char c){
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
}
int isoperand(char c){
    if (c>='0' && c<='9') return 1;
    return 0;
}

int evaluate(char post[]){
    int res = 0;
    for(int i=0; i<strlen(post); i++){
        if(isoperand(post[i])){
            push(post[i]-'0');
        }
        else if(isoperator(post[i])){
            int p1 = pop();
            int p2 = pop();
            switch(post[i]){
                case '+': res = p2+p1;
                break;
                case '-': res = p2-p1;
                break;
                case '*': res = p2*p1;
                break;
                case '/':res = p2/p1;
                break;
                case '^': res = (int)pow(p2,p1);
                break;
            }
            push(res);
        }
    }
    return pop();
    
}

int main(){
    char post[20];
    printf("Enter postfix expression: ");
    scanf("%s",post);
    int ans = evaluate(post);
    printf("Evaluated: %d",ans);
    return 0;
}