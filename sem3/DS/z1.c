#include<stdio.h>
// Assuming first is sorted then insert
void insertion(int arr[], int n){
    for(int i=1; i<n; i++){
        int key = arr[i];
        int j = i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void insertion_rec(int arr[], int n, int i){
    if (i==n) return; 

    int key = arr[i];
    int j = i-1;
   while(j>=0 && arr[j]>key){
    arr[j+1]= arr[j];
    j--;
   }
   arr[j+1]=key;
    insertion_rec(arr,n,i+1);
}

void display(int arr[], int n){
    for(int i=0; i<n; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

// Sort the n-1 then insert nth


int main(){
    int arr[5]={43,12,9,8,4};
    insertion(arr,5);
    display(arr,5);
    int arr2[6]={6,1,3,5,0,7};
    insertion_rec(arr2,6,1);
    display(arr2,6);
}