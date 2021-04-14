#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <string.h>

int
main (int argc, char *argv[])
{
    pid_t pid;
    int status;
    int i = 1; 
    if (argc == i || argc == i + 1) {
        return 0;
    }
    i = argc - 1; 
    while (i >= 2) { 
        if (i + 1 < argc) {
            argv[i + 1] = NULL; 
        }
        while(strcmp(argv[1], argv[i]) != 0) {
            i--;
        } 
        pid = fork();
        if (pid < 0) {
            return 1;
        } else if (!pid) { 
            execvp(argv[i + 1], &argv[i + 1]);
            _exit(1);
        }
        wait(&status);
        if(!WIFEXITED(status) || WEXITSTATUS(status) || WIFSIGNALED(status)) { 
            printf("ne norm\n");
            return 1;
        } 
        i--;
    }
    return 0;
}