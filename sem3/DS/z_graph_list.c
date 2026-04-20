#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int vertex;
    struct Node* next;
}Node;

#define MAX_VERTEX 10
Node* graph[MAX_VERTEX];
int n = 0; 

Node* create_node(int x){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory not allocated\n");
        exit(-1);
    }
    newnode->vertex = x;
    newnode->next = NULL;
    return newnode;
}

void addEdge_undirected(int src, int dest){
    Node* newnode = create_node(dest);
    newnode->next = graph[src];
    graph[src]=newnode;

    newnode = create_node(src);
    newnode->next = graph[dest];
    graph[dest]=newnode;
}
void addEdge_directed(int src, int dest){
    Node* newnode = create_node(dest);
    newnode->next = graph[src];
    graph[src]=newnode;
}
void displayGraph(){
    for(int i=0; i<n; i++){
        Node* temp = graph[i];
        printf("Vertex %d: ", i);
        while(temp){
            printf("%d->",temp->vertex);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}

int countEdges(int directed,int undirected){
    int count = 0; 
    for(int i=0; i<n; i++){
        Node* temp = graph[i];
        while(temp){
            count++;
            temp=temp->next;
        }
    }
    if(undirected){      // one edge appears twice
        count=count/2;
    }
    return count;
}

// max for directed is n n-1
// undirected is n n-1 / 2
// min is n-1


int main(){
    printf("Enter number of vertices: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        graph[i]=NULL;
    }
    int edges;
    printf("Enter the number of edges: ");
    scanf("%d",&edges);
    printf("Enter 1 for undirected and 2 for directed: ");
    int input;
    scanf("%d",&input);
    printf("Enter each edge (source dest) ");
    for(int i=0; i<edges;i++){
        int src, dest;
        scanf("%d %d",&src,&dest);
        if(input==1){
        addEdge_undirected(src,dest);
        }
        else addEdge_directed(src,dest);
    }
    printf("Adjacency list rep\n");
    displayGraph();
    return 0;
}


