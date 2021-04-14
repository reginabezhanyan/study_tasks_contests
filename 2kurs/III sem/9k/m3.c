#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int
start (char *str)
{
    int status;
    pid_t pid = fork();
    if (!pid) {
        execlp(str, str, NULL);
        _exit(1);
    } else {
        wait(&status);
    }
    return (WIFEXITED(status) && !WEXITSTATUS(status));
}

int
main (int argc, char *argv[])
{
    return !((start(argv[1]) || start(argv[2])) && start(argv[3]));
}