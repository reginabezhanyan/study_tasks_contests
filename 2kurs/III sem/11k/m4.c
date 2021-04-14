#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <signal.h>

int
main (int argc, char *argv[])
{ 
    int fd1[2], fd2[2];
    int num = 1;
    int n;
    sscanf(argv[1], "%d", &n); 
    pipe(fd1);
    pipe(fd2);
    FILE *f11 = fdopen(fd1[0], "r");
    FILE *f12 = fdopen(fd1[1], "w");
    FILE *f21 = fdopen(fd2[0], "r");
    FILE *f22 = fdopen(fd2[1], "w");
    fprintf(f22, "%d", num);
    pid_t pid1, pid2;
    if(!(pid1 = fork())) {
        int tmp1;
        fscanf(f21, "%d", n&tmp1);
        if (tmp1 == n) {
            
        }
    }
    return 0;
}