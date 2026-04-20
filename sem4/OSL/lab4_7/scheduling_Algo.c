#include<stdio.h>

#define MAX 10

struct process{
    int pid, at, bt, wt,  ct, rt, tat, priority;
    int queue;
};

struct process p[MAX];
int n;

void reset(){
    for(int i=0; i<n; i++){
        p[i].rt=p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }
}

void sort(){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(p[j].at>p[j+1].at){
                struct process temp = p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void display(){
    float avgw = 0; 
    float avgt= 0;
        printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
        for(int i=0; i<n; i++){
            printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
                p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        }
}

void fcfs(){
    sort();
    int time = 0;
    for(int i=0; i<n; i++){
        if(time<p[i].at){
            printf("Idle %d %d", time, p[i].at);
            time=p[i].at;
        }
        printf("P%d (%d %d)|",p[i].pid,time,time+p[i].bt);
        time+=p[i].bt;
        p[i].rt = 0;
        p[i].ct = time;
        p[i].tat = p[i].ct -p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    display();
}

void rr(){
    printf("Enter quantum: ");
    int q;
    scanf("%d",&q);
    sort();
    int time = 0;
    int completed = 0; 
    while(completed<n){
        int done = 0;
        for(int i=0; i<n; i++){
            if(p[i].at<=time && p[i].rt>0){
                done=1;
                int run = (p[i].rt < q) ? p[i].rt : q;
                p[i].rt-=run;
                printf("P%d (%d %d) || ",p[i].pid,time,time+run);
                time+=run;
                if(p[i].rt==0){
                    completed++;
                    p[i].ct=time;
                    p[i].tat=p[i].ct-p[i].at;
                    p[i].wt=p[i].tat-p[i].bt;
                }
            }
        }
        if(done==0){
            printf("Idle (%d %d) || ", time, time+1);
            time++;
        }
        /*
        if(done == 0){
            int next_at = 1e9;
            for(int i=0; i<n; i++){
                if(p[i].rt > 0 && p[i].at > time){
                    if(p[i].at < next_at){
                        next_at = p[i].at;
                    }
                }      
            }
    printf("Idle (%d %d) || ", time, next_at);
    time = next_at;
}  */

    }
    display();
}

//sjf is same as non preemptive priority but with bt as priority
void nonpreepriority(){
    sort();
    int time = 0;
    int completed = 0;
    int visited[MAX] = {0};

    while(completed < n){
        int idx = -1;
        for(int i = 0; i < n; i++){
            if(!visited[i] && p[i].at <= time){
                if(idx == -1 || p[i].priority < p[idx].priority){
                    idx = i;
                }
            }
        }
        if(idx == -1){
    int next = 1000000;
    for(int i=0; i<n; i++){
        if(!visited[i] && p[i].at > time){
            if(p[i].at < next){
                next = p[i].at;
            }
        }
    }
    printf("Idle (%d %d) | ", time, next);
    time = next;
    continue;
}
        printf("P%d (%d %d) | ", p[idx].pid, time, time + p[idx].bt);
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        visited[idx] = 1;
        completed++;
    }
    display();
}

// preemptive prioirty is same but with priority instead of rt
// edf also same but with deadline
// rms also same but with period
void srtf(){
    sort();
    int time = 0;
    int completed = 0;

    while(completed < n){
        int idx = -1;
        for(int i = 0; i < n; i++){
            if(p[i].at <= time && p[i].rt > 0){
                if(idx == -1 || p[i].rt < p[idx].rt){
                    idx = i;
                }
            }
        }

        if(idx == -1){
            printf("Idle (%d %d) | ", time, time+1);
            time++;
            continue;
        }
        printf("P%d (%d %d) | ", p[idx].pid, time, time+1);
        p[idx].rt--;
        time++;

        if(p[idx].rt == 0){
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }
    display();
}
void mlfq() {
    int q1 = 4, q2 = 8;
    int time = 0, completed = 0;

    for(int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
        p[i].queue = 1;
        p[i].ct = 0;
    }

    printf("\nMLFQ Gantt Chart:\n");

    while(completed < n) {
        int found = 0;

        // -------- Q1 (RR q=4) --------
        for(int i = 0; i < n; i++) {
            if(p[i].queue == 1 && p[i].at <= time && p[i].rt > 0) {
                int run = (p[i].rt < q1) ? p[i].rt : q1;

                printf("P%d(Q1) (%d %d) | ", p[i].pid, time, time + run);

                p[i].rt -= run;
                time += run;
                found = 1;

                if(p[i].rt == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                } else {
                    p[i].queue = 2;  // demote
                }
                break;
            }
        }

        // -------- Q2 (RR q=8) --------
        if(!found) {
            for(int i = 0; i < n; i++) {
                if(p[i].queue == 2 && p[i].at <= time && p[i].rt > 0) {
                    int run = (p[i].rt < q2) ? p[i].rt : q2;

                    printf("P%d(Q2) (%d %d) | ", p[i].pid, time, time + run);

                    p[i].rt -= run;
                    time += run;
                    found = 1;

                    if(p[i].rt == 0) {
                        p[i].ct = time;
                        p[i].tat = p[i].ct - p[i].at;
                        p[i].wt = p[i].tat - p[i].bt;
                        completed++;
                    } else {
                        p[i].queue = 3;  // demote
                    }
                    break;
                }
            }
        }

        // -------- Q3 (FCFS) --------
        if(!found) {
            for(int i = 0; i < n; i++) {
                if(p[i].queue == 3 && p[i].at <= time && p[i].rt > 0) {

                    printf("P%d(Q3) (%d %d) | ", p[i].pid, time, time + p[i].rt);

                    time += p[i].rt;
                    p[i].rt = 0;
                    found = 1;

                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                    break;
                }
            }
        }

        // -------- Idle --------
        if(!found) {
            int next = 1e9;
            for(int i = 0; i < n; i++) {
                if(p[i].rt > 0 && p[i].at > time) {
                    if(p[i].at < next) next = p[i].at;
                }
            }
            printf("Idle (%d %d) | ", time, next);
            time = next;
        }
    }

    display();
}
int main(){
    printf("Enter the n: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        printf("Enter at, bt, prior: ");
        scanf("%d",&p[i].at);
        scanf("%d",&p[i].bt);
        scanf("%d",&p[i].priority);
        p[i].pid=i;
        p[i].rt=p[i].bt;
    }
    reset();
    fcfs();
    reset();
    rr();
    reset();
    nonpreepriority();

}