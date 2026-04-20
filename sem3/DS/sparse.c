#include<stdio.h>

#define MAX 20 

typedef struct term
{
    int row; 
    int column; 
    int val;
} term;

void create_sparse(term a[], int row, int col, int mat[][20]){
    int k = 1; 
    a[0].row = row; 
    a[0].column = col;
    a[0].val = 0;

    for(int i =0; i<row; i++){
        for(int j=0; j<col; j++){
            if(mat[i][j]!=0){
                a[k].row = i; 
                a[k].column = j;
                a[k].val = mat[i][j];
                k++;
                a[0].val++;
            }
        }
    }
}

void display(term a[]){
    for(int i=1; i<=a[0].val; i++){
        printf("(%d %d %d )\n", a[i].row, a[i].column, a[i].val);
    }
}

// SIMPLE TRANSPOSE o(col * non zero)
void simpleTranspose(term a[], term b[]){
    int n = a[0].val; 
    int col = a[0].column;
    int row = a[0].row;

    // set dimensions for tranposed
    b[0].row = col;
    b[0].column = row; 
    b[0].val = n;

    // iterating through the columns and finding the non zero element
    if(n>0){
        int q=1;
        for(int cols = 0; cols< col; cols++){
            for(int i=1; i<=n; i++){
                if(a[i].column == cols){
                    b[q].row = a[i].column;
                    b[q].column = a[i].row;
                    b[q].val = a[i].val;
                    q++;
                }
            }
        }
    }
}

void fastTranpose(term a[], term b[]){
    int rowTerms[MAX];
    int starting_pos[MAX];
    int n = a[0].val;
    int col = a[0].column;
    int row = a[0].row;

    // Set dimensions for tranposed 
    b[0].row = col;
    b[0].column = row; 
    b[0].val = n;

    if(n>0){
        for(int i=0; i<col; i++){
            rowTerms[i]=0;
        }
        for(int i=1; i<=n; i++){
            rowTerms[a[i].column]++;
        }
        starting_pos[0]=1;
        for(int i=1; i<col; i++){
            starting_pos[i]=starting_pos[i-1]+rowTerms[i-1];
        }
    for(int i=1; i<=n; i++){
        int j = starting_pos[a[i].column];
        b[j].row = a[i].column;
        b[j].column = a[i].row;
        b[j].val = a[i].val;
        starting_pos[a[i].column]++;
    }
}
}

int main(){
    int mat[20][20] = {
        {0,0,3,0,4},
        {0,0,5,7,0},
        {0,0,0,0,0},
        {0,2,6,0,0}
    };
    
    term sparse[MAX], transposed[MAX];
    
    printf("Original Matrix:\n");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    
    create_sparse(sparse, 4, 4, mat);
    
    printf("\nSparse representation:\n");
    display(sparse);
    
    simpleTranspose(sparse, transposed);
    printf("\nTransposed sparse matrix:\n");
    display(transposed);
    
    return 0;
}
