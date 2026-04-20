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

    for (int i = 0; i < f; i++)
        frame[i] = -1;

    int index = 0, faults = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page already in frame
        for (int j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        // move by index
        if (!found) {
            frame[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }

        // Print frame
        printf("\nAfter page %d: ", pages[i]);
        for (int j = 0; j < f; j++)
            printf("%d ", frame[j]);
    }

    printf("\n\nTotal Page Faults = %d\n", faults);

    free(pages);
    free(frame);

    return 0;
}