#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <string.h> 
#include <stdlib.h>

int lsh, lse;

void handler(int s)
{
    semctl(lse, 0, IPC_RMID);
    shmctl(lsh, 0, IPC_RMID);
    exit(0);
}

void work(key_t key, int n)
{
    int shmid, semid;
    char *shmaddr;
    char line[100] = {0};

    printf(" %d HERE\n", n);
    fflush(stdout);

    while ((shmid = shmget(key, sizeof(line), 0666)) < 0);
    while ((semid = semget(key, 2, 0666)) < 0);

    shmaddr = shmat(shmid, NULL, 0);
    strcpy(line, shmaddr);
    printf("%d: %s\n", n, line);
    fflush(stdout);

    struct sembuf op1[] =
    {
        { .sem_num = 0, -1, 0 },
        { .sem_num = 1, 1, 0 }
    };
    semop(semid, op1, sizeof(op1) / sizeof(op1[0]));

    if (semctl(semid, 1, GETVAL, NULL) == 1) {
        snprintf(line, sizeof(line), "HAHA I'S FIRST, LOSER, SUCK, %d", (n % 2) + 1);
        strcpy(shmaddr, line);
    } else {
        strcpy(line, shmaddr);
        printf("OH %d: %s\n", n, line);
        fflush(stdout);
    }
    struct sembuf op2[] =
    {
        { 0, 1, 0 },
    };
    semop(semid, op2, sizeof(op2) / sizeof(op2[0]));
    shmdt(shmaddr);
    _exit(0);
}

int main(int argc, char *argv[])
{
    char line[100] = {0};
    key_t key = strtol(argv[1], NULL, 10);
    int shmid, semid;
    char *shmaddr;

    signal(SIGINT, handler);
    lsh = shmget(key, sizeof(line), 0666 | IPC_CREAT | IPC_EXCL);
    lse = semget(key, 2, 0666 | IPC_CREAT | IPC_EXCL);
    shmid = lsh;
    semid = lse;
    shmaddr = shmat(shmid, NULL, 0);
    strcpy(shmaddr, "I love dogs and always ready have a sex with some cats!");

    if (!fork()) {
        work(key, 1);
    }
    if (!fork()) {
        work(key, 2);
    }

    short arr[2] = {1, 0};

    printf("OK, GO!\n");
    fflush(stdout);
    semctl(semid, 0, SETALL, arr);    
    
    while (wait(NULL) != -1);
    semctl(semid, 0, IPC_RMID);
    shmctl(shmid, 0, IPC_RMID);
    return 0;
}
