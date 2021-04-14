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
    long long x1;
    long long x2;
};

int main(int argc, char* argv[])
{  
    key_t key = strtol(argv[1], NULL, 10);
    long long int n = strtoll(argv[2], NULL, 10); 
    long long int value1 = strtoll(argv[3], NULL, 10); 
    long long int value2 = strtoll(argv[4], NULL, 10); 
    long long int maxval = strtoll(argv[5], NULL, 10); 
    pid_t pid; 
    int msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL); 
    if (msgid < 0) { 
        return 1;
    } 
    struct Message msg;
    msg.type = 1;
    msg.x1 = value1;
    msg.x2 = value2; 
    int size = sizeof(msg) - sizeof(msg.type);
    for (int i = 0; i < n; i++) { 
        pid = fork();
        if(pid < 0) {
            msgctl(msgid, IPC_RMID, NULL);
            while (wait(NULL) != -1); 
            return 1;
        } else if(!pid) {  
            while(1) {
                if(msgrcv(msgid, &msg, size, i + 1, 0) < 0) {
                    _exit(1);
                }
                long long x3 = msg.x1 + msg.x2;
                printf("%d %lld\n", i, x3);
                fflush(stdout);
                if (x3 <= maxval) {
                    msg.x1 = msg.x2;
                    msg.x2 = x3; 
                    msg.type = x3 % n + 1;
                    if(msgsnd(msgid, &msg, size, IPC_NOWAIT) < 0) {
                        _exit(1);
                    }
                } else {
                    msgctl(msgid, IPC_RMID, NULL);
                    _exit(0);
                }
            }            
        } 
    } 

    if(msgsnd(msgid, &msg, size, IPC_NOWAIT) < 0) {
        return 1;
    }
    while (wait(NULL) != -1);  
    return 0;
}