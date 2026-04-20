#include <stdio.h>
#include <stdlib.h>

#define MAX 50

// Reference Byte
void reference_byte(int pages[], int n, int f) {
    int frame[MAX], ref[MAX] = {0};

    for(int i=0;i<f;i++) frame[i] = -1;

    int faults = 0;

    for(int i=0;i<n;i++) {

        // shift all
        for(int j=0;j<f;j++)
            ref[j] >>= 1;

        int found = -1;

        for(int j=0;j<f;j++) {
            if(frame[j] == pages[i]) {
                found = j;
                break;
            }
        }

        if(found != -1) {
            ref[found] |= (1 << 7); // set MSB
        } else {
            int pos = 0;
            for(int j=1;j<f;j++){
                if(ref[j] < ref[pos]) pos = j;
            }
            frame[pos] = pages[i];
            ref[pos] = (1 << 7);
            faults++;
        }
        printf("Page %d: ", pages[i]);
        for(int j = 0; j < f; j++){
            if(frame[j] == -1) printf("- ");
            else printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("\nReference Byte Faults = %d\n", faults);
}

/* ------------------ 2. Second Chance ------------------ */
void second_chance(int pages[], int n, int f) {
    int frame[MAX], ref[MAX] = {0};
    for(int i=0;i<f;i++) frame[i] = -1;

    int pointer = 0, faults = 0;

    for(int i=0;i<n;i++) {
        int found = 0;

        for(int j=0;j<f;j++) {
            if(frame[j] == pages[i]) {
                ref[j] = 1;
                found = 1;
                break;
            }
        }

        if(!found) {
            while(1) {
                if(ref[pointer] == 0) {
                    frame[pointer] = pages[i];
                    ref[pointer] = 1;
                    pointer = (pointer + 1) % f;
                    faults++;
                    break;
                } else {
                    ref[pointer] = 0;
                    pointer = (pointer + 1) % f;
                }
            }
        }
                printf("Page %d: ", pages[i]);
        for(int j = 0; j < f; j++){
            if(frame[j] == -1) printf("- ");
            else printf("%d ", frame[j]);
        }
        printf("\n");

    }

    printf("Second Chance Faults = %d\n", faults);
}

/* ------------------ 3. Enhanced Second Chance ------------------ */
void enhanced_second_chance(int pages[], int n, int f) {
    int frame[MAX], R[MAX] = {0}, M[MAX] = {0};
    for(int i = 0; i < f; i++) frame[i] = -1;

    int faults = 0;

    for(int i = 0; i < n; i++) {
        int found = 0;

        // Check hit
        for(int j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                R[j] = 1;   // mark referenced
                found = 1;
                break;
            }
        }

        if(!found) {
            int pos = -1;

            // --- First pass: look for (0,0) ---
            for(int j = 0; j < f; j++)
                if(R[j]==0 && M[j]==0) { pos = j; break; }

            // --- Second pass: clear R bits, look for (0,1) ---
            if(pos == -1) {
                for(int j = 0; j < f; j++) R[j] = 0;  // ← simulate timer: clear all R bits

                for(int j = 0; j < f; j++)
                    if(R[j]==0 && M[j]==1) { pos = j; break; }
            }

            // --- Third pass: look for (0,0) again (R bits were just cleared) ---
            if(pos == -1)
                for(int j = 0; j < f; j++)
                    if(R[j]==0 && M[j]==0) { pos = j; break; }

            // --- Fourth pass: look for (0,1) again ---
            if(pos == -1)
                for(int j = 0; j < f; j++)
                    if(R[j]==0 && M[j]==1) { pos = j; break; }

            // --- Fallback (should not happen after R clear) ---
            if(pos == -1) pos = 0;

            frame[pos] = pages[i];
            R[pos] = 1;
            M[pos] = 0;   // newly loaded page is clean (not modified)
            faults++;
        }

        printf("Page %d: ", pages[i]);
        for(int j = 0; j < f; j++)
            printf(frame[j] == -1 ? "- " : "%d ", frame[j]);
        printf("\n");
    }

    printf("Enhanced Second Chance Faults = %d\n", faults);
}

/* ------------------ MAIN ------------------ */
int main() {
    int n, f;
    int pages[MAX];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for(int i=0;i<n;i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    reference_byte(pages, n, f);
    second_chance(pages, n, f);
    enhanced_second_chance(pages, n, f);

    return 0;
}