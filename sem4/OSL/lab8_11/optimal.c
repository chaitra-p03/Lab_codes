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

    int faults = 0;

    for (int i = 0; i < n; i++) {

        // Check if page already in frame (HIT)
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
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

            // Only run optimal logic if no empty slot exists
            if (pos == -1) {
                int farthest = -1;
                for (int j = 0; j < f; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        // break upon first occurence
                        if (frame[j] == pages[k])
                            break;
                    }
                    // Page never used again (if found would have broken at n-1, n breaks for condition);
                    if (k == n) {
                        pos = j;
                        break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            frame[pos] = pages[i];
            faults++;
        }

        printf("\nAfter page %d: ", pages[i]);
        for (int j = 0; j < f; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);

    free(pages);
    free(frame);
    return 0;
}