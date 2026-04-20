#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int n, m;
int Allocation[MAX][MAX], Request[MAX][MAX];
int Available[MAX];

bool detectDeadlock() {
    int Work[MAX];
    bool Finish[MAX];

    for (int i = 0; i < m; i++)
        Work[i] = Available[i];

    for (int i = 0; i < n; i++) {
        Finish[i] = true;  

        for (int j = 0; j < m; j++) {
            if (Allocation[i][j] != 0) {
                Finish[i] = false;  
                break;
            }
        }
    }
    

    while (1) {
        int found = -1;

        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (Request[i][j] > Work[j])
                        break;
                }

                if (j == m) {
                    found = i;
                    break;
                }
            }
        }

        if (found == -1)
            break;

        for (int k = 0; k < m; k++)
            Work[k] += Allocation[found][k];

        Finish[found] = true;
    }

    bool deadlock = false;

    printf("\nDeadlocked processes: ");
    for (int i = 0; i < n; i++) {
        if (!Finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if (!deadlock)
        printf("None");

    return deadlock; 
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("Enter Request matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Request[i][j]);

    printf("Enter Available vector:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &Available[i]);

    if (detectDeadlock())
        printf("\n\nSystem is in DEADLOCK\n");
    else
        printf("\n\nSystem is NOT in deadlock (safe)\n");

    // Part (b): extra request
    int r;
    printf("\nEnter additional request of P2 (resource index): ");
    scanf("%d", &r);

    Request[2][r] += 1;

    printf("\nAfter P2 additional request:\n");

    if (detectDeadlock())
        printf("\nSystem enters DEADLOCK\n");
    else
        printf("\nSystem is still NOT in deadlock\n");

    return 0;
}