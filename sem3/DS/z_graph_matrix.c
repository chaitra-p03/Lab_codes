#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX 10

int graph[MAX_VERTEX][MAX_VERTEX];
int n = 0;

void initializeGraph(){
    for(int i=0; i<MAX_VERTEX; i++){
        for(int j=0; j<MAX_VERTEX; j++){
            graph[i][j] = 0;
        }
    }
}

void addEdge_undirected(int src, int dest){
    graph[src][dest] = 1;
    graph[dest][src] = 1; 
}

void addEdge_directed(int src, int dest){
    graph[src][dest] = 1; 
}

void displayGraph(){
    printf("\nAdjacency Matrix:\n");
    printf(" ");
    for(int i=0; i<n; i++){
        printf("%d ", i);
    }
    printf("\n");
    
    for(int i=0; i<n; i++){
        printf("%d ", i);
        for(int j=0; j<n; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main(){
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    initializeGraph();    
    int edges;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter 1 for undirected and 2 for directed: ");
    int input;
    scanf("%d", &input);
    
    printf("Enter each edge (source dest):\n");
    for(int i=0; i<edges; i++){
        int src, dest;
        scanf("%d %d", &src, &dest);
        if(input == 1){
            addEdge_undirected(src, dest);
        }
        else {
            addEdge_directed(src, dest);
        }
    }
    displayGraph();
    return 0;
}