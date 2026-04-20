#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
    int data;
    struct Node * next;
    struct Node * prev;
} Node;

Node* create_node()
{
    Node * newnode = (Node *)malloc(sizeof(Node));
    if(newnode==NULL)
    {
        printf("Memory not allocated\n");
        exit(0);
    }
    printf("Enter data: ");
    scanf("%d",&newnode->data);
    newnode->next=NULL;
    newnode->prev=NULL;
    return newnode;
}

Node * create_list(Node **tail)
{
    Node * head = NULL;
    Node * curr =NULL;
    int n;
    printf("Enter no of nodes: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        Node * newnode = create_node();
        if(head==NULL)
        {
            head=newnode;
            curr=newnode;
        }
        else
        {
            curr->next = newnode;
            newnode->prev=curr;
            curr=curr->next;
        }
    }
    *tail = curr;
    return head;
}

void insert_rear(Node** head, Node **tail)
{
// if list empty then first
    if(*head==NULL)
    {
        printf("List is empty! Adding as the first node\n");
        Node * newnode = create_node();
        * head = newnode;
        * tail = newnode;
    }
    else
    {
        Node * newnode = create_node();
        (*tail)->next = newnode;
        newnode->prev = (*tail);
        newnode->next = NULL;
        *tail = newnode;
    }
}

void del_rear(Node** head, Node** tail)
{
// no element
    if((*head)==NULL)
    {
        printf("List is empty! Cannot delete\n");
        return;
    }
// single element case
    if((*head)->next == NULL)
    {
        free(*head);
        *head = NULL;
        *tail =NULL;
        return;
    }
    else
    {
        Node* temp = (*tail);
        (*tail)=(*tail)->prev;
        (*tail)->next=NULL;
        free(temp);
        temp=NULL;
    }
}

void insert_pos(Node**head, Node**tail, int pos)
{
    Node * newnode = create_node();

// empty list
    if(*head==NULL)
    {
        printf("Empty list! Adding at pos 1\n");
        * head = * tail = newnode;
        return;
    }

// insertion at beginning
    if(pos == 1)
    {
        newnode->next = *head;
        (*head)->prev = newnode;
        * head = newnode;
        return;
    }
    Node * curr = * head;
    for(int i=1; i<pos-1 && curr!=NULL; i++)
    {
        curr=curr->next;
    }
    if(curr==NULL)
    {
        printf("Position does not exist!\n");
        return;
    }

// insertion at end
    if(curr == *tail)
    {
        curr->next = newnode;
        newnode->prev = curr;
        *tail = newnode;

    }
    else
    {
        newnode->next = curr->next;
        newnode->prev = curr;
        curr->next->prev = newnode;
        curr->next = newnode;
    }


    return;
}

void insert_before(Node** head, Node** tail, int val)
{

    Node*curr= *head;
    int pos = 1;
    while(curr!=NULL && curr->data!=val)
    {
        curr=curr->next;
        pos++;
    }
    if (curr == NULL)
    {
        printf("Value not found.\n");
        return;
    }
    insert_pos(head,tail,pos);
}
void insert_after(Node** head, Node** tail, int val)
{
    Node*curr= *head;
    int pos = 1;
    while(curr!=NULL && curr->data!=val)
    {
        curr=curr->next;
        pos++;
    }
    if (curr == NULL)
    {
        printf("Value not found.\n");
        return;
    }

    insert_pos(head,tail,pos+1);
}

void del_pos(Node** head, Node** tail)
{
    if(*head==NULL)
    {
        printf("Empty list! Cannot delete");
        return;
    }
    int pos;
    printf("Enter pos: ");
    scanf("%d",&pos);

    Node * curr = * head;
    for(int i=1; i<pos; i++)
    {
        curr=curr->next;
        if(curr==NULL)
        {
            printf("Pos does not exist");
            return;
        }
    }

    if(curr->prev!=NULL){
        curr->prev->next = curr->next;
    }
    else{
        // else single node case 
        * head = curr->next;
    }

    if(curr->next!=NULL){
        curr->next->prev = curr->prev;
    }
    else{
        *tail=curr->prev;
    }
    free(curr);
    curr=NULL;
}


void traverse_forward(Node* head)
{
    Node * curr = head;
    if(curr==NULL)
    {
        printf("Empty List!\n");
        return;
    }
    while(curr!=NULL)
    {
        printf("%d--",curr->data);
        curr=curr->next;
    }
    printf("\n");
}

void traverse_backward(Node * tail)
{
    Node * curr = tail;
    if(curr==NULL)
    {
        printf("Empty List!\n");
        return;
    }
    while(curr!=NULL)
    {
        printf("%d--",curr->data);
        curr=curr->prev;
    }
    printf("\n");
}


int main()
{
    printf("1. To create a list\n"
           "2. Insert at rear end\n"
           "3. Delete from rear end\n"
           "4. Insert at given pos\n"
           "5. Delete from given pos\n"
           "6. Insert after node\n"
           "7. Insert before node\n"
           "8. Traverse forward\n"
           "9. Traverse backward\n"
           "0. EXIT\n");
    int input=0;
    Node * head = NULL;
    Node * tail = NULL;
    do
    {
        printf("Enter input: ");
        scanf("%d",&input);
        switch(input)
        {
        case 1:
            head = create_list(&tail);
            break;
        case 2:
            insert_rear(&head, &tail);
            break;
        case 3:
            del_rear(&head, &tail);
            break;
        case 4:
            printf("Enter pos: ");
            int pos;
            scanf("%d",&pos);
            insert_pos(&head, &tail, pos);
            break;
        case 5:
            del_pos(&head, &tail);
            break;
        case 6:
            printf("Enter after which val to be inserted: ");
            int val;
            scanf("%d",&val);
            insert_after(&head,&tail,val);
            break;
        case 7:
            printf("Enter before which val to be inserted: ");
            int bval;
            scanf("%d",&bval);
            insert_before(&head,&tail,bval);
            break;
        case 8:
            traverse_forward(head);
            break;
        case 9:
            traverse_backward(tail);
            break;
        default:
            printf("Enter valid number!");
        }
    }
    while(input!=0);

}
