#include<stdio.h>
#include<stdlib.h>

int* creation(int n){
    int * arr = (int*)malloc(n*sizeof(int));
    if(arr==NULL){
        printf("Memory not allocated\n");
        exit(0);
    }
    for(int i=0; i<n; i++){
        printf("Enter no of patients: ");
        scanf("%d",(arr+i));
    }
    return arr;
}

void display(int * arr, int n){
    for(int i=0; i<n; i++){
        printf("%d ",*(arr+i));
    }
}

int min(int * arr, int n, int index, int min_index){
    if(index>=n) {
        return min_index+1;
    } 
    if(arr[index]<arr[min_index]){
        min_index=index;
    }
    return min(arr,n,index+1,min_index);
}

int main(){
    printf("Enter no of days: ");
    int n;
    scanf("%d",&n);
    int * arr = creation(n);
    display(arr,n);
    int res = min(arr,n,0,0);
    printf("Min is on day %d",res);
    printf("\n");
    display(arr,n);
}