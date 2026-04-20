// best fit + safety check

#include<stdio.h>
#include<stdbool.h>

#define MAX 10
int max[MAX], need[MAX];
int alloc[MAX];
int blocks[MAX];
int nb, np;

void sort(int arr[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j]<arr[j+1]){
                int temp=arr[j]; 
                arr[j]=arr[j+1]; 
                arr[j+1]=temp;
            }
        }
    }
}

void calcNeed(){
    for(int i=0; i<np; i++)
        need[i]=max[i]-alloc[i];
}

int bestFit(int request){
    int best=-1;
    for(int i=0; i<nb; i++)
        if(blocks[i]>=request)
            if(best==-1 || blocks[i]<blocks[best])
                best=i;
    return best;
}

bool isSafe(){
    int work=0;
    bool finish[MAX]={false};
    int seq[MAX], k=0;

    for(int i=0; i<nb; i++) work+=blocks[i];

    while(1){
        bool found=false;
        for(int i=0; i<np; i++){
            if(!finish[i] && need[i]<=work){
                work+=alloc[i];
                finish[i]=true;
                if(alloc[i]>0)
                    seq[k++]=i;
                found=true;
            }
        }
        if(!found) break;
    }

    for(int i=0; i<np; i++)
        if(!finish[i]) return false;

    printf("Safe | Seq: ");
    for(int i=0; i<k; i++) printf("P%d ", seq[i]);
    printf("\n");

    return true;
}

int main(){
    printf("Enter no of blocks: ");
    scanf("%d",&nb);
    printf("Enter size of each block: ");
    for(int i=0; i<nb; i++) scanf("%d",&blocks[i]);

    printf("Enter no of processes: ");
    scanf("%d",&np);
    printf("Enter the max mem for each process:\n");
    for(int i=0; i<np; i++){
        printf("P%d: ",i);
        scanf("%d",&max[i]);
        alloc[i]=0;
    }
    calcNeed();

    while(1){
        int pid, req;
        printf("\nEnter pid (-1 to stop): ");
        scanf("%d",&pid);
        if(pid==-1) break;

        printf("Enter request: ");
        scanf("%d",&req);

        printf("P%d request %d\n", pid, req);

        sort(blocks, nb);

        printf("Before: ");
        for(int i=0; i<nb; i++) printf("%d ", blocks[i]);
        printf("\n");

        if(req>need[pid]){
            printf("Exceeds max need\n");
            continue;
        }

        int idx=bestFit(req);
        if(idx==-1){
            printf("No suitable block\n");
            continue;
        }

        blocks[idx]-=req;
        alloc[pid]+=req;
        calcNeed();

        sort(blocks, nb);

        printf("After: ");
        for(int i=0; i<nb; i++) printf("%d ", blocks[i]);
        printf("\n");

        if(!isSafe()){
            printf("Not Safe -> Rollback\n");
            blocks[idx]+=req;
            alloc[pid]-=req;
            calcNeed();
        }
    }

    printf("\nFinal Allocation:\n");
    for(int i=0; i<np; i++)
        printf("P%d: %d\n", i, alloc[i]);

    return 0;
}