#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h> 

int
main (int argc, char *argv[]) //(cmd1 < file1 && cmd2) | cmd3 >> file2
{
    int fd[2];
    if (pipe(fd) < 0) {
        return 1;
    }
    if(!fork()) {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]); 
        if (!fork()) {
            int file1;
            if ((file1 = open(argv[4], O_RDONLY)) < 0) {
                return 1;
            }
            dup2(file1, 0);  
            close(file1); 
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }
        int status;
        wait(&status);
        if(WIFEXITED(status) && !WEXITSTATUS(status)) {  
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        } 
    }
    if (!fork()) {
        int file2;
        if ((file2 = open(argv[5], O_CREAT | O_WRONLY | O_APPEND, 0666)) < 0) {
            return 1;
        }
        dup2(file2, 1);
        dup2(fd[0], 0);
        close(file2);
        close(fd[0]); 
        close(fd[1]); 
        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }
    close(fd[0]); 
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}