#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

enum { BASE = 127 };

int
mysys (const char *str)
{
    int status;
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    } else if (!pid) {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(BASE);
    } else {
        waitpid(pid, &status, 0); 
        if (WIFSIGNALED(status)) {
            return BASE + 1 + WTERMSIG(status);
        } else {
            return WEXITSTATUS(status);
        }
    } 
}