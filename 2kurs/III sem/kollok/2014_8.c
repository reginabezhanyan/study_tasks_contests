#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>  
 
int
main (int argc, char *argv[])
{
    int fd[2];
    for (int i = 1; i < 3; i++) {
        pipe(fd);
        if (!fork()) {  
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]); 
            execlp(argv[i], argv[i], NULL); 
            _exit(1);
        }   
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]); 
    } 
    if (!fork()) {
        execlp(argv[3], argv[3], NULL); 
        _exit(1);
    } 
    close(0);
    while (wait(NULL) != -1);  
    return 0;
} 