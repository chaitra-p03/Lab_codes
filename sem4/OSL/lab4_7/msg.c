#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

struct my_msg {
    long int msg_type;
    char text[100];
};

int main() {
    // 1. Create queue
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    // 2. Send
    struct my_msg m;
    m.msg_type = 1;
    strcpy(m.text, "hello");
    msgsnd(msgid, &m, sizeof(m.text), 0);

    // 3. Receive
    struct my_msg received;
    msgrcv(msgid, &received, sizeof(received.text), 1, 0);
    printf("Got: %s\n", received.text);

    // 4. Delete
    msgctl(msgid, IPC_RMID, 0);

    return 0;
}