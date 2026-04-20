#include <stdio.h>
#include <stdlib.h>

int main() {
    int frames, pages;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &pages);

    int *ref = (int *)malloc(pages * sizeof(int));
    int *frame = (int *)malloc(frames * sizeof(int));
    int *freq = (int *)malloc(frames * sizeof(int));

    printf("Enter page reference string: ");
    for (int i = 0; i < pages; i++)
        scanf("%d", &ref[i]);

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        freq[i] = 0;
    }

    int faults = 0;

    for (int i = 0; i < pages; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                freq[j]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // No empty frame
            if (pos == -1) {
                int maxFreq = freq[0];
                pos = 0;
                for (int j = 1; j < frames; j++) {
                    if (freq[j] > maxFreq) {
                        maxFreq = freq[j];
                        pos = j;
                    }
                }
            }

            frame[pos] = ref[i];
            freq[pos] = 1;
            faults++;
        }

        printf("Page %d -> Frames: ", ref[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] == -1) printf("- ");
            else printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults (MFU): %d\n", faults);

    free(ref); free(frame); free(freq);
    return 0;
}