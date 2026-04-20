#include <stdio.h>
#include <sys/msg.h>
#include <string.h>

struct msg1 {
    long int type;
    int num;
};

struct msg2 {
    long int type;
    char result[50];
};

int main() {
    int id = msgget((key_t)1234, 0666 | IPC_CREAT);

    // send number
    struct msg1 m;
    m.type = 1;
    printf("Enter a number: ");
    scanf("%d", &m.num);
    msgsnd(id, &m, sizeof(m.num), 0);

    // wait for result
    struct msg2 r;
    msgrcv(id, &r, sizeof(r.result), 2, 0);
    printf("Result: %s\n", r.result);

    msgctl(id, IPC_RMID, 0);
    return 0;
}