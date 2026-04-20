#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int n, m;

int Allocation[MAX][MAX], Max[MAX][MAX], Need[MAX][MAX];
int Available[MAX];

void calculateNeed() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}

bool isSafe() {
    int Work[MAX];
    bool Finish[MAX] = {false};
    for(int i = 0; i < m; i++)
        Work[i] = Available[i];

    while (1) {
        int found = -1;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) break;
                }
                // doesnt break -> satisfies
                if (j == m) {
                    found = i;
                    break;
                }
            }
        }
        if (found == -1)
            break;

        for (int k = 0; k < m; k++){
            Work[k] += Allocation[found][k];
            Finish[found] = true;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!Finish[i])
            return false;
    }

    return true;
}

bool requestResources(int pid, int request[]) {
    for(int i = 0; i < m; i++){
        if(request[i] > Need[pid][i])
            return false;
    }

    for(int i = 0; i < m; i++){
        if(request[i] > Available[i])
            return false;
    }

    // pretend allocation
    for(int i = 0; i < m; i++) {
        Available[i] -= request[i];
        Allocation[pid][i] += request[i];
        Need[pid][i] -= request[i];
    }

    if(isSafe()) return true;

    // rollback
    for(int i = 0; i < m; i++) {
        Available[i] += request[i];
        Allocation[pid][i] -= request[i];
        Need[pid][i] += request[i];
    }

    return false;
}

void printState() {
    printf("\nAllocation:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            printf("%d ", Allocation[i][j]);
        printf("\n");
    }

    printf("\nNeed:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            printf("%d ", Need[i][j]);
        printf("\n");
    }

    printf("\nAvailable:\n");
    for(int i = 0; i < m; i++)
        printf("%d ", Available[i]);
    printf("\n");
}

int main() {
    int total[MAX];

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

        for(int j = 0; j < m; j++) {
        int sum = 0;
        for(int i = 0; i < n; i++)
            sum += Allocation[i][j];
        Available[j] = total[j] - sum;
    }

    calculateNeed();

    printState();

    if(isSafe())
        printf("\nSystem is SAFE\n");
    else
        printf("\nSystem is NOT SAFE\n");

    int pid, request[MAX];

    printf("\nEnter process number for request: ");
    scanf("%d", &pid);

    printf("Enter request vector:\n");
    for(int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    if(requestResources(pid, request))
        printf("Request GRANTED\n");
    else
        printf("Request DENIED\n");

    printState();

    return 0;
}