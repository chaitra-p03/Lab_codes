// Menu driven C program to represent the vande bharat
// city is a vertex and the train route is the edge
// vertices represent major cities DELHI (NDLS) and 10 more
// read the cities and routes and represent using adjacency list and display the list
// perform bfs starting from a given city and display the cities
// perform dfs similarly 
// display all directly connected cities for any input city

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    char station[10];
    struct Node* next;
}Node; 

Node* getnode(){
    Node* newnode = (Node*)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("Memory not allocated\n");
        exit(1);
    }
    newnode->next = NULL;
    return newnode;
}

#define MAX 11
Node* vertices[MAX];
int i = 0;

void add_vertex(char * station){
    Node* newnode = getnode();
    strcpy(newnode->station,station);
    vertices[i++] = newnode;
}


void addEdge(char* source, char* destination){
    int src_idx = find_index(source);
    int dest_idx = find_index(destination);
    
    if(src_idx == -1){
        printf("Source '%s' not found!\n", source);
        return;
    }
    if(dest_idx == -1){
        printf("Destination '%s' not found!\n", destination);
        return;
    }
    Node* newnode = getnode();
    strcpy(newnode->station, destination);
    Node* temp = vertices[src_idx];
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newnode;
    Node* newnode2 = getnode();
    strcpy(newnode2->station, source);
    
    temp = vertices[dest_idx];
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newnode2;
    
    printf("Route added: %s <-> %s\n", source, destination);
}

int find_index(char* input){
    for(int i=0; i<MAX; i++){
        if(strcmp(vertices[i]->station,input)==0){
            return i;
        }
    }
    return -1;
}

void display_list(){
    for(int i=0; i<MAX;i++){
        Node* temp = vertices[i];
        printf("Station %s : ",temp->station);
        temp=temp->next;
        while(temp!=NULL){
            printf("%s ",temp->station);
            temp=temp->next;
        }
    }
}

// Display directly connected cities
void display_connections(char* city){
    int idx = find_index(city);
    
    printf("\nDirect connections from %s: ", city);
    Node* temp = vertices[idx]->next;
    if(temp == NULL){
        printf("None\n");
        return;
    }
    
    while(temp != NULL){
        printf("%s", temp->station);
        if(temp->next != NULL) printf(", ");
        temp = temp->next;
    }
    printf("\n");
}

int visited[MAX];

void reset_visited(){
    for(int i = 0; i < MAX; i++){
        visited[i] = 0;
    }
}

void dfs_helper(int idx){
    visited[idx] = 1;
    printf("%s ", vertices[idx]->station);
    
    Node* temp = vertices[idx]->next;
    while(temp != NULL){
        int neighbor_idx = find_index(temp->station);
        if(neighbor_idx != -1 && !visited[neighbor_idx]){
            dfs_helper(neighbor_idx);
        }
        temp = temp->next;
    }
}

void dfs(char* city){
    int idx = find_index(city);
    reset_visited();
    printf("\nDFS starting from %s: ", city);
    dfs_helper(idx);
    printf("\n");
}

void bfs(char* city){
    int idx = find_index(city);
    reset_visited();
    
    int queue[MAX];
    int front = 0, rear = -1;
    
    queue[++rear] = idx;
    visited[idx] = 1;
    
    printf("\nBFS starting from %s: ", city);
    
    while(front <= rear){
        int curr_idx = queue[front++];
        printf("%s ", vertices[curr_idx]->station);
        
        Node* temp = vertices[curr_idx]->next;
        while(temp != NULL){
            int neighbor_idx = find_index(temp->station);
            if(neighbor_idx != -1 && !visited[neighbor_idx]){
                visited[neighbor_idx] = 1;
                queue[++rear] = neighbor_idx;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main(){
    int choice;
    char city1[20], city2[20];
    
    printf("=== VANDE BHARAT TRAIN ROUTE SYSTEM ===\n");
    
    // Pre-populate some cities
    add_vertex("NDLS");     // New Delhi
    add_vertex("LKO");      // Lucknow
    add_vertex("KNP");      // Kanpur
    add_vertex("AGC");      // Agra Cantt
    add_vertex("GWL");      // Gwalior
    add_vertex("JHS");      // Jhansi
    add_vertex("BPL");      // Bhopal
    add_vertex("UJN");      // Ujjain
    add_vertex("RTM");      // Ratlam
    add_vertex("BRC");      // Vadodara
    add_vertex("MMCT");     // Mumbai Central
    
    while(1){
        printf("1. Add City\n");
        printf("2. Add Route (Edge)\n");
        printf("3. Display Adjacency List\n");
        printf("4. Display Direct Connections\n");
        printf("5. BFS Traversal\n");
        printf("6. DFS Traversal\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                printf("Enter city code: ");
                scanf("%s", city1);
                add_vertex(city1);
                break;
                
            case 2:
                printf("Enter source city: ");
                scanf("%s", city1);
                printf("Enter destination city: ");
                scanf("%s", city2);
                addEdge(city1, city2);
                break;
                
            case 3:
                display_list();
                break;
                
            case 4:
                printf("Enter city: ");
                scanf("%s", city1);
                display_connections(city1);
                break;
                
            case 5:
                printf("Enter starting city: ");
                scanf("%s", city1);
                bfs(city1);
                break;
                
            case 6:
                printf("Enter starting city: ");
                scanf("%s", city1);
                dfs(city1);
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