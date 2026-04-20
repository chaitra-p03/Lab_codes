// Binary Search Tree 
// create and dispaly
// find and disaplay the second smallest no in BST
// delete the node with non empty left subtree and empty right subtree
// find the diff between the no of nodes of left and right subtree

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* left; 
    struct Node* right;
}Node; 

Node* getnode(){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory not allocated\n");
        exit(1);
    }
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

void create_tree(Node** root, int ele){
    if(*root==NULL){
        Node* newnode = getnode();          // before if would cause memory leak
        newnode->data = ele;
        (*root) = newnode;
        return;
    }
    if(ele<(*root)->data){
        create_tree(&(*root)->left,ele);
    }
    else create_tree(&(*root)->right,ele);
}

void display(Node* root){
    if(root==NULL) {
        return;
    }
    display(root->left);
    printf("%d ",root->data);
    display(root->right);
}

void secondsmallest(Node* root){
    if(root==NULL || root->left == NULL && root-> right == NULL) return; 
    Node* parent = NULL;
    Node* curr = root;
    while(curr->left!=NULL){
        parent = curr;
        curr=curr->left;
    }
    if(curr->right!=NULL) {
        curr = curr->right;
        while(curr->left!=NULL){
            curr=curr->left;
        }
        printf("Second smallest %d\n",curr->data);
        return;
    }
    printf("Second smallest %d\n", parent->data);
    return;
}

void delete(Node** root){
    if(*root==NULL || (*root)->left==NULL && (*root)->right==NULL){
        return;
    }
    // search for non empty left and empty right
    if((*root)->left!=NULL && (*root)->right==NULL){
        Node* temp = *root; 
        (*root) = (*root)->left;
        free(temp);
        temp=NULL;
    }
    delete(&(*root)->left);
    delete(&(*root)->right);
}

int number(Node* root){
    if(root==NULL) return 0;
    return 1 + number(root->left) + number (root->right);
}

int diff(Node* root){
    if(root==NULL) return 0;
    int d = 0;
    d = number(root->left) - number(root->right);
    return d;
}

int main(){
    Node* root = NULL;
    int n; 
    printf("Enter the no of nodes: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        int ele;
        printf("Enter element: ");
        scanf("%d",&ele);
        create_tree(&root,ele);
    }
    display(root);
    secondsmallest(root);
    delete(&root);
    display(root);
    printf("Count diff is %d", diff(root));
}