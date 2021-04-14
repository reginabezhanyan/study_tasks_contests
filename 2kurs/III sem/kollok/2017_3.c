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
    int fd[2];
    pipe(fd); 
    if (!fork()) { 
        if (!fork()) {
            pid_t pids = getpid(), pidp = getppid();
            write(fd[1], &pids, sizeof(pids));
            write(fd[1], &pidp, sizeof(pidp));
            _exit(0);            
        }
        close(fd[1]); close(fd[0]); 
        wait(NULL);
        _exit(0);
    }
    if (!fork()) { 
        if (!fork()) {
            pid_t son, parent;
            read(fd[0], &son, sizeof(son));
            read(fd[0], &parent, sizeof(parent));
            printf("%d %d\n", son, parent);
            fflush(stdout); 
            _exit(0);
        }
        close(fd[1]); close(fd[0]); 
        wait(NULL);
        _exit(0);
    }
    close(fd[1]); close(fd[0]); 
    while (wait(NULL) != -1); 
    return 0;
}

