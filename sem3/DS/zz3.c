// Spell Checker using BST
// read words into the BST and then print them in alphabetical order
// read a word from the user and check via the bst if its spelled correctly
// check if the entered word has siblings, if it exists, have its parent nodes middle letter capitalised

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

#define MAX 20

typedef struct Node{
    char data[MAX];
    struct Node* left; 
    struct Node* right;
}Node; 

Node* getnode(){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode == NULL){
        printf("Memory not allocated\n");
        exit(1);
    }
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

int alpha(char set1[], char set2[]){
    char * p =set1; 
    char *q = set2;
    while(*p&&*q && (*p)==(*q)){
        p++;
        q++;
    }
    return((*p)>(*q));
}

void create_bst(Node** root, char data[]){
    if(*root==NULL){
        Node* temp = getnode();
        strcpy(temp->data,data);
        *root=temp;
        return;
    }
    if(alpha(data,(*root)->data)){
        create_bst(&(*root)->right,data);
    }
    else {
        create_bst(&(*root)->left,data);
    }
}

void inorder(Node* root){
    if(root==NULL){
        return;
    }
    inorder(root->left);
    printf("%s ",root->data);
    inorder(root->right);
}


void checker(Node* root, char input[]){
    if(root == NULL){ 
        printf("NO\n");
        return;
    }

    if(strcmp(root->data,input)==0){
        printf("YES\n");
        return;
    }
    if(strcmp(root->data,input)>0){
        checker(root->left,input);
    }
    else if(strcmp(root->data,input)<0)
    checker(root->right,input);
}

void sibling(Node* root, char input[]){
    Node* parent = NULL;
    Node* temp = root;
    while(temp != NULL && strcmp(temp->data, input) != 0){
        parent = temp;
        if(strcmp(input, temp->data) < 0){ 
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    if(temp == NULL){
        printf("Word not found\n");
        return;
    }
    if(parent == NULL){
        printf("Root has no siblings\n");
        return;
    }
    if(parent->left != NULL && parent->right != NULL){
        int n = strlen(parent->data);
        if(parent->data[n/2] >= 'a' && parent->data[n/2] <= 'z'){
            parent->data[n/2] = parent->data[n/2] - 32;
        }
        printf("Has sibling. Parent: %s\n", parent->data);
    }
    else{
        printf("No sibling\n");
    }
}

int main() {
    Node* root = NULL;
    int n;
    char word[MAX];
    printf("Enter no of nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        create_bst(&root, word);
    }

    inorder(root);
    printf("\n");
    char input[MAX];
    printf("Enter to check: ");
    scanf("%s",input);
    checker(root,input);
    sibling(root,input);

    return 0;
}

