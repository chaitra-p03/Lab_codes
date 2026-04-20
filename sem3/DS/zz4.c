#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node{
    char name[20];
    struct Node* left; 
    struct Node* right;
}Node;

Node* dll = NULL;
void append(Node* newnode){
    // Create a copy for DLL (don't use BST nodes directly)
    Node* copy = (Node*)malloc(sizeof(Node));
    strcpy(copy->name, newnode->name);
    copy->left = NULL;
    copy->right = NULL;
    
    if(dll == NULL){
        dll = copy;
        return;
    }
    Node* temp = dll;
    while(temp->right != NULL){
        temp = temp->right;
    }
    temp->right = copy;
    copy->left = temp;
}

void display_dll(){
    if(dll == NULL){
        printf("No files viewed yet.\n");
        return;
    }
    printf("Recently viewed: ");
    Node* temp = dll; 
    while(temp != NULL){
        printf("%s ", temp->name);
        temp = temp->right;
    }
    printf("\n");
}


Node* getnode(){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory not allocated\n");
        exit(1);
    }
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
}

int is_file(char* name){
    return strstr(name, ".txt") != NULL;
}

Node* create_tree(Node* root, char input[]){
    if(root==NULL){
        Node* temp = getnode();
        strcpy(temp->name,input);
        return temp;
    }
    if(is_file(root->name)){
        printf("Error: File cannot have children!\n");
        return root;
    }

    if(strcmp(input,root->name)>0){
        root->right = create_tree(root->right, input);
    }
    else if(strcmp(input,root->name)<0){
        root->left = create_tree(root->left, input);
    }
}

void del_file(Node** root, char input[]){
    if(*root==NULL) return;
    // file doesnt have any children so leaf node
    Node* parent = NULL;
    Node* temp = (*root);
    while(temp!=NULL && strcmp(temp->name,input)!=0){
    parent = temp;
        if(strcmp(input,temp->name)<0){
        temp=temp->left;
    }
    else temp = temp->right;
}
if(temp==NULL){
    printf("Not found\n");
    return;
}
if(parent==NULL) {// del root
free(temp);
return;
} 
else if(parent->left==temp){
    parent->left=NULL;
}
else parent->right =NULL;
free(temp);
temp=NULL;
}




void view(Node* root, char input[]){
    if(root == NULL){
        printf("'%s' not found!\n", input);
        return;
    }
    
    int cmp = strcmp(input, root->name);
    
    if(cmp == 0){
        printf("Found: %s\n", input);
        append(root);  // Add to DLL
        return;
    }
    else if(cmp < 0){
        view(root->left,input);
    }
    else{
        view(root->right, input);
    }
}

// Display BST (inorder)
void display_bst(Node* root){
    if(root == NULL) return;
    display_bst(root->left);
    printf("%s ", root->name);
    display_bst(root->right);
}

int main(){
    Node* root = NULL;
    int choice;
    char input[20];
    
    
    while(1){
        printf("\n--- MENU ---\n");
        printf("1. Insert File (.txt)\n");
        printf("2. Insert Directory\n");
        printf("3. View/Search File or Directory\n");
        printf("4. Delete File\n");
        printf("5. Display BST (Inorder)\n");
        printf("6. Display Recently Viewed (DLL)\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                printf("Enter file name (with .txt): ");
                scanf("%s", input);
                if(!is_file(input)){
                    printf("Error: File must have .txt extension!\n");
                }
                else{
                    root = create_tree(root, input);
                }
                break;
                
            case 2:
                printf("Enter directory name: ");
                scanf("%s", input);
                if(is_file(input)){
                    printf("Error: Directory cannot have .txt extension!\n");
                }
                else{
                    root = create_tree(root, input);
                }
                break;
                
            case 3:
                printf("Enter name to search: ");
                scanf("%s", input);
                view(root, input);
                break;
                
            case 4:
                printf("Enter file name to delete: ");
                scanf("%s", input);
                del_file(&root, input);
                break;
                
            case 5:
                printf("BST (Alphabetical): ");
                display_bst(root);
                printf("\n");
                break;
                
            case 6:
                display_dll();
                break;
                
            case 7:
                printf("Exiting...\n");
                exit(0);
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}