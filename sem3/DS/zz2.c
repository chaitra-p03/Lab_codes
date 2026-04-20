// iterative create bt 
// display bt in tree form 
// iterative pre order
// delete a node with less than degree 2 
// display all non leaf nodes

#include<stdio.h>
#include<stdlib.h>

#define MAX 20

typedef struct Node{
    int data;
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

void create_tree(Node** root, int ele){
    Node* newnode = getnode();
    newnode->data = ele;
    if(*root == NULL){
        *root = newnode;
        return;
    }
    
    Node* queue[MAX];
    int front = 0, rear = -1;
    queue[++rear] = *root;
    
    while(front <= rear){
        Node* temp = queue[front++];
        
        if(temp->left == NULL){
            temp->left = newnode;
            return;
        }
        else{
            queue[++rear] = temp->left;
        }
        
        if(temp->right == NULL){
            temp->right = newnode;
            return;
        }
        else{
            queue[++rear] = temp->right;
        }
    }
}

void display_tree(Node* root){
    if(root == NULL){
        printf("Tree is empty\n");
        return;
    }
    
    Node* queue[MAX];
    int front = 0;
    int rear = -1;
    queue[++rear] = root;
    
    int level = 1;
    while(front <= rear){
        int size = rear - front + 1;
        printf("Level %d: ", level++);
        
        for(int i = 0; i < size; i++){
            Node* temp = queue[front++];
            printf("%d ", temp->data);
            if(temp->left != NULL) queue[++rear] = temp->left;
            if(temp->right != NULL) queue[++rear] = temp->right;
        }
        printf("\n");
    }
}

void preorder(Node* root){
    if(root == NULL){
        printf("Tree is empty\n");
        return;
    }
    
    Node* stack[MAX];
    int top = -1;
    stack[++top] = root;
    
    while(top != -1){
        Node* temp = stack[top--];
        printf("%d ", temp->data);
        if(temp->right != NULL) stack[++top] = temp->right;
        if(temp->left != NULL) stack[++top] = temp->left;
    }
    printf("\n");
}

int degree(Node* node){
    if(node == NULL) return -1;
    if(node->left == NULL && node->right == NULL) return 0;
    else if(node->left != NULL && node->right != NULL) return 2;
    else return 1;
}

void delete_nodes(Node** root){
    if(*root == NULL){
        return;
    }
    
    delete_nodes(&(*root)->left);
    delete_nodes(&(*root)->right);

    int d = degree(*root);

    if(d == 0){ 
        printf("Deleted\n");
        free(*root);      
        (*root) = NULL;
    }
    else if(d == 1){ 
        printf("Deleted\n");
        Node* temp = (*root);
        if(temp->left != NULL){
            (*root) = temp->left;
        }
        else{  
            (*root) = temp->right;
        }
        free(temp);
    }
}

void displaynonleaf(Node* root){
    if(root == NULL) return;
    
    if(root->left != NULL || root->right != NULL){
        printf("%d ", root->data);
    }
    
    displaynonleaf(root->left);
    displaynonleaf(root->right);
}

int main(){
    Node* root = NULL;
    int n; 
    
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        int ele;
        printf("Enter element %d: ", i+1);
        scanf("%d", &ele);
        create_tree(&root, ele);
    }
    
    display_tree(root);
    preorder(root);
    displaynonleaf(root);
    printf("\n");
    delete_nodes(&root);
    display_tree(root);
    
    return 0;
}
