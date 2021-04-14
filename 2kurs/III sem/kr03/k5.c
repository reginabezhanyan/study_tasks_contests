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
    int count = 0; 
    for(int i = 1; i < argc; i++) {
        if (argv[i][0] == 'p') { 
            if(!fork()) {
                execlp(&argv[i][1], &argv[i][1], NULL);
                _exit(1);
            }
        } else if (argv[i][0] == 's'){
            int status;
            while (wait(&status) != -1) {
                if(WIFEXITED(status) && !WEXITSTATUS(status)) {
                    count++;
                }
            }
            if(!fork()) {
                execlp(&argv[i][1], &argv[i][1], NULL);
                _exit(1);
            }
            wait(&status);
            if(WIFEXITED(status) && !WEXITSTATUS(status)) {
                count++;
            }
        }
    }
    int status;
    while (wait(&status) != -1) {
        if(WIFEXITED(status) && !WEXITSTATUS(status)) {
            count++;
        }
    }
    printf("%d\n", count);
    fflush(stdout);
    return 0;
}