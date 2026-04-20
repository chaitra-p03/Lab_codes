#include <stdio.h>
#include <stdlib.h>
/*-> we cant change where the pointer points but only the value at the pointer because in C everything is passed by a local copy
-> hence for tail, we need to change the pointer itself for which we need to send the address of tail which is received by a pointer to a pointer.
then changing the value of pointer to pointer means changing the address of tail which is what we need
*/
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node *create_node()
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
    return newnode;
}

Node *create(Node **tail)
{
    int n;
    printf("Enter the no of nodes: ");
    scanf("%d", &n);
    Node *head = NULL;
    Node *curr = NULL;
    *tail = NULL;
    for (int i = 0; i < n; i++)
    {
        Node *newnode = create_node();
        if (head == NULL)
        {
            head = newnode;
            curr = newnode;
            *tail = newnode;
        }
        else
        {
            newnode->prev = curr;
            curr->next = newnode;
            curr = newnode;
            *tail = newnode;
        }
    }

    return head;
}

void insert_rear(Node **ptr_head, Node **ptr_tail)
{
    Node *newnode = create_node();
    if (*ptr_head == NULL)
    {
        *ptr_head = newnode;
        *ptr_tail = newnode;
    }
    else
    {
        newnode->prev = *ptr_tail;
        (*ptr_tail)->next = newnode;
        *ptr_tail = newnode;
    }

    return;
}

void del_rear(Node **ptr_head, Node **ptr_tail)
{
    if (*ptr_head == NULL)
    {
        printf("Emtpy! Cannot delete\n");
        return;
    }
    else if ((*ptr_head)->next == NULL)
    {
        free(*ptr_tail);
        *ptr_head = NULL;
        *ptr_tail = NULL;
    }
    else
    {
        Node *temp = (*ptr_tail);
        (*ptr_tail) = (*ptr_tail)->prev;
        (*ptr_tail)->next = NULL;
        free(temp);
        temp = NULL;
    }
}

void insert_pos(Node **ptr_head, Node **ptr_tail, int pos)
{
    Node *newnode = create_node();
    Node *curr = *ptr_head;
    if (curr == NULL || pos == 1)
    {
        if (curr == NULL)
        {
            printf("Empty! Adding as first node\n");
            *ptr_head = newnode;
            *ptr_tail = newnode;
        }
        else
        {
            newnode->next = *ptr_head;
            (*ptr_head)->prev = newnode;
            *ptr_head = newnode;
        }
        return;
    }
    for (int i = 1; i < pos; i++)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        printf("Postion not found\n");
        free(newnode);
        newnode = NULL;
        return;
    }
    if (curr->next == NULL)
    {
        newnode->next = NULL;
        newnode->prev = curr;
        curr->next = newnode;
        *ptr_tail = newnode;
        return;
    }
    newnode->next = curr;
    newnode->prev = curr->prev;
    curr->prev->next = newnode;
    curr->prev = newnode;
    return;
}
void del_pos(Node **ptr_head, Node **ptr_tail, int pos)
{
    Node *curr = *ptr_head;
    if (curr == NULL)
    {
        printf("Empty! Cannot delete\n");
        return;
    }

    for (int i = 1; i < pos; i++)
    {
        curr = curr->next;
    }
        if (curr == NULL)
    {
        printf("Postion not found\n");
        return;
    }
    if(curr->prev ==NULL && curr->next==NULL){
        *ptr_head=NULL;
        *ptr_tail=NULL;
    }
    else if (curr->next == NULL)
    {
        Node *temp = *ptr_tail;
        *ptr_tail = curr->prev;
        (*ptr_tail)->next=NULL;
        free(temp);
        temp = NULL;
    }
    else if(curr->prev==NULL){
        *ptr_head = curr->next; 
        (*ptr_head)->prev=NULL;
    }
    else{
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    }
    free(curr);
    curr = NULL;
    return;
}

void insert_after(Node **head, Node **tail, int after)
{
    if(*head==NULL){
        printf("List is empty!\n");
        return;
    }
    Node *curr = *head;
    while (curr != NULL && curr->data != after)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        printf("Did not find element\n");
        return;
    }
    if (curr->next == NULL)
    {
        insert_rear(head,tail);
        return;
    }
    else
    {
            Node *newnode = create_node();
        newnode->next = curr->next;
        curr->next->prev = newnode;
        newnode->prev = curr;
        curr->next = newnode;
        return;
    }
}

void insert_before(Node **head, int before)
{
    Node *curr = *head;
    // empty list
    if (curr == NULL)
    {
        printf("List is empty\n");
        return;
    }
    Node *newnode = create_node();
    // before head
    if (curr->data == before)
    {
        newnode->next = *head; 
        (*head)->prev=newnode;
        *head = newnode;
        return;
    }
    // other pos 
    while (curr != NULL && curr->data != before)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        printf("Element not found\n");
        free(newnode);
        return;
    }
        newnode->next = curr;
        newnode->prev = curr->prev;
        curr->prev->next = newnode;
        curr->prev = newnode;
    
}

void traverse_forward(Node *head)
{
    if (head == NULL)
    {
        printf("Empty list!\n");
        return;
    }
    Node *curr = head;
    while (curr != NULL)
    {
        printf("%d--", curr->data);
        curr = curr->next;
    }
    printf("\n");
    return;
}

void traverse_backward(Node *tail)
{
    if (tail == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    Node *curr = tail;
    while (curr != NULL)
    {
        printf("%d--", curr->data);
        curr = curr->prev;
    }
    printf("\n");
    return;
}
int main()
{
    printf("1. To create a list\n"
           "2. Insert at rear end\n"
           "3. Delete from rear end\n"
           "4. Insert at pos\n"
           "5. Delete from pos\n"
           "6. Insert after\n"
           "7.Insert before\n"
           "8.Traverse forward\n"
           "9.Traverse backward\n");

    Node *head = NULL;
    Node *tail = NULL;

    int input = 0;
    do
    {
        printf("Enter input: ");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            head = create(&tail);
            break;
        case 8:
            traverse_forward(head);
            break;
        case 9:
            traverse_backward(tail);
            break;
        case 2:
            insert_rear(&head, &tail);
            break;
        case 3:
            del_rear(&head, &tail);
            break;
        case 4:
            printf("Enter pos to insert: ");
            int pos;
            scanf("%d", &pos);
            insert_pos(&head, &tail, pos);
            break;
        case 5:
            printf("Enter pos to delete: ");
            int dpos;
            scanf("%d", &dpos);
            del_pos(&head, &tail, dpos);
            break;
        case 6:
            printf("Enter after: ");
            int after;
            scanf("%d", &after);
            insert_after(&head, &tail, after);
            break;

        case 7:
            printf("Enter before: ");
            int before;
            scanf("%d", &before);
            insert_before(&head, &tail, before);
            break;

        default:
            printf("Enter valid number!");
        }

    } while (input != 0);
}