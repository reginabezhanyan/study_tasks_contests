#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int msgid;

typedef struct Message
{
    long mtype;
    char Data[256];
} Message;

void handler(int s)
{
    printf("\nSIGINT, HELLO!\n");
    fflush(stdout);
    msgctl(msgid, IPC_RMID, NULL);
    exit(0);
}

int main(int argc, char *argv[])
{
    key_t key = strtol(argv[1], NULL, 10);
    char str[256];
    struct Message Message;
    if (!fork()) {
        int count = 0;
        while ((msgid = msgget(key, 0666)) < 0);
        
        while (1) {
            printf("B waiting\n");
            fflush(stdout);
            count = msgrcv(msgid, (struct msgbuf *) (&Message), sizeof(Message.Data), 2, 0);
            if (count <= 0) {
                exit(0);
            }
            printf("2 got %s", Message.Data);
            fflush(stdout);
            if (Message.Data[0] == 'q' || Message.Data[0] == 'Q') {
                Message.mtype = 4;
                strcpy(Message.Data, "DONE!\n");
                msgsnd(msgid, (struct msgbuf *) (&Message), strlen(Message.Data) + 1, 0);
                exit(0);
            }
            sleep(1);
        }
    }
    if (!fork()) {
        int count = 0;
        while ((msgid = msgget(key, 0666)) < 0);
                
        while (1) {
            printf("A waiting\n");
            fflush(stdout);
            count = msgrcv(msgid, (struct msgbuf *) (&Message), sizeof(Message.Data), 1, 0);
            if (count <= 0) {
                exit(0);
            }
            printf("1 got %s", Message.Data);
            fflush(stdout);
            if (Message.Data[0] == 'q' || Message.Data[0] == 'Q') {
                Message.mtype = 3;
                strcpy(Message.Data, "DONE!\n");
                msgsnd(msgid, (struct msgbuf *) (&Message), strlen(Message.Data) + 1, 0);
                exit(0);
            }
            sleep(1);
        }
    }
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler }, NULL);
    msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
    while (1) {
        fgets(str, sizeof(str), stdin);
        strcpy(Message.Data, str);
        if (str[0] == 'a' || str[0] == 'A') {
            Message.mtype = 1;
            msgsnd(msgid, (struct msgbuf *) (&Message), strlen(Message.Data) + 1, 0);
        } else if (str[0] == 'b' || str[0] == 'B') {
            Message.mtype = 2;
            msgsnd(msgid, (struct msgbuf *) (&Message), strlen(Message.Data) + 1, 0);
        } else if (str[0] == 'q' || str[0] == 'Q') {
            Message.mtype = 1;
            msgsnd(msgid, (struct msgbuf *) (&Message), strlen(Message.Data) + 1, 0);
            Message.mtype = 2;
            msgsnd(msgid, (struct msgbuf *) (&Message), strlen(Message.Data) + 1, 0);
            sleep(1);
            
            msgrcv(msgid, (struct msgbuf *) (&Message), sizeof(Message.Data), 3, 0);
            printf("1: %s", Message.Data);
            msgrcv(msgid, (struct msgbuf *) (&Message), sizeof(Message.Data), 4, 0);
            printf("2: %s", Message.Data);

            msgctl(msgid, IPC_RMID, NULL);
            break;
        }
    }


    while (wait(NULL) != -1);
    return 0;
}
