#include <stdio.h>
#include <stdlib.h>

#define MAX 20
struct stack{
    char exp[MAX];
    int top;
} s;

void push(char c){
    if(s.top==MAX-1){
        printf("Overflow");
        return;
    }
    s.exp[++s.top]=c;
}

void pop_noreturn(){
    if(s.top==-1){
        printf("Empty");
    }
    else {
        s.top--;
    }
}

int check(char c1,char c2){
    return (c1=='(' && c2==')');
}

int balanced(char exp[]){
    int len = strlen(exp);
    for(int i=0; i<len; i++){
        if(exp[i]=='(' ){
            push(exp[i]);
        }
        else if (exp[i]==')'){
            if(s.top==-1) return 0;
            else if(check(s.exp[s.top],exp[i])){
                pop_noreturn();
            }
            else return 0;
        }
    }
    return s.top == -1;
}

/*
1. Closing first 
2. Empty () 
3. Opening unmatched left 
4. No brackets at all
*/

int duplicate(char exp[]){
    for(int i=0; i<strlen(exp); i++){
        if(exp[i]==')'){

            if(top==-1) return 1;

            //if(stack[s.top]=='(') return 1; redundant

            int inside = 0; 
            while(top!=-1 && stack[s.top]!='('){
                inside++;
                top--;
            }
            if(top!=-1){
                top--; // removes the (
            }
            if(inside<1) return 1;
        }
        else {
            stack[++top]=exp[i];
        }
    }

    while(top!=-1){  // if ) not encountered
        if(stack[top]=='(') return 1;
        top--;
    }
    return 0; // no brackets at all outer
}


//JUST DUPLICATE DETECTION - says )( is dup when its unbalanced
int pure_duplicate(char exp[]) {
    for(int i = 0; i < strlen(exp); i++) {
        if(exp[i] == ')') {
            
            int inside = 0;
            while(top != -1 && stack[top] != '(') {
                inside++;
                top--;
            }
            top--; 
            
            if(inside == 0) return 1; //() - dup
        }
        else {
            stack[++top] = exp[i];
        }
    }
    return 0;
}






int main(){
    s.top = -1;

}

/*
For every closing bracket, there should be a matching opening in stack
If closing and stack empty - FALSE 
Stack should be empty at the end
*/


#define MAX 30
char stack[MAX];
int top = -1; 

void push(char c){
    if(top==MAX-1){
        printf("Overflow");
        return;
    }
    stack[++top] = c;
}

char pop(){
    if(top==-1){
        printf("Underflow!");
        return '\0';
    }
    return stack[top--];
}

int isequal(char c, char stk){
    return (c=='(' && stk==')');
}

int isbalanced(char exp[]){
    for(int i=0; i<strlen(exp); i++){
        if(exp[i]=='('){
            push(exp[i]);
        }
        else if(exp[i]==')'){
            if(top==-1) return 0;
            if(isequal(stack[top],exp[i])){
                char s = pop();
            }
            else return 0;
        }
    }
    return top==-1;
}