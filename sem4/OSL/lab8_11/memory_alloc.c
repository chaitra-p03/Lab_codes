#include <stdio.h>

#define MAX 50

int main() {
    int nb, np, choice;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    int original[MAX];
    printf("Enter block sizes:\n");
    for (int i = 0; i < nb; i++)
        scanf("%d", &original[i]);

    printf("Enter number of processes: ");
    scanf("%d", &np);

    int process[MAX];
    printf("Enter process sizes:\n");
    for (int i = 0; i < np; i++)
        scanf("%d", &process[i]);

    while (1) {
        int block[MAX], allocation[MAX];

        for (int i = 0; i < nb; i++)
            block[i] = original[i];

        for (int i = 0; i < np; i++)
            allocation[i] = -1;

        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 4)
            break;

        if (choice == 1) {  // First Fit
        for (int i = 0; i < np; i++) {
            for (int j = 0; j < nb; j++) {
                if (block[j] >= process[i]) {
                    allocation[i] = j;
                    block[j] -= process[i];
                    break;
                }
            }
        }
    }

    else if (choice == 2) {  // Best Fit
        for (int i = 0; i < np; i++) {
            int best = -1;
            for (int j = 0; j < nb; j++) {
                if (block[j] >= process[i]) {
                    if (best == -1 || block[j] < block[best])
                        best = j;
                }
            }
            if (best != -1) {
                allocation[i] = best;
                block[best] -= process[i];
            }
        }
    }

    else if (choice == 3) {  // Worst Fit
        for (int i = 0; i < np; i++) {
            int worst = -1;
            for (int j = 0; j < nb; j++) {
                if (block[j] >= process[i]) {
                    if (worst == -1 || block[j] > block[worst])
                        worst = j;
                }
            }
            if (worst != -1) {
                allocation[i] = worst;
                block[worst] -= process[i];
            }
        }
    }

            else {
                printf("Invalid choice\n");
                break;
            }

        // Output
        printf("\nProcess\tSize\tBlock\n");
        for (int i = 0; i < np; i++) {
            if (allocation[i] != -1)
                printf("P%d\t%d\t%d\n", i, process[i], allocation[i]);
            else
                printf("P%d\t%d\tNot Allocated\n", i, process[i]);
        }
    }

    return 0;
}