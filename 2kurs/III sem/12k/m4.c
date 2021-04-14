#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

int
main(int argc, char* argv[])
{      
    int count = strtol(argv[1], NULL, 10); 
    key_t key = ftok(argv[0], 0); 
    int semid = semget(key, count, 0666 | IPC_CREAT | IPC_EXCL);
    if (semid < 0) {
        return 1;
    }
    setvbuf(stdin, NULL, _IONBF, 0);
    for (int i = 0; i < count; i++) { 
        if(!fork()) {  
            int buf;
            while(1) {
                struct sembuf b1[] =
                {
                    { .sem_num = i, -1, 0},
                };
                if(semop(semid, b1, sizeof(b1) / sizeof(b1[0])) < 0) {
                    _exit(1);
                } 
                if (scanf("%d", &buf) == 1) {
                    printf("%d %d\n", i, buf);
                    fflush(stdout);
                    int proc = buf  % count;
                    if (proc < 0) {
                        proc += count;
                    }
                    struct sembuf b2[] =
                    {
                        { .sem_num = proc, 1, 0 },
                    }; 
                    if(semop(semid, b2, sizeof(b2) / sizeof(b2[0])) < 0) {
                        _exit(1);
                    }  
                } else {
                    semctl(semid, 0, IPC_RMID, 0);
                    _exit(0);
                } 
            }
        }
    } 
    semctl(semid, 0, SETVAL, 1); 
    while (wait(NULL) != -1);  
    return 0;
}