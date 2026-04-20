#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int *pages = (int *)malloc(n * sizeof(int));

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int *frame = (int *)malloc(f * sizeof(int));
    int *recent = (int *)malloc(f * sizeof(int));  

    for (int i = 0; i < f; i++) {
        frame[i]  = -1;
        recent[i] = 0;
    }

    int faults = 0, hits = 0;

    for (int i = 0; i < n; i++) {

        // Check hit
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                // page in j frame was used at index i in string
                recent[j] = i; 
                hits++;
                break;
            }
        }

    if (!found) {
        int pos = -1;

        for (int j = 0; j < f; j++) {
            if (frame[j] == -1) {
                pos = j;
                break;
            }
        }

        if (pos == -1) {
            pos = 0;
            for (int j = 1; j < f; j++) {
                if (recent[j] < recent[pos]) {
                    pos = j;
                }
            }
        }

        frame[pos]  = pages[i];
        recent[pos] = i;
        faults++;
    }

    // Display
    printf("Page %d: ", pages[i]);
    for (int j = 0; j < f; j++)
        printf("%d ", frame[j]);
    printf("\n");
}

    printf("\nPage Faults = %d\n", faults);
    printf("Hit Ratio   = %.2f%%\n", (hits * 100.0) / n);

    free(pages);
    free(frame);
    free(recent);

    return 0;
}