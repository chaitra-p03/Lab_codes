#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int vertex;
    struct Node* next;
}Node;

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

void dfs(int v){
    visited[v]=TRUE;
    printf("%d ",v);
    for(Node* w = graph[v]; w; w=w->next){
        if(!visited[w->vertex]){
            dfs(w->vertex);
        }
    }
} 

void dfs_iterative(int start) {
    int stack[MAX_VERTEX];
    int top = -1;

    for (int i = 0; i < n; i++)
        visited[i] = FALSE;

    stack[++top] = start;


    while (top != -1) {
        int v = stack[top--];

        if (!visited[v]) {
            visited[v] = TRUE;
            printf("%d ", v);

            Node* temp = graph[v];
            while (temp) {
                if (!visited[temp->vertex])
                    stack[++top] = temp->vertex;
                temp = temp->next;
            }
        }
    }
    printf("\n");
}


int main(){
    printf("Enter no of vertices: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        graph[i]=NULL;
        visited[i]=FALSE;
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
    printf("DFS: \n");
    for (int i=0; i<n; i++) {
      if (!visited[i]) {
            dfs(i);
            printf("\n");
        }
    }
}
