#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 

int
main(void)
{
    int num, tmp;
    int status = 0;
    pid_t pid;
    for(int i = 0; ; i++) {
        pid = fork();
        if (pid < 0) {
            if (i != 0) {
                if(fscanf(stdin, "%d", &tmp) == EOF) {
                    fprintf(stdout,"%d\n", num);
                    break;
                }
                _exit(1);   
            } else {
                return 0;
            }   
        } else if (pid) {
            wait(&status);
            if (!WIFEXITED(status) || WEXITSTATUS(status) == 1) {
                if (i != 0) {
                    _exit(1);
                } else {
                    fprintf(stdout, "%d\n", -1);
                    break;
                }
            } else {
                if (i != 0) {
                    fprintf(stdout,"%d\n", num);
                }
                break;
            } 
        }
        if (fscanf(stdin, "%d", &num) == EOF) {
            break;
        }
    }
    return 0;
}