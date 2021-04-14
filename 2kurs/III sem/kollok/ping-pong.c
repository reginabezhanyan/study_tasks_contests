#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_CNT = 100 };
int target_pid, cnt;
int fd[2];
int status;
int num;

void handler(int s)
{
    if (cnt < MAX_CNT) {
        read(fd[0], &cnt, sizeof(cnt));
        printf("%d %d\n", num, cnt);
        fflush(stdout);
        cnt++;
        write(fd[1], &cnt, sizeof(cnt));
        kill(target_pid, SIGUSR1);
    } else if (target_pid == getppid()) {
        printf("Child bb\n");
        close(fd[1]);
        close(fd[0]);
        exit(0);
    } else {
        kill(target_pid, SIGUSR1);
    }
}

int main(void)
{
    pipe(fd);
    signal(SIGUSR1, handler);
    cnt = 0;
    
    if (target_pid = fork()) {
        num = 1;
        write(fd[1], &cnt, sizeof(cnt));
        while(wait(&status) == -1);
        printf("Parent bb\n");
        fflush(stdout);
        close(fd[1]);
        close(fd[0]);
    } else {
        num = 2;
        read(fd[0], &cnt, sizeof(cnt));
        target_pid = getppid();
        write(fd[1], &cnt, sizeof(cnt));
        kill(target_pid, SIGUSR1);
        while (1) {
            pause();
        }
    }
    return 0;
}
