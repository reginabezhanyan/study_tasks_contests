#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char* argv[])
{ 
    int count = strtol(argv[1], NULL, 10);  
    int semid = semget(key, nproc, 0666 | IPC_CREAT | IPC_EXCL);
    if (semid < 0) {
        return 1;
    }   
    semctl(semid, 0, SETVAL, 1); 
    FILE *in= fdopen(0, "r");
    FILE *out = fdopen(1, "w");        
    for (int i = 0; i < count; i++) {
        struct sembuf b1[] =
        {
            { .sem_num = i, -1, SEM_UNDO },
        };  
        if(!fork()) {  
            while(1) {
                if(semop(semid, b1, sizeof(b1) / sizeof(b1[0])) < 0) {
                    _exit(1);
                }
                int buf;
                if(fscanf(in, "%d", &buf) == EOF) {
                    _exit(0);
                }
                printf(out, "%d %d\n", i, buf);
                fflush(out);
                int proc = buf % count;
                struct sembuf b2[] =
                {
                    { .sem_num = proc, 1, SEM_UNDO },
                }; 
                if(semop(semid, b2, sizeof(b2) / sizeof(b2[0])) < 0) {
                    _exit(1);
                }  
            }            
        }
    } 
    
    semctl(semid, 0, IPC_RMID, 0);
    while (wait(NULL) != -1); 

    return 0;
}