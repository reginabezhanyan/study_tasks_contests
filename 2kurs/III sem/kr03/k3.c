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

enum
{
    MAX = 5,
    K = 32,
    B = 2,
    C = 6
};  

int
main(void)
{
    int semid;
    key_t key = 1;
    while((semid = semget(key, 4, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        key++;
    } 
    int shmid; 
    key = 1;
    while ((shmid = shmget(key, sizeof(unsigned int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        key++;
    }
    unsigned int *shmaddr = (unsigned int*) shmat(shmid, NULL, 0); 
    
    if(!fork()) {
        struct sembuf down[] =
        {
            { .sem_num = 1, -1, 0},
        };
        while(1) {
            if(semop(semid, down, sizeof(down) / sizeof(down[0])) < 0) {
                _exit(0);
            }
            unsigned ip =  shmaddr[0]; 
            printf("1 %x\n", (ip << 8) >> 8);
            fflush(stdout);
            semctl(semid, 0, SETVAL, 1);
        }
        
    }
    if(!fork()) {
        struct sembuf down[] =
        {
            { .sem_num = 2, -1, 0},
        };
        while(1) {
            if(semop(semid, down, sizeof(down) / sizeof(down[0])) < 0) {
                _exit(0);
            }
            unsigned ip =  shmaddr[0]; 
            printf("2 %x\n", (ip << 16) >> 16);
            fflush(stdout);
            semctl(semid, 0, SETVAL, 1);
        }
        
    }
    if(!fork()) {
        struct sembuf down[] =
        {
            { .sem_num = 3, -1, 0},
        };
        while(1) {
            if(semop(semid, down, sizeof(down) / sizeof(down[0])) < 0) {
                _exit(0);
            }
            unsigned ip =  shmaddr[0];  
            printf("3 %x\n", (ip << 24) >> 24);
            fflush(stdout); 
            semctl(semid, 0, SETVAL, 1);
        }
    }
    struct sembuf down[] =
    {
        { .sem_num = 0, -1, 0},
    }; 
    unsigned int IPv4; 
    while(scanf("%o", &IPv4) == 1) {  
        if((IPv4 >> (K - 1)) == 0) {
            shmaddr[0] = IPv4;
            semctl(semid, 1, SETVAL, 1);
            semop(semid, down, sizeof(down) / sizeof(down[0]));
        } else if((IPv4 >> (K - B)) == B) {
            shmaddr[0] = IPv4;
            semctl(semid, 2, SETVAL, 1);
            semop(semid, down, sizeof(down) / sizeof(down[0]));
        } else if((IPv4 >> (K - 3)) == C){
            shmaddr[0] = IPv4;
            semctl(semid, 2, SETVAL, 1);
            semop(semid, down, sizeof(down) / sizeof(down[0]));
        }
    }
    semctl(semid, IPC_RMID, 0);
    while(wait(NULL) != -1);
    shmdt(shmaddr); 
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}