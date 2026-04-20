#include<stdio.h>
#include<string.h>

#define MAX 150
int top = -1;
char stack[MAX];
char post[MAX];

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
    return (c=='+' || c=='-' || c=='^' || c=='*' || c=='/');
}

int isoperand(char c){
    if((c>='a' && c<='z') || (c>'A' && c<'Z') || (c>='0' && c<='9')){
        return 1; 
    }
    return 0;
}

int precedence(char op){
   if(op=='+' || op=='-') return 1; 
   if (op=='*' || op=='/') return 2;
   if (op=='^') return 3;
   return 0;
}

int higherorequalprecedence(char c1, char c2){
    int p1=precedence(c1);
    int p2=precedence(c2);
    if(p1==p2){
        if(c1=='^') return 0; //associativity 
        else return 1;
    }
    return (p1>p2);
}

void convert(char exp[]){
    push('(');
    int i=0;
    int j=0;
    while(exp[i]!='\0'){
        if(exp[i]==' ') {
            i++;
            continue;
        }
        else if(exp[i]=='('){
            push(exp[i]);
        }
        else if(isoperand(exp[i])){
            post[j++]=exp[i];
        }
        else if(isoperator(exp[i])){
            while(top!=-1 && higherorequalprecedence(stack[top], exp[i])){
                post[j++]=pop();
            }
            push(exp[i]);
        }
        else if(exp[i]==')'){
            while(top!=-1 && stack[top]!='('){
                post[j++]=pop();
            }
            pop();
        }
        i++;
    }
 while(top!=-1 && stack[top]!='('){ 
      post[j++]=pop();
   }
    post[j]='\0';
    printf("Post fix expression %s\n", post);
}

int main(){
    char exp[50];
    printf("Enter expression: ");
    fgets(exp,MAX,stdin);
    exp[strcspn(exp,"\n")]='\0';
    strcat(exp,")");
    convert(exp);
    return 0;
}

/*
1. Create an empty stack and an empty postfix expression.

2. Scan the infix expression from left to right.

3. If the scanned character is an operand, add it to the postfix expression.

4. If the scanned character is an operator, then 
    
    a. If the stack is empty or the top of the stack is an opening parenthesis,
       push the operator onto the stack. 
    
    b. If the precedence of the operator is higher than the precedence of the 
       operator at the top of the stack, push the operator onto the stack. 
    
    c. If the precedence of the operator is lower than or equal to the 
       precedence of the operator at the top of the stack, pop the operator 
       from the stack and add it to the postfix expression. 
       
       Repeat this step until either the stack is empty or the operator at 
       the top of the stack has a lower precedence than the current operator. 
       Then push the current operator onto the stack.

5. If the scanned character is an opening parenthesis, push it onto the stack.

6. If the scanned character is a closing parenthesis, pop operators from the 
   stack and add them to the postfix expression until an opening parenthesis 
   is encountered. Discard the opening parenthesis.

7. Repeat steps 3–6 until the entire infix expression has been scanned.

8. Pop any remaining operators from the stack and add them to the postfix 
   expression.

9. Evaluate the postfix expression using a stack.

*/