// Scan, CScan with MFU

#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void sort(int arr[], int pages[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j] > arr[j+1]){
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;

                int p = pages[j];
                pages[j] = pages[j+1];
                pages[j+1] = p;
            }
        }
    }
}

void display(int seq[], int n, int total){
    printf("Page Order:\n");
    for(int i=0;i<n;i++)
        printf("%d ", seq[i]);
    printf("\nTotal Seek Time = %d\n", total);
}

/* SCAN (LEFT first) */
void scan(int pages[], int cyl[], int n, int head, int size){
    sort(cyl, pages, n);

    int total = 0, seq[MAX], k = 0;

    int i;
    for(i=0;i<n && cyl[i] < head;i++);

    // LEFT side
    for(int j=i-1;j>=0;j--){
        total += abs(head - cyl[j]);
        head = cyl[j];
        seq[k++] = pages[j];
    }

    // go to 0
    total += abs(head - 0);
    head = 0;

    // RIGHT side
    for(int j=i;j<n;j++){
        total += abs(head - cyl[j]);
        head = cyl[j];
        seq[k++] = pages[j];
    }

    printf("\nSCAN:\n");
    display(seq, k, total);
}

/* C-SCAN (RIGHT first, jump NOT counted) */
void cscan(int pages[], int cyl[], int n, int head, int size){
    sort(cyl, pages, n);

    int total = 0, seq[MAX], k = 0;

    int i;
    for(i=0;i<n && cyl[i] < head;i++);

    // RIGHT side
    for(int j=i;j<n;j++){
        total += abs(head - cyl[j]);
        head = cyl[j];
        seq[k++] = pages[j];
    }

    // go to end
    total += abs(head - (size-1));
    head = size-1;

    // jump to 0 (NOT counted)
    head = 0;

    // LEFT side
    for(int j=0;j<i;j++){
        total += abs(head - cyl[j]);
        head = cyl[j];
        seq[k++] = pages[j];
    }

    printf("\nC-SCAN:\n");
    display(seq, k, total);
}

/* MFU */
void mfu(int pages[], int n, int f){
    int frames[f], freq[f], faults = 0;

    for(int i=0;i<f;i++){
        frames[i] = -1;
        freq[i] = 0;
    }

    printf("\nMFU Process:\n");

    for(int i=0;i<n;i++){
        int found = 0;

        for(int j=0;j<f;j++){
            if(frames[j] == pages[i]){
                found = 1;
                freq[j]++;
                break;
            }
        }

        if(!found){
            faults++;

            int pos = -1;

            // empty frame
            for(int j=0;j<f;j++){
                if(frames[j] == -1){
                    pos = j;
                    break;
                }
            }

            // replace MFU
            if(pos == -1){
                pos = 0;
                for(int j=1;j<f;j++){
                    if(freq[j] > freq[pos])
                        pos = j;
                }
            }

            frames[pos] = pages[i];
            freq[pos] = 1;
        }

        printf("Page %d -> ", pages[i]);
        for(int j=0;j<f;j++){
            if(frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

/* MAIN */
int main(){
    int f, head, size;
    int pages[MAX], cyl[MAX];
    int n = 0;

    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &size);

    printf("Enter (page cylinder), -1 to stop:\n");

    while(1){
        int p;
        scanf("%d", &p);
        if(p == -1) break;

        scanf("%d", &cyl[n]);
        pages[n] = p;
        n++;
    }

    int seq[MAX];

    // SCAN
    scan(pages, cyl, n, head, size);

    // C-SCAN
    cscan(pages, cyl, n, head, size);

    sort(cyl, pages, n);
    mfu(pages, n, f);

    return 0;
}