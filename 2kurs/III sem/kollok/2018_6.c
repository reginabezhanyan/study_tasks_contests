#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <signal.h>

int
main (void)
{ 
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2); 
    if (!fork()) {
        pid_t pid_br2;
        pid_t pid1 = getpid();
        close(fd1[1]);
        close(fd2[0]);
        write(fd2[1], &pid1, sizeof(pid1));
        read(fd1[0], &pid_br2, sizeof(pid_br2));
        printf("1 %d %d\n", getpid(), pid_br2);
        //fflush(stdout);
        _exit(0);
    }
    if (!fork()) {
        pid_t pid_br1;
        pid_t pid2 = getpid();
        close(fd1[0]);
        close(fd2[1]);
        write(fd1[1], &pid2, sizeof(pid2));
        read(fd2[0], &pid_br1, sizeof(pid_br1));
        printf("2 %d %d\n", getpid(), pid_br1);
        //fflush(stdout);
        _exit(0);
    }
    close(fd1[1]); close(fd1[0]);
    close(fd2[0]); close(fd2[1]);
    while (wait(NULL) != -1); 
    return 0;
}

