#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <time.h>

enum { K = 10 }; 

int main(int argc, char* argv[])
{ 
    int count = strtol(argv[1], NULL, 10); 
    key_t key = strtol(argv[2], NULL, 10);
    int nproc = strtol(argv[3], NULL, 10);
    int iter_count = strtol(argv[4], NULL, 10);  
    int semid = semget(key, count, 0666 | IPC_CREAT | IPC_EXCL);
    if (semid < 0) {
        return 1;
    }   
    short *ptr = calloc(count, sizeof(ptr[0]));
    for(int i = 0; i < count; i++) {
        ptr[i] = 1;
    } 
    semctl(semid, 0, SETALL, ptr);
    
    int shmid = shmget(key, count * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL);
    if (shmid < 0) {
        return 1;
    }
    
    int *shmaddr = (int*) shmat(shmid, NULL, 0);
    for(int i = 0; i < count; i++) {
        scanf("%d", &shmaddr[i]);
    } 
    
    for (int i = 0; i < nproc; i++) { 
        if(!fork()) {  
            int gpsch = strtoll(argv[i + 5], NULL, 10); 
            srand(gpsch);
            for(int j = 0; j < iter_count; j++) {
                int ind1 = rand() % count;
                int ind2 = rand() % count;
                int val = rand() % K;  
                if(ind1 != ind2) {
                    struct sembuf down[] =
                    {
                        { .sem_num = ind1, -1, 0 },
                        { .sem_num = ind2, -1, 0},
                    };  
                    if(semop(semid, down, sizeof(down) / sizeof(down[0])) < 0) {
                        _exit(1);
                    }
                    operation(shmaddr, ind1, ind2, val);
                    struct sembuf up[] =
                    {
                        { .sem_num = ind1, 1, 0 },
                        { .sem_num = ind2, 1, 0},
                    };  
                    if(semop(semid, up, sizeof(up) / sizeof(up[0])) < 0) {
                        _exit(1);
                    }   
                }   
            }  
            _exit(0);
        }
    } 
    while (wait(NULL) != -1);
    semctl(semid, 0, IPC_RMID, 0);
    for(int i = 0; i < count; i++) {
        printf("%d\n", shmaddr[i]);
        fflush(stdout);
    }
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}