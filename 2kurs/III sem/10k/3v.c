#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

enum
{
    READ,
    APPEND,
    ELSE
};


int
func(char *cmd, int mod, char *file)
{
    pid_t pid = fork();
    if (!pid) {
        int fd;
        if (mod == 0) {
            if ((fd = open(file, O_RDONLY)) < 0 || dup2(fd, 0) < 0) {
                _exit(1);
            }
            close(fd);
        } else if (mod == 1) {
            if ((fd = open(file, O_WRONLY | O_APPEND)) < 0 || dup2(fd, 1) < 0) {
                _exit(1);
            }
            close(fd);            
        }
        execlp(cmd, cmd, NULL);
        _exit(1);
    } else if (pid > 0) {
        int status;
        wait(&status);
        return WIFEXITED(status) && WEXITSTATUS(status) == 0;
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    int fd[2];
    if(pipe(fd) < 0) {
        return 1;
    }
    pid_t pid = fork();
    if (pid < 0) {
        return 1;
    } else if (!pid) {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        _exit(!(func(argv[1], READ, argv[4]) && func(argv[2], ELSE, NULL)));
    }
    int status;
    wait(&status);
    dup2(fd[0], 0);
    close(fd[1]);
    close(fd[0]);
    func(argv[3], APPEND, argv[5]);
    return 0;
}