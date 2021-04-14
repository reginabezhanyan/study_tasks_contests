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
    pipe(fd);
    if(!fork()) {
        int file4 = open(argv[4], O_RDONLY);
        dup2(file4, 0);  
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);  
        execlp(argv[1], argv[1], NULL);
        _exit(1); 
        close(file4);
    }
    
    if(!fork()) {
        int file5 = open(argv[5], O_CREAT | O_WRONLY | O_APPEND, 0640);
        dup2(file5, 1);
        dup2(fd[0], 0);
        close(fd[1]);
        close(fd[0]);
        if (!fork()) {
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }
        int tatus;
        wait(&status);
        if(!WIFEXITED(status) || WEXITSTATUS(status)) {  
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        } 
        close(file5);
    }
    
    close(fd[0]); 
    close(fd[1]);
    while (wait(NULL) != -1);
    
    return 0;  
}