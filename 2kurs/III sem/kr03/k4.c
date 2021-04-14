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

int
main(int argc, char* argv[])
{      
    int semid, shmid, memid;
    key_t key = 1;
    while((semid = semget(key, argc, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        key++;
    } 
    key = 1;
    while((shmid = shmget(key, sizeof(unsigned int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        key++;
    }
    unsigned int *shmaddr = (unsigned int *) shmat(shmid, NULL, 0);
    key = 1;
    while((memid = shmget(key, sizeof(unsigned char), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        key++;
    }
    unsigned char *memaddr = (unsigned char *) shmat(memid, NULL, 0);
    
    unsigned int n = argc - 1;
    int l = 0;
    while(n > 0) {
        l++;
        n >>= 1;
    } 
    for (int i = 1; i < argc; i++) {
        if(!fork()) {
            int fd = open(argv[i], O_RDONLY); 
            struct sembuf down[] = { i, -1, 0 }; 
            while(1) {
                if(semop(semid, down, sizeof(down) / sizeof(down[0])) < 0) {
                    close(fd);
                    _exit(0);
                } 
                lseek(fd, shmaddr[0], SEEK_SET);
                unsigned char mem;
                read(fd, &mem, sizeof(mem));
                memaddr[0] = mem;
                semctl(semid, 0, SETVAL, 1);
            }
        }
    }
    unsigned int addr;
    unsigned int mask  = 0;
    for (int j = 0; j < l; j++) {
        mask = (mask << 1) + 1;
    } 
    struct sembuf b1[] = { 0, -1, 0 }; 
    while (fscanf(stdin, "%u", &addr) == 1) {
        unsigned int k = (addr & mask) + 1; 
        addr >>= l;
        shmaddr[0] = addr;
        semctl(semid, k, SETVAL, 1);
        semop(semid, b1, sizeof(b1) / sizeof(b1[0]));
        printf("%u\n", memaddr[0]);
        fflush(stdout);
    }
    semctl(semid, 0, IPC_RMID, 0);
    shmdt(shmaddr);
    shmdt(memaddr);
    shmctl(shmid, IPC_RMID, 0);
    shmctl(memid, IPC_RMID, 0);
    while (wait(NULL) != -1);  
    return 0;
}