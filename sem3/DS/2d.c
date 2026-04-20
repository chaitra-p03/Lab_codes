#include<stdio.h>
#include<stdlib.h>

typedef struct Student{
    char name[50];
    int roll; 
    float marks; 
}Student;

void read(Student * ptr){
    printf("Enter name, roll, marks: ");
    scanf("%s",ptr->name);
    scanf("%d",&ptr->roll);
    scanf("%f",&ptr->marks);
}

void display(Student *ptr, int n){
    for(int i=0; i<n; i++){
        printf("Name: %s Roll: %d marks %f\n",(ptr+i)->name, (ptr+i)->roll, (ptr+i)->marks);
    }
}

Student * find_highest(Student *ptr, int n){
    int max = 0;
    Student * res;
    for(int i=0; i<n; i++){
        if((ptr+i)->marks>max){
            max=(ptr+i)->marks;
            res=ptr+i;
        }
    }
    return res;
}


int main(){
int n; 
printf("Enter no of students: ");
scanf("%d",&n);

Student * arr = (Student *)malloc(n*sizeof(Student));
for(int i=0; i<n; i++){
    read(arr+i);
}

display(arr,n);
Student *highest = find_highest(arr,n);
printf("The student with highest marks is %s of roll %d and marks %.2f", highest->name, highest->roll, highest->marks);

free(arr);

}