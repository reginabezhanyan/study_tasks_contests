#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

struct Message
{
    long type;
    long value;
};

int MAX;
int LEVEL;

void
merge(int msgid, int k)
{  
    int m;
    int i = k << 1;
    int j = (k << 1) + 1;
    struct Message fir, sec, msg;
    msg.type = k;  
    if (((m = msgrcv(msgid, &sec, sizeof(sec) - sizeof(sec.type), 
            j, IPC_NOWAIT)) == -1) && (j > LEVEL)) { 
        while (msgrcv(msgid, &fir, sizeof(fir) - sizeof(fir.type), i, IPC_NOWAIT) != -1) {
            msg.value = fir.value;
            msgsnd(msgid, &msg, sizeof(msg) - sizeof(msg.type), IPC_NOWAIT);
        }
        return;
    } 
    if(m < 0) {
        return;    
    }
    if (msgrcv(msgid, &fir, sizeof(fir) - sizeof(fir.type), i, IPC_NOWAIT) < 0)  {
        return;
    }  
    while(1) { 
        if (fir.value == sec.value) {
            msg.value = fir.value; 
            msgsnd(msgid, &msg, sizeof(msg) - sizeof(msg.type), IPC_NOWAIT);
            if (msgrcv(msgid, &fir, sizeof(fir) - sizeof(fir.type), i, IPC_NOWAIT) < 0) {
                return;
            }
            if (msgrcv(msgid, &sec, sizeof(sec) - sizeof(sec.type), j, IPC_NOWAIT) < 0) {
                return;
            }
        } else if (fir.value < sec.value){
            if (msgrcv(msgid, &fir, sizeof(fir) - sizeof(fir.type), i, IPC_NOWAIT) < 0) {
                return;
            }
        } else {
            if (msgrcv(msgid, &sec, sizeof(sec) - sizeof(sec.type), j, IPC_NOWAIT) < 0) {
                return;
            }
        }
    } 
}

void
tree_fork(int msgid, int i, int n)
{ 
    if (i << 1 < LEVEL) {
        if (!fork()) {
            tree_fork(msgid, i << 1, n); 
            _exit(0);
        }
    }
    if ((i << 1) + 1 < LEVEL) {
        if (!fork()) {
            tree_fork(msgid, (i << 1) + 1, n);
            _exit(0);
        }
    }
    while (wait(NULL) != -1);  
    merge(msgid, i); 
}

int
main(int argc, char *argv[])
{
    int n = 1;
    while(n < argc - 1) {
        n <<= 1;
    } 
    struct Message msg; 
    MAX = argc - 1;
    LEVEL = n; 
    int msgid;
    key_t key = 1; 
    while ((msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL)) == -1) {
        key++;
    }  
    int tmp;
    for (int i = 1; i < argc; i++) {
        if (!fork()) {
            FILE *f = fopen(argv[i], "r");
            msg.type = n;
            while (fscanf(f, "%d", &tmp) == 1) { 
                msg.value = tmp; 
                if(msgsnd(msgid, &msg, sizeof(msg) - sizeof(msg.type), IPC_NOWAIT) < 0) { 
                    _exit(1);
                }
            }
            fclose(f); 
            _exit(0);
        }
        n += 2;
        if(n >= LEVEL * 2) {
            n = LEVEL + 1;
        }
    }
    while(wait(NULL) != -1);
    tree_fork(msgid, 1, n); 
    while(wait(NULL) != -1);
    while (msgrcv(msgid, &msg, sizeof(msg) - sizeof(msg.type), 1, IPC_NOWAIT) != -1) {
        printf("%ld\n", msg.value);
    }
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}