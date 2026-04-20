#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void print(int seq[], int n, int total) {
    for(int i = 0; i < n; i++) {
        printf("%d ", seq[i]);
    }
    printf("\nTotal movement = %d\n", total);
}

/* FCFS */
void fcfs(int req[], int n, int head) {
    int total = 0, seq[MAX];
    seq[0] = head;

    for(int i = 0; i < n; i++) {
        total += abs(head - req[i]);
        head = req[i];
        seq[i+1] = head;
    }

    printf("\nFCFS:\n");
    print(seq, n+1, total);
}

/* SSTF */
void sstf(int req[], int n, int head) {
    int visited[MAX] = {0}, total = 0, seq[MAX];
    seq[0] = head;

    for(int i = 0; i < n; i++) {
        int min = 9999, idx = -1;

        for(int j = 0; j < n; j++) {
            if(!visited[j] && abs(head - req[j]) < min) {
                min = abs(head - req[j]);
                idx = j;
            }
        }

        visited[idx] = 1;
        total += min;
        head = req[idx];
        seq[i+1] = head;
    }

    printf("\nSSTF:\n");
    print(seq, n+1, total);
}

/* Sort helper */
void sort(int arr[], int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
}

/* SCAN (LEFT first) */
void scan(int req[], int n, int head, int size) {
    sort(req, n);
    int total = 0, seq[MAX], k = 0;

    int i;
    for(i = 0; i < n && req[i] < head; i++);

    seq[k++] = head;

    // move left
    for(int j = i-1; j >= 0; j--) {
        total += abs(head - req[j]);
        head = req[j];
        seq[k++] = head;
    }

    // go to 0
    total += abs(head - 0);
    head = 0;
    seq[k++] = head;

    // move right
    for(int j = i; j < n; j++) {
        total += abs(head - req[j]);
        head = req[j];
        seq[k++] = head;
    }

    printf("\nSCAN:\n");
    print(seq, k, total);
}

/* C-SCAN (RIGHT first, jump NOT counted) */
void cscan(int req[], int n, int head, int size) {
    sort(req, n);
    int total = 0, seq[MAX], k = 0;

    int i;
    for(i = 0; i < n && req[i] < head; i++);

    seq[k++] = head;

    // move right
    for(int j = i; j < n; j++) {
        total += abs(head - req[j]);
        head = req[j];
        seq[k++] = head;
    }

    // go to end
    total += abs(head - (size - 1));
    head = size - 1;
    seq[k++] = head;

    // jump to 0 (NOT counted)
    head = 0;
    seq[k++] = head;

    // service remaining
    for(int j = 0; j < i; j++) {
        total += abs(head - req[j]);
        head = req[j];
        seq[k++] = head;
    }

    printf("\nC-SCAN:\n");
    print(seq, k, total);
}

/* LOOK (LEFT first) */
void look(int req[], int n, int head) {
    sort(req, n);
    int total = 0, seq[MAX], k = 0;

    int i;
    for(i = 0; i < n && req[i] < head; i++);

    seq[k++] = head;

    // left
    for(int j = i-1; j >= 0; j--) {
        total += abs(head - req[j]);
        head = req[j];
        seq[k++] = head;
    }

    // right
    for(int j = i; j < n; j++) {
        total += abs(head - req[j]);
        head = req[j];
        seq[k++] = head;
    }

    printf("\nLOOK:\n");
    print(seq, k, total);
}

/* C-LOOK (RIGHT first) */
void clook(int req[], int n, int head) {
    sort(req, n);
    int total = 0, seq[MAX], k = 0;

    int i;
    for(i = 0; i < n && req[i] < head; i++);

    seq[k++] = head;

    // move right
    for(int j = i; j < n; j++) {
        total += abs(head - req[j]);
        head = req[j];
        seq[k++] = head;
    }

    // jump to lowest request
    if(i > 0) {
        head = req[0];
        seq[k++] = head;

        for(int j = 1; j < i; j++) {
            total += abs(head - req[j]);
            head = req[j];
            seq[k++] = head;
        }
    }

    printf("\nC-LOOK:\n");
    print(seq, k, total);
}

int main() {
    int n, req[MAX], head, size;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter requests:\n");
    for(int i = 0; i < n; i++) scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &size);

    fcfs(req, n, head);
    sstf(req, n, head);
    scan(req, n, head, size);
    cscan(req, n, head, size);
    look(req, n, head);
    clook(req, n, head);

    return 0;
}