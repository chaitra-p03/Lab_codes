#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct employee{
    char name[30];
    int id; 
    char dept[20];
    int sal;
}employee;

int selection_rec(employee arr[],int n){
    if(n<=1) return 0;

    int min = 0;
    for(int i=0; i<n; i++){
        if(arr[i].id<arr[min].id){
            min = i;
        }
    }

    employee temp = arr[0];
    arr[0] = arr[min];
    arr[min] = temp;
    
    return selection_rec(arr+1,n-1);
}

void sort(employee arr[], int n){
    selection_rec(arr,n);   
}

void max_sal(employee arr[], int n){
    int max = 0;
    for(int i=1; i<n; i++){
        if(arr[i].sal > arr[max].sal){
            max = i;
        }
    }
    printf("Emp with max sal is %s",arr[max].name);
}

