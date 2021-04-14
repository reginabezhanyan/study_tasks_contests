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
    pid_t pid = fork();
    int status;
    if (pid < 0) {
        return 0;
    } else if(!pid) {
        int file1, file2, file3;
        if ((file1 = open(argv[2], O_RDONLY, 0660)) < 0) {
            _exit(42);
        }
        if ((file2 = open(argv[3], O_CREAT | O_WRONLY | O_APPEND, 0660)) < 0) {
            _exit(42);
        }
        if ((file3 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0660)) < 0) {
            _exit(42);
        }
        if (dup2(file1, STDIN_FILENO) < 0) {
            _exit(42);
        }
        if (close(file1) < 0) {
            _exit(42);
        }
        if (dup2(file2, STDOUT_FILENO) < 0) {
            _exit(42);
        }
        if (close(file2) < 0) {
            _exit(42);
        }
        if (dup2(file3, STDERR_FILENO) < 0) {
            _exit(42);
        }
        if (close(file3) < 0) {
            _exit(42);
        }
        execlp(argv[1], argv[1], NULL);
        _exit(42);
    } else {
        wait(&status);
        printf("%d\n", status);
    }
    return 0;   
}

