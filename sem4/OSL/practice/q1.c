// Implement LSTF disk schuduling along with MFU page replacement
#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void display(int seq[], int n, int total){
    for(int i = 0; i < n; i++){
        printf("%d ", seq[i]);
    }
    printf("\nTotal Seek Time = %d\n", total);
}

void lstf(int pages[], int cyl[], int n, int head, int ordered_pages[]){
    int visited[MAX] = {0};
    int total = 0;
    int curr = head;

    for(int i = 0; i < n; i++){
        int maxDist = -1;
        int pos = -1;

        for(int j = 0; j < n; j++){
            if(!visited[j] && abs(curr - cyl[j])>maxDist){
                maxDist = curr - cyl[j];
                pos = j;
            }
        }

        visited[pos] = 1;
        total += maxDist;
        curr = cyl[pos];

        ordered_pages[i] = pages[pos];
    }

    printf("\nLSTF Order (Pages):\n");
    display(ordered_pages, n, total);
}

void mfu(int pages[], int n, int f){
    int frames[f];
    int freq[f];
    int faults = 0;

    for(int i = 0; i < f; i++){
        frames[i] = -1;
        freq[i] = 0;
    }

    printf("\nMFU Process:\n");

    for(int i = 0; i < n; i++){
        int found = 0;

        for(int j = 0; j < f; j++){
            if(frames[j] == pages[i]){
                found = 1;
                freq[j]++;
                break;
            }
        }

        if(!found){
            faults++;

            int pos = -1;

            for(int j = 0; j < f; j++){
                if(frames[j] == -1){
                    pos = j;
                    break;
                }
            }

            if(pos == -1){
                pos = 0;
                for(int j = 1; j < f; j++){
                    if(freq[j] > freq[pos]){
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            freq[pos] = 1;
        }

        printf("Page %d -> ", pages[i]);
        for(int j = 0; j < f; j++){
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

int main(){
    int f, head;
    int pages[MAX], cyl[MAX];
    int n = 0;

    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter (page cylinder), -1 to stop:\n");

    while(1){
        int p;
        scanf("%d", &p);
        if(p == -1) break;

        scanf("%d", &cyl[n]);
        pages[n] = p;
        n++;
    }

    int ordered_pages[MAX];

    lstf(pages, cyl, n, head, ordered_pages);
    mfu(ordered_pages, n, f);

    return 0;
}