#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <limits.h>

enum { K = 4 };

int
main(int argc, char *argv[])
{ 
    key_t key = 1;
    int shmid; 
    if ((shmid = shmget(key, argc * sizeof(long long), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        key++;
    }
    long long *sum = (long long *) shmat(shmid, NULL, 0); 
    for(int i = 1; i < argc; i++) {
        if(!fork()) { 
            long long tmp = strtoll(argv[i], NULL, 10);
            sum[i] = 0; 
            if (tmp == LLONG_MIN) {
                sum[i]  = 2;
            } else {
                if (tmp < 0) {
                    tmp *= -1;
                } 
                while(tmp != 0) {
                    sum[i] += tmp % K;
                    tmp = tmp / K;
                }
            } 
            _exit(0);
        }
    }
    while(wait(NULL) != -1);
    for(int i = 1; i < argc; i++) {
        printf("%lld\n", sum[i]);
        fflush(stdout);
    }
    shmdt(sum); 
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}