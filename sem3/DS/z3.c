/*write a c program using structures and pointers to store employee details. 
each employee should have name string, id integer, email string 
the program should 
count how many employees have a gmail id 
display all employee details and count
*/
#include<stdio.h>
#include<string.h>

struct employee{
    char name[50];
    int id;
    char email[20];
};

void add(struct employee * ptr, int n){
    for(int i=0; i<n; i++){
        scanf("%s",ptr->name);
        scanf("%d",&ptr->id);
        scanf("%s",ptr->email);
        ptr++;
    }
}


int valid_mail(struct employee* ptr){
    /*char * mail = ptr->email;
    while(*mail!='\0'){
        if(*mail=='@'){
            return 1;
        }
        mail++;
    }
    return 0; */
    return (strstr(ptr->email, "@gmail.com")!=NULL);
}

void count_mail(struct employee * ptr, int n){
    int count = 0;
    for(int i=0; i<n; i++){
        count+=valid_mail(ptr+i);
    }
    printf("People with Gmail is %d", count);
}

void display(struct employee * ptr, int n){
    int c = 0;
    for(int i=0; i<n; i++){
        printf("%s %d %s | ",(ptr+i)->name, (ptr+i)->id, (ptr+i)->email);
        c++;
    }
    printf("Count %d",c);
}


int main(){
    int n;
    scanf("%d",&n);
    struct employee arr[n];
    struct employee * ptr = arr;
    add(ptr,n);
    count_mail(ptr,n);
    display(ptr,n);
}
