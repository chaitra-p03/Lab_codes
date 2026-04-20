#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node *create()
{
    int n;
    printf("Enter the no of nodes: ");
    scanf("%d", &n);
    Node *head = NULL;
    Node *curr = NULL;
    for (int i = 0; i < n; i++)
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        if (newnode == NULL)
        {
            printf("Memory not allocated\n");
            exit(0);
        }
        int data;
        printf("Enter data: ");
        scanf("%d", &data);
        newnode->data = data;
        newnode->next = NULL;
        newnode->prev = NULL;

        if (head == NULL)
        {
            head = newnode;
            curr = newnode;
        }
        else
        {
            newnode->prev = curr;
            curr->next = newnode;
            curr = newnode;
        }
    }
    return head;
}

Node *concat(Node *head1, Node *head2)
{

    if(head1==NULL){
        printf("List 1 empty\n");
        return head2;
    }
    if(head2==NULL){
        printf("List 2 empty\n");
        return head1;
    }
    Node *curr = head1;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = head2;
    head2->prev = curr;

    return head1;
}

void display(Node *head)
{
    Node *curr = head;
    while (curr != NULL)
    {
        printf("%d--", curr->data);
        curr=curr->next;
    }
}

int main()
{
    printf("Creating the first doubly linked list\n");
    Node *head1 = create();
    printf("Creating the second doubly linked list\n");
    Node *head2 = create();
    head1 = concat(head1, head2);
    display(head1);

    return 0;
}
