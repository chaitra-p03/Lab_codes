#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int vertex;
    struct Node* next;
}Node;

typedef struct queue{
    int vertex;
    struct queue* link;
}queueNode;

typedef struct queue* queue_pointer;

#define MAX_VERTEX 10
#define FALSE 0
#define TRUE 1
int n = 0;
Node* graph[MAX_VERTEX];
int visited[MAX_VERTEX];

Node* create_node(int x){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory not allocated\n");
        exit(-1);
    }
    newnode->vertex=x;
    newnode->next=NULL;
    return newnode;
}

void addEdge(int src, int dest){
    Node* newnode = create_node(dest);
    newnode->next = graph[src];
    graph[src] = newnode;
    // undirected graphs
    newnode = create_node(src);
    newnode->next = graph[dest];
    graph[dest] = newnode;
}

void display_graph(){
    for(int i=0; i<n; i++){
        Node* temp = graph[i];
        printf("Vertex %d: ",i);
        while(temp){
            printf("%d->",temp->vertex);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}

void addq(queue_pointer* front, queue_pointer* rear, int vertex){
    queue_pointer temp = (queue_pointer)malloc(sizeof(queueNode));
    temp->vertex = vertex;
    temp-> link = NULL;
    if(*rear!=NULL){
        (*rear)->link=temp;
        *rear = temp;
    }
    else{
        *front = temp;
        *rear = temp;
    }
}

int delq(queue_pointer* front, queue_pointer* rear){
    queue_pointer temp = *front;
    int item;
    if(temp==NULL){
        return -1;
    }
    item = temp->vertex;
    *front = temp->link;
    if(*front == NULL){
        *rear = NULL;
    }
    free(temp);
    return item;
}

void bfs(int v){
    queue_pointer front = NULL;
    queue_pointer rear = NULL; 
    printf("%d ",v);
    visited[v]=TRUE;
    addq(&front,&rear,v);
    while(front){
        v = delq(&front,&rear);
        for(Node* w = graph[v]; w; w=w->next){
            if(!visited[w->vertex]){
                printf("%d ",w->vertex);
                visited[w->vertex] = TRUE;
                addq(&front, &rear, w->vertex);
            }
        }
    }
}

int main(){
    printf("Enter no of vertices: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        graph[i]=NULL;
    }
    int edges;
    printf("Enter the number of edges: ");
    scanf("%d",&edges);
    printf("Enter each edge (source dest) ");
    for(int i=0; i<edges;i++){
        int src, dest;
        scanf("%d %d",&src,&dest);
        addEdge(src,dest);
    }
    display_graph();
    printf("BFS: \n");
    for (int i=0; i<n; i++) {
      if (!visited[i]) {
            bfs(i);
        }
    }
}