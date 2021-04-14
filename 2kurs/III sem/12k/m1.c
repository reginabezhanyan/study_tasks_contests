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
    int nproc = strtol(argv[1], NULL, 10); 
    key_t key = strtol(argv[2], NULL, 10);
    long long int maxval = strtol(argv[3], NULL, 10); 
    int semid = semget(key, nproc, 0666 | IPC_CREAT | IPC_EXCL);
    if (semid < 0) {
        return 1;
    }   
    semctl(semid, 0, SETVAL, 1);
    int shmid = shmget(key, 2 * sizeof(long long int), 0666 | IPC_CREAT | IPC_EXCL);
    if (shmid < 0) {
        return 1;
    }
    long long int *shmaddr = (long long int*) shmat(shmid, NULL, 0);
    shmaddr[0] = 0;
    shmaddr[1] = 0; 
    for (int i = 0; i < nproc; i++) {
        struct sembuf b1[] =
        {
            { .sem_num = i, -1, 0 },
        };  
        if(!fork()) {  
            while(1) {
                if(semop(semid, b1, sizeof(b1) / sizeof(b1[0])) < 0) {
                    _exit(1);
                }
                printf("%d %lld %lld\n", i + 1, shmaddr[0], shmaddr[1]);
                fflush(stdout);
                if (shmaddr[0] < maxval) {
                    shmaddr[0]++;
                    shmaddr[1] = i + 1;
                    int proc = ((shmaddr[0] % nproc) * (shmaddr[0] % nproc) * 
                            (shmaddr[0] % nproc) * (shmaddr[0] % nproc)) % nproc; 
                fflush(stdout);
                    struct sembuf b2[] =
                    {
                        { .sem_num = proc, 1, 0 },
                    }; 
                    if(semop(semid, b2, sizeof(b2) / sizeof(b2[0])) < 0) {
                        _exit(1);
                    }  
                } else {
                    _exit(0);
                }
            }            
        }
    } 
    wait(NULL);
    semctl(semid, 0, IPC_RMID, 0);
    while (wait(NULL) != -1);
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, 0);

    return 0;
}