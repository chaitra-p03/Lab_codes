#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

struct msg1 {
    long int type;
    int num;
};

struct msg2 {
    long int type;
    char result[50];
};

int isPalindrome(int n) {
    int original = n, rev = 0;
    while(n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return original == rev;
}

int main() {
    int id = msgget((key_t)1234, 0666 | IPC_CREAT);

    // receive number
    struct msg1 m;
    msgrcv(id, &m, sizeof(m.num), 1, 0);
    printf("Received: %d\n", m.num);

    // check palindrome
    struct msg2 r;
    r.type = 2;
    if(isPalindrome(m.num))
        strcpy(r.result, "Palindrome");
    else
        strcpy(r.result, "Not Palindrome");

    // send result back
    msgsnd(id, &r, sizeof(r.result), 0);

    return 0;
}