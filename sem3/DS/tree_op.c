#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int val;
    struct Node* left; 
    struct Node* right;
}Node;

#define MAX 30
Node* stack[MAX];
int top = -1; 

void push(Node* curr){
    if(top==MAX-1){
        printf("overflow");
        return;
    }
    stack[++top]=curr;
}

Node* pop(){
    if(top==-1){
        printf("empty");
        return NULL;
    }
    return stack[top--];
}

Node* peek(){
    if(top==-1){
        printf("empty");
        return NULL;
    }
    return stack[top];
}

Node* create_node(int val){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory not allocated\n");
        exit(-1);
    }
    newnode->val = val;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}


Node* creation(){
    int value;
    printf("Enter node value (-1 for null): ");
    scanf("%d",&value);
    if(value==-1){
        return NULL;
    }
    Node* newnode = create_node(value);
    printf("Entering the left child of %d: ",value);
    newnode->left = creation();
    printf("Entering the right child of %d: ",value);
    newnode->right = creation();

    return newnode;
}

void preorder(Node* head){
    if(head==NULL) return;
    top = -1;
    push(head);
    while(top!=-1){
        Node* curr = pop();
        printf("%d ",curr->val);
        if(curr->right!=NULL) push(curr->right);
        if(curr->left!=NULL) push(curr->left);
    }
    printf("\n");
}

void inorder(Node* head){
    if(head==NULL) return;
    top=-1;
    Node* curr = head;
    while(curr!=NULL || top>-1){
        while(curr!=NULL){
            push(curr);
            curr=curr->left;
        }
        curr = pop();
        printf("%d ",curr->val);
        curr = curr->right;
    }
    printf("\n");
}

void postorder(Node* head){
    if(head==NULL) return;
    top = -1;
    Node* prev = NULL;
    Node* curr = head;
    do{
        while(curr!=NULL){
            push(curr);
            curr=curr->left;
        }
        while(curr==NULL && top>-1){
            curr = peek();
            if(curr->right==NULL || curr->right==prev){
                top--;
                printf("%d ",curr->val);
                prev = curr;
                curr = NULL;
            }
            else curr = curr->right;
        }
    }while(top!=-1);
    printf("\n");
}

Node* find_parent(Node* root, int ele){
    if(root==NULL) return NULL;    
    if(root->val==ele) return NULL;
    
    if((root->left && root->left->val==ele) || (root->right && root->right->val==ele)){
        return root;
    }
    Node* leftresult = find_parent(root->left, ele);
    if(leftresult!=NULL) return leftresult;

    return find_parent(root->right,ele);
}

int depth(Node* head){
    if(head==NULL) return 0; 
    int l = depth(head->left);
    int r = depth(head->right);
    return(1 + (l>r ? l : r));
}

int find_ancestor(Node* head, int ele){
    if(head==NULL) return 0;
    
    if(head->val==ele) return 1;
    
    if(find_ancestor(head->left, ele) || find_ancestor(head->right, ele)){
        printf("%d ", head->val);
        return 1;
    }
    
    return 0;
}

void print_ancestors(Node* head, int ele){
    printf("Ancestors of %d: ", ele);
    if(!find_ancestor(head, ele)){
        printf("Element not found in tree");
    }
    printf("\n");
}


int leaf_node(Node* head){
    if(head==NULL) return 0; 
    if(head->left==NULL && head->right==NULL) return 1;
    return (leaf_node(head->left)+leaf_node(head->right)); 
}

void display_menu(){
    printf("1. Create Tree\n");
    printf("2. Preorder Traversal\n");
    printf("3. Inorder Traversal\n");
    printf("4. Postorder Traversal\n");
    printf("5. Find Parent of Node\n");
    printf("6. Find Depth/Height of Tree\n");
    printf("7. Find Ancestors of Node\n");
    printf("8. Count Leaf Nodes\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

int main(){
    Node* root = NULL;
    int choice, value, count;
    Node* parent;
    
    while(1){
        display_menu();
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Creating Binary Tree\n");
                root = creation();
                break;
                
            case 2:
                printf("Preorder Traversal: ");
                preorder(root);
                break;
                
            case 3:
                printf("Inorder Traversal: ");
                inorder(root);
                break;
                
            case 4:
                printf("Postorder Traversal: ");
                postorder(root);
                break;
                
            case 5:
                printf("Enter the node value to find its parent: ");
                scanf("%d", &value);
                parent = find_parent(root, value);
                if(parent==NULL){
                    printf("Either node is root or node not found in tree\n");
                }
                else{
                    printf("Parent of %d is: %d\n", value, parent->val);
                }
                break;
                
            case 6:
                if(root==NULL){
                    printf("Tree is empty! Depth is 0\n");
                }
                else{
                    printf("Depth of tree: %d\n", depth(root));
                }
                break;
                
            case 7:
                if(root==NULL){
                    printf("Tree is empty! Create a tree first.\n");
                    break;
                }
                printf("Enter the node value to find its ancestors: ");
                scanf("%d", &value);
                print_ancestors(root, value);
                break;
                
            case 8:
                if(root==NULL){
                    printf("Tree is empty! Leaf count is 0\n");
                }
                else{
                    count = leaf_node(root);
                    printf("Number of leaf nodes: %d\n", count);
                }
                break;
                
            case 9:
                printf("Exiting!\n");
                exit(0);
                
            default:
                printf("Invalid.\n");
        }
    }
    
    return 0;
}