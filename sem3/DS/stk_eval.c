#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 30
int stack[MAX];
int top = -1;

void push(int c){
    if(top==MAX-1){
        printf("Overflow");
        return;
    }
    stack[++top]=c;
}
int pop(){
    if(top==-1){
        printf("Stack empty");
        return 0;
    }
    return stack[top--];
}

int isoperator(char c){
    return (c=='+' || c=='-' || c=='^' || c=='*' || c=='/');
}

int isoperand(char c){
    if((c>='0' && c<='9')){
        return 1; 
    }
    return 0;
}

int eval_post(char post[]){
    int n = strlen(post);
    for(int i=0; i<n; i++){
        if(post[i]==' '){
            continue;
        }
        else if(isoperand(post[i])){
            push(post[i]-'0');
        }
        else if (isoperator(post[i])){
            int p2 = pop();
            int p1 = pop();
            int r = 0;
            switch(post[i]){
                case '+': 
                r = p1 + p2;
                break;
                case '-': 
                r = p1-p2;
                break;
                case '/' : 
                r = p1/p2;
                break;
                case '*' : 
                r = p1*p2;
                break;
                case '^' : 
                r = (int)pow(p1,p2);
                break;
            
            }
            push(r);
        }
    }
    return stack[top];
}

int eval_pre(char pref[]){
    int n = strlen(pref);
    for(int i=n-1; i>=0; i--){
        if(pref[i]==' '){
            continue;
        }
        else if(isoperand(pref[i])){
            push(pref[i]-'0');
        }
        else if (isoperator(pref[i])){
            int p1 = pop();
            int p2 = pop();
            int r = 0;
            switch(pref[i]){
                case '+': 
                r = p1 + p2;
                break;
                case '-': 
                r = p1-p2;
                break;
                case '/' : 
                r = p1/p2;
                break;
                case '*' : 
                r = p1*p2;
                break;
                case '^' : 
                r = (int)pow(p1,p2);
                break;
            
            }
            push(r);
        }
    }
    return stack[top];
}
