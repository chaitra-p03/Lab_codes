#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX 10

int n, m;
int Allocation[MAX][MAX], Max[MAX][MAX], Need[MAX][MAX];
int Available[MAX];

pthread_mutex_t lock;

// Calculate Need
void calculateNeed() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}

// Safety Algorithm
bool isSafe() {
    int Work[MAX];
    bool Finish[MAX] = {false};

    for(int i = 0; i < m; i++)
        Work[i] = Available[i];

    while(1) {
        int found = -1;

        for(int i = 0; i < n; i++) {
            if(!Finish[i]) {
                int j;
                for(j = 0; j < m; j++)
                    if(Need[i][j] > Work[j])
                        break;

                if(j == m) {
                    found = i;
                    break;
                }
            }
        }

        if(found == -1)
            break;

        for(int k = 0; k < m; k++)
            Work[k] += Allocation[found][k];

        Finish[found] = true;
    }

    for(int i = 0; i < n; i++)
        if(!Finish[i])
            return false;

    return true;
}

// Request resources
bool requestResources(int pid, int req[]) {
    for(int i = 0; i < m; i++)
        if(req[i] > Need[pid][i])
            return false;

    for(int i = 0; i < m; i++)
        if(req[i] > Available[i])
            return false;

    // Pretend allocation
    for(int i = 0; i < m; i++) {
        Available[i] -= req[i];
        Allocation[pid][i] += req[i];
        Need[pid][i] -= req[i];
    }

    if(isSafe())
        return true;

    // Rollback
    for(int i = 0; i < m; i++) {
        Available[i] += req[i];
        Allocation[pid][i] -= req[i];
        Need[pid][i] += req[i];
    }

    return false;
}

// Release resources
void releaseResources(int pid) {
    for(int i = 0; i < m; i++) {
        Available[i] += Allocation[pid][i];
        Allocation[pid][i] = 0;
        Need[pid][i] = 0;
    }
}

// Thread function
void* process(void* arg) {
    int pid = *(int*)arg;
    int req[MAX];

    // Take request input
    pthread_mutex_lock(&lock);

    printf("\nEnter request for P%d:\n", pid);
    for(int i = 0; i < m; i++)
        scanf("%d", &req[i]);

    if(requestResources(pid, req)) {
        printf("P%d request GRANTED\n", pid);
    } else {
        printf("P%d request DENIED\n", pid);
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    pthread_mutex_unlock(&lock);

    sleep(1); // simulate execution

    pthread_mutex_lock(&lock);
    printf("P%d releasing resources\n", pid);
    releaseResources(pid);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t threads[MAX];
    int ids[MAX];
    int total[MAX];

    pthread_mutex_init(&lock, NULL);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("Enter Max matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);

    printf("Enter total resources:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &total[i]);

    // Compute Available
    for(int j = 0; j < m; j++) {
        int sum = 0;
        for(int i = 0; i < n; i++)
            sum += Allocation[i][j];
        Available[j] = total[j] - sum;
    }

    calculateNeed();

    // Create threads
    for(int i = 0; i < n; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, process, &ids[i]);
    }

    for(int i = 0; i < n; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}