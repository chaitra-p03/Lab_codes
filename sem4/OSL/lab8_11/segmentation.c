#include <stdio.h>

#define MAX 10

int main() {
    int n;

    printf("Enter number of segments: ");
    scanf("%d", &n);

    int base[MAX], limit[MAX];

    printf("Enter base and limit for each segment:\n");
    for (int i = 0; i < n; i++) {
        printf("Segment %d:\n", i);
        printf("Base: ");
        scanf("%d", &base[i]);
        printf("Limit: ");
        scanf("%d", &limit[i]);
    }

    int seg, offset;

    printf("\nEnter segment number: ");
    scanf("%d", &seg);

    printf("Enter offset: ");
    scanf("%d", &offset);

    if (seg >= n) {
        printf("Invalid segment number\n");
        return 0;
    }

    if (offset >= limit[seg]) {
        printf("Segmentation Fault (Invalid offset)\n");
    } else {
        int physical = base[seg] + offset;
        printf("Physical Address = %d\n", physical);
    }

    return 0;
}