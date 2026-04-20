#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    int height;
    struct Node* leftchild; 
    struct Node* rightchild;
}Node;

#define MAX(a,b) ((a)>(b) ? (a) : (b))

int height(Node *node){
    return node==NULL ? -1 : node->height;
}

// Left Left - perform RR rotation
void rotateRight(Node** node){
    Node* child = (*node)->leftchild;
    (*node)->leftchild = child->rightchild;
    child->rightchild = (*node);
    (*node)->height = MAX(height((*node)->rightchild), height((*node)->leftchild)) + 1;
    child->height = MAX(height(child->leftchild), height(child->rightchild)) + 1; 
    (*node)=child;
}

// Right Right - perform LL rotation
void rotateLeft(Node** node){
    Node* child = (*node)->rightchild;
    (*node)->rightchild = child->leftchild;
    child->leftchild = (*node);
    (*node)->height = MAX(height((*node)->rightchild), height((*node)->leftchild)) + 1;
    child->height = MAX(height(child->rightchild), height(child->leftchild)) + 1;
    (*node) = child;
}

void doublerotateLeftRight(Node** node){
    rotateLeft(&(*node)->leftchild);
    rotateRight(node);
}

void doublerotateRightLeft(Node** node){
    rotateRight(&(*node)->rightchild);
    rotateLeft(node);
}

void insert(int x, Node** root){
    if(*root==NULL){
        *root = (Node*)malloc(sizeof(Node));
        (*root)->data = x;
        (*root)->leftchild = (*root)->rightchild = NULL;
        (*root)->height = 0;
    }
    else if (x<(*(root))->data){
        insert(x,&(*root)->leftchild);
        if(height((*root)->leftchild) - height((*root)->rightchild)==2){
            if(x<(*root)->leftchild->data){
                rotateRight(root);
            }
            else doublerotateLeftRight(root);
        }
    }
    else if(x>(*root)->data){
        insert(x,&(*root)->rightchild);
        if(height((*root)->leftchild) - height((*root)->rightchild)==-2){
            if(x>(*root)->rightchild->data){
                rotateLeft(root);
            }
            else doublerotateRightLeft(root);
        }
    }
    (*root)->height = MAX(height((*root)->rightchild), height((*root)->leftchild)) + 1;
}

void inorder(Node* node){
    if(node!=NULL){
        inorder(node->leftchild);
        printf("%d ", node->data);
        inorder(node->rightchild);
    }
}

int main(){
    Node* Tree = NULL;
    int input = 1; 
    while(input){
        printf("\n1.Insert element\n 2.Inorder check\n 3.Exit\n");
        int data;
        scanf("%d",&data);
        switch (data)
        {
        case 1: 
            printf("Enter data ");
            int x; 
            scanf("%d",&x);
            insert(x,&Tree);
            break;
        case 2:
            inorder(Tree);
            printf("\n");
            break;
        case 3: 
            exit(1);
        default:
            printf("Enter valid");
            break;
        }
    }
}