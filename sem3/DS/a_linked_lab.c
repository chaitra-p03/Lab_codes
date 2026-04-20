#include <stdio.h>
#include <stdlib.h>
// Newnode - malloc
// functions that possibly can change head must return new head
// malloc must be paired with NULL 
// for deleting or not using that node store the reference then free it
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *create_list(int n)
{
    Node *head = NULL;
    Node *curr = NULL;
    for (int i = 0; i < n; i++)
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        if (newnode == NULL)
        {
            printf("Memory Not Allocated\n");
            exit(0);
        }
        int data;
        printf("Enter data: ");
        scanf("%d", &data);
        newnode->data = data;
        newnode->next = NULL;

        if (head == NULL)
        {
            head = newnode;
            curr = head;
        }
        else
        {
            curr->next = newnode;
            curr = newnode;
        }
    }
    return head;
}

Node *insert_before(Node *head, int toadd, int before)
{
    Node *curr = head;
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("Memory not allocated\n");
        return head;
    }
    newnode->data = toadd;
    // if head
    if (head->data == before)
    {
        newnode->next = head;
        return newnode;
    }
    Node *prev=NULL;
    while (curr != NULL)
    {
        if (curr->data == before)
        {
            prev->next = newnode;
            newnode->next = curr;
            return head;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Element not found in list\n");
    free(newnode);
    newnode = NULL;
    return head;
}

Node *insert_after(Node *head, int toadd, int after)
{
    Node *curr = head;
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("Memory Not allocated\n");
        return head;
    }
    newnode->data = toadd;
    while (curr != NULL)
    {
        if (curr->data == after)
        {
            newnode->next = curr->next;
            curr->next = newnode;
            return head;
        }
        curr = curr->next;
    }
    printf("Element not found in list\n");
    free(newnode);
    newnode = NULL;
    return head;
}

Node *delete_node(Node *head, int del)
{
    if (head->data == del)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    Node *curr = head->next;
    Node *prev = head;
    while (curr != NULL)
    {
        if (curr->data == del)
        {
            prev->next = curr->next;
            free(curr);
            return head;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Element not found in the list\n");
    return head;
}

void traverse(Node *head)
{
    Node *curr = head;
    while (curr != NULL)
    {
        printf("%d--", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

Node *reverse(Node *head)
{
    Node *prev = NULL;
    Node *curr = head;
    while (curr != NULL)
    {
        Node *after = curr->next;
        curr->next = prev;
        prev = curr;
        curr = after;
    }
    return prev;
}

// outer for loop is while(swap) - basically while not sorted
// inside everytime iterates through the whole thing 
// if any pass has no swaps needed, sorted hence swap remains 0 and breaks
Node *sort(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    int swap = 1;
    while (swap)
    {
        swap = 0;
        Node *curr = head;
        while (curr->next != NULL)
        {
            if (curr->data > curr->next->data)
            {
                int temp = curr->data;
                curr->data = curr->next->data;
                curr->next->data = temp;
                swap = 1;
            }
            curr = curr->next;
        }
    }
    return head;
}

Node *delete_alt(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    Node *curr = head;
    while (curr != NULL && curr->next != NULL)
    {
        Node *temp = curr->next;
        curr->next = curr->next->next;
        free(temp);
        curr = curr->next;
    }
    return head;
}

Node *insert_sorted(Node *head, int insert)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("Memory not allocated\n");
        exit(0);
    }
    newnode->data = insert;
    if (insert < head->data)
    {
        newnode->next = head;
        return newnode;
    }
    Node *curr = head;
    Node *prev = NULL;
    while (curr != NULL && curr->data < insert)
    {
        prev = curr;
        curr = curr->next;
    }
    prev->next = newnode;
    newnode->next = curr;

    return head;
}
int main()
{
    Node *head = NULL;
    int input = 0;
    do
    {
        printf("1. To create a linked list\n"
               "2. Insert an element before another specified\n"
               "3. Insert an element after another specified\n"
               "4. Delete a specified\n"
               "5. Traverse and Display\n"
               "6. Reverse\n"
               "7. Sort in ascending\n"
               "8. Delete Alternating Nodes\n"
               "9. Insert into sorted\n"
               "0. EXIT\n");

        scanf("%d", &input);
        switch (input)
        {
        case 1:;
            int n;
            printf("Enter no of nodes: ");
            scanf("%d", &n);
            head = create_list(n);
            break;

        case 2:
            printf("Enter the element to be added: ");
            int to_add;
            scanf("%d", &to_add);
            printf("Enter the element before which to be added: ");
            int before;
            scanf("%d", &before);
            head = insert_before(head, to_add, before);
            break;

        case 3:
            printf("Enter the element to be added: ");
            int new_add;
            scanf("%d", &new_add);
            printf("Enter the element after which to be added: ");
            int after;
            scanf("%d", &after);
            head = insert_after(head, new_add, after);
            break;

        case 4:
            printf("Enter element to be deleted: ");
            int del;
            scanf("%d", &del);
            head = delete_node(head, del);
            break;

        case 5:
            traverse(head);
            break;

        case 6:
            head = reverse(head);
            break;

        case 7:
            head = sort(head);
            break;

        case 8:
            head = delete_alt(head);
            break;

        case 9:
            printf("Enter element to insert into sorted: ");
            int insert;
            scanf("%d", &insert);
            head = insert_sorted(head, insert);
            break;

        default:
            printf("Enter valid number!");
        }
    } while (input != 0);
}