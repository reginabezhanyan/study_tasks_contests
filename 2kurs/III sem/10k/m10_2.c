#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <time.h> 

int
main(void)
{
    int fd[2];
    if (pipe(fd) < 0) {
        return 1;
    }
    pid_t pid = fork();
    if(pid < 0) {
        return 1;
    } else if(pid > 0) { 
        close(fd[0]); 
        int buf;
        while (fscanf(stdin, "%d", &buf) != EOF) {
            if (write(fd[1], &buf, sizeof(buf)) < 0) {
                return 1;
            }
        }
        close(fd[1]);
        wait(NULL);
    } else {
        pid_t pid2 = fork();
        if (pid2 < 0) {
            return 1;
        } else if (pid2 > 0) {
            close(fd[0]); 
            close(fd[1]);
            wait(NULL);
        } else {
            close(fd[1]);
            int num;
            long long int sum = 0;
            while (read(fd[0], &num, sizeof(num)) == sizeof(num)) {
                sum += num;
            }
            close(fd[0]);
            fprintf(stdout, "%lld\n", sum);
        }
    }
    return 0;
}