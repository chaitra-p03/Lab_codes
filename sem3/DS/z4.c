#include<stdio.h>

typedef struct Book{
    int id;
    char title[40];
    char author[30];
    float price;
}Book;

void create(Book arr[], int n){
    for(int i=0; i<n; i++){
        scanf("%d",&arr[i].id);
        scanf("%s",arr[i].title);
        scanf("%s",arr[i].author);
        scanf("%f",&arr[i].price);
    }
}

int binary(Book arr[],int start,int end,char str[]){
        if(start>end) return 0;

        int mid = (start+end)/2;
        if(strcmp(arr[mid].title,str)==0) return 1; 
        if(strcmp(arr[mid].title,str)>0){
            return binary(arr,start,mid-1,str);
        }
        else {
            return binary(arr,mid+1,end,str);
        }
    }

void search(Book arr[],char str[], int n){
    int res = binary(arr,0,n-1,str);
}

void display(Book arr[], int n){
    for(int i=0; i<n; i++){
        printf("%s %d",arr[i].title, arr[i].id);
    }
}

