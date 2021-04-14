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
    pid_t *pid = malloc((n + 1)* sizeof(*pid));
    int count = 0; 
    int msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL); 
    if (msgid < 0) {
        fprintf(stderr, "msgget: %s\n", strerror(errno));
        return 1;
    } 
	struct Message msg;
    msg.type = 1;
    msg.x1 = value1;
    msg.x2 = value2; 
	int size = sizeof(msg) - sizeof(msg.type);
    
    for (int i = 1; i <= n; i++) { 
        pid[i] = fork();
        if(pid[i] < 0) {
            msgctl(msgid, IPC_RMID, NULL);
            for(int j = 1; j <= count; j++) {
                kill(pid[j], SIGKILL);
            } 
            free(pid);
            while (wait(NULL) != -1); 
            return 1;
        } else if(!pid[i]) {  
			//printf("%d %d %d\n", i, getpid(), pid[i]);
            while(1) {
                if(msgrcv(msgid, &msg, size, i, 0) < 0) {
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
        count++;
    } 

    if(msgsnd(msgid, &msg, size, IPC_NOWAIT) < 0) {
		fprintf(stderr, "msgsnd: %s\n", strerror(errno));
        return 1;
    } 
    
    while (wait(NULL) != -1); 
    free(pid);
    return 0;
}