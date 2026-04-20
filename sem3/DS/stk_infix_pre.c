#include <stdio.h>
#include <string.h>

#define MAX 50
char stack[MAX];
char prefix[MAX];
int top = -1;

void push(char c){
    if(top==MAX-1){
        printf("Overflow");
        return;
    }
    stack[++top]=c;
}
char pop(){
    if(top==-1){
        printf("Stack empty");
        return '\0';
    }
    return stack[top--];
}

int isoperator(char c){
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='^'){
        return 1;
    }
    return 0;
}

int isoperand(char c){
    if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9')){
        return 1; 
    }
    return 0;
}

int precedence(char c){
    if(c=='+' || c=='-') return 1; 
    else if (c=='*' || c=='/') return 2;
    else if (c=='^') return 3;
    return 0;
}

int higherorequalprecedence(char c1, char c2){
    int p1 = precedence(c1);
    int p2 = precedence(c2);
    if(p1==p2){
        if(c1=='^') return 1;
        return 0;
    }
    return (p1>p2);
}

void reverse_str(char exp[]){
    int n = strlen(exp);
    for(int i=0; i<n/2; i++){
        char s = exp[i];
        exp[i]=exp[n-i-1];
        exp[n-i-1] = s;
    }
    for(int i=0; i<n; i++){
        if(exp[i]=='(') exp[i]=')';
        else if(exp[i]==')') exp[i]='(';
    }
}

void convert(char exp[]){
    int j = 0;
    push('(');
    strcat(exp,")");
    reverse_str(exp);
    for(int i=0; i<strlen(exp); i++){
        if(exp[i]==' '){
            continue;
        }
        else if(isoperand(exp[i])){
            prefix[j++]=exp[i];
        }
        else if(exp[i]=='('){
    push(exp[i]);
}
        else if(isoperator(exp[i])){
            while(top!=-1 && higherorequalprecedence(stack[top],exp[i])){
                prefix[j++]=pop();
            }
            push(exp[i]);
        }
        else if(exp[i]==')'){
            while(top!=-1 && stack[top]!='('){
            prefix[j++]=pop();
            }
             if(top!=-1 && stack[top]=='('){
        pop(); 
        }
    } 
}
    while(top!=-1 && stack[top]!='('){
        prefix[j++]=pop();
    }
    prefix[j]='\0';
    reverse_str(prefix);
    printf("Prefix expression is %s",prefix);
}
int main(){
    char exp[50];
    printf("Enter expression: ");
    fgets(exp,MAX,stdin);
    exp[strcspn(exp,"\n")]='\0';
    convert(exp);
    return 0;
}